#include "functions.h"

void print (char *filename, vector<double> v){
  ofstream fout(filename);
  int dim=v.size();
  if(!fout) {
  	cout<<"cannot open output_file"<<endl;
  	exit(0);
  	 }
  for (int i=0; i<dim; i++)
  	fout <<v[i]<< endl;
}

void print (int r, vector<double> v){
  char *filename;
  if(r==0){
    filename=(char *)"L_square.0";
  }
  if(r==1){
    filename=(char *)"L_square.1";
  }
  if(r==2){
    filename=(char *)"L_square.2";
  }
  if(r==3){
    filename=(char *)"L_square.3";
  }
  ofstream fout(filename);
  int dim=v.size();
  if(!fout) {
  	cout<<"cannot open output_file"<<endl;
  	exit(0);
  	 }
  for (int i=0; i<dim; i++)
  	fout <<v[i]<< endl;
  fout.close();
}

element :: element(){}

element :: element(int p){
  n_cities =p;
  path.assign(n_cities,0);
  L=0;
}

element :: ~element(){}

void element :: SetStart(){
  for (int i=0; i<n_cities; i++){
    path[i]=i+1;
  }
}

void element :: copy(element old){
  for (int i=0; i<n_cities; i++){
    path[i]=old.GetCity(i);
  }
  L=old.GetL();
}

int element :: pbc(int j){ //periodic boundary conditions that avoid first element
    if (j>=n_cities)
      return j-n_cities+1;
    else
      return j;
}

void element :: perm(int i, int j){
  if(i==0 || j==0){
    cout <<"I can't permutate the first city"<<endl;
    i++;
    j++;
  }
  int appo=path[i];
  path[i]=path[j];
  path[j]=appo;
  check();
}

void element :: mut_shift(int m, int n, Random * rm){
  int st=rm->RanInt(1,n_cities-m);
  int appo;
  if(m>=n_cities-1){
    cout<<"m troppo grande"<<endl;
    m=n_cities-2;
  }
  for (int i=0; i<n; i++){
    appo=path[pbc(st+m+i)];
    for (int j=0; j<m;j++){
      path[pbc(st+m+i-j)]=path[pbc(st+m+i-j-1)];
    }
    path[pbc(st+i)]=appo;
  }
  check();
}

void element :: mut_cont(int m, Random* rn){
  int appo, st;
  st=rn->RanInt(1,n_cities-2*m);
  if(m>=n_cities/2){
    cout<<"m troppo grande"<<endl;
    m=(n_cities/2)-1;
  }
  for(int i=0; i<m; i++){
    appo=path[st+i];
    path[st+i]=path[st+m+i];
    path[st+m+i]=appo;
  }
  check();
}

void element :: mut_inv(int m, Random* rn){
  int appo, st;
  if(m>=n_cities){
    cout<<"m troppo grande"<<endl;
    m=n_cities-1;
  }
  st=rn->RanInt(1,n_cities-m);
  for(int i=0; i<(int)m/2; i++){
    appo=path[st+i];
    path[st+i]=path[st+m-i];
    path[st+m-i]=appo;
  }
  check();
}

void element :: Length(vector<double> x, vector<double> y){
  int c1, c2;
  double accu=0;
  for (int i=0; i<n_cities; i++){
    if (i==n_cities-1){
      c1=path[i]-1;
      c2=path[0]-1;
    }
    else{
      c1=path[i]-1;  //position of the city i in the vector of coordinates
      c2=path[i+1]-1;   //position of city i+1 in the vector of coordinates
    }
    accu +=sqrt(pow(x[c1]-x[c2],2)+pow(y[c1]-y[c2],2));
  }
  L=accu;
}

void element :: check(){
  if (path[0]!=1){
    cout<<"check error "<<endl;
    cout<<"printing wrong element "<<endl;
    print();
    exit(0);
  }
  vector<int>v(n_cities,0);
  int j;
  for (int i=0; i<n_cities; i++){
    j=path[i];
    v[j-1]+=1;
  }
  for (int i=0; i<n_cities; i++){
    if (v[i]!=1){
      cout<<"check error"<<endl;
      cout<<"printing wrong element "<<endl;
      print();
      exit(0);
    }
  }
  vector <int> ().swap(v);
}

void element :: print(){
  cout<<endl;
  for(int i=0; i<n_cities; i++)
    cout<<path[i]<<endl;
}

void element :: clean(){ //clear memory once the element is no longer part of my population
  vector <int> ().swap(path);
}


population :: population(){}

population :: population(int p, int n, vector<double> x0, vector<double> y0, Random * r){
  n_element =p;
  cities=n;
  rnd=r;
  for (int i=0; i<cities; i++){
    x.push_back(x0[i]);
    y.push_back(y0[i]);
  }
}

population :: ~population(){}

void population :: SetProb(double m, double c){
  r_mut=m;
  r_cross=c;
}

void population :: start(){
  int c1, c2;
  element first(cities);
  first.SetStart();         //genero primo elemento ordinato e ne calcolo la lunghezza
  first.Length(x,y);
  gen.push_back(first);             //lo assegno come primo elemento della mia popolazione
  new_gen.push_back(first);
  for (int i=1; i<n_element; i++){ //genero altri elementi permutando casualmente dal primo
    element one(cities);
    one.copy(gen[i-1]);
    c1=rnd->RanInt(1,cities);
    do {
      c2=rnd->RanInt(1,cities);
    }while(c2==c1);
    one.perm(c1,c2);
    one.Length(x,y);
    gen.push_back(one);
    new_gen.push_back(one);
  }
  order();
}

void population :: order(){
  sort(gen.begin(),gen.end());
}

int population :: select(){
  double r=rnd->Rannyu();
  int p=2;
  int j=(int)(n_element*pow(r,p));
  return j;
}

void population :: crossover (int one, int two){
  int c=rnd->RanInt(1,cities);
  int accu;
  element child1(cities), child2(cities);
  for (int i=0; i<c; i++){
    child1.SetCity(i,gen[one].GetCity(i));
    child2.SetCity(i,gen[two].GetCity(i));
  }
  int i=c;
  for(int j=0; j<cities; j++){
    accu=0;
    for(int k=0; k<i; k++){
      if(gen[two].GetCity(j)==child1.GetCity(k))
        accu++;
    }
    if(accu==0){
      child1.SetCity(i,gen[two].GetCity(j));
      i++;
    }
  }
  i=c;
  for(int j=0; j<cities; j++){
    accu=0;
    for(int k=0; k<i; k++){
      if(gen[one].GetCity(j)==child2.GetCity(k))
        accu++;
    }
    if(accu==0){
      child2.SetCity(i,gen[one].GetCity(j));
      i++;
    }
  }
  child1.check();
  child2.check();
  child1.Length(x,y);
  child2.Length(x,y);
  gen[one].copy(child1);
  gen[two].copy(child2);
}

void population :: mutate(int s){
  int i=rnd->Rannyu(0,4);
  int c, d;
  if(i<1){
    c=rnd->RanInt(1,cities);
    do {
      d=rnd->RanInt(1,cities);
    }while(c==d);
    gen[s].perm(c,d);
  }
  if(i>=1 && i<2){
    c=rnd->RanInt(1,cities-1);
    d=rnd->RanInt(1,cities-2);
    gen[s].mut_shift(c,d,rnd);
  }
  if(i>=2 && i<3){
    c=rnd->RanInt(1,cities/2);
    gen[s].mut_cont(c,rnd);
  }
  if(i>=3){
    c=rnd->RanInt(1,cities-1);
    gen[s].mut_inv(c,rnd);
  }
}

void population :: generate(){
  int k, l;
  element one(cities), two(cities);
//pesco elementi nella vecchia generazione con roulette truccata, tento di mutarli e accoppiarli e li salvo nella nuova
  for (int i=0; i<n_element; i+=2){
    k=select();
    one.copy(gen[k]);
    if (rnd->Rannyu()<r_mut){
      mutate(k);
      gen[k].Length(x,y);
    }
    do{
      l=select();
    }while(l==k);
    two.copy(gen[l]);
    if (rnd->Rannyu()<r_mut){
      mutate(l);
      gen[l].Length(x,y);
    }

    if (rnd->Rannyu()<r_cross){
      crossover(l,k);
    }
    new_gen[i]=gen[k];
    new_gen[i+1]=gen[l];
    gen[k].copy(one);         //rimetto a posto elementi originari per non modificare l'ordine
    gen[l].copy(two);
  }
  //salvo nuova generazione in generazione attuale, e la ordino
  for(int i=0; i<n_element; i++){
    gen[i].copy(new_gen[i]);
    new_gen[i].clean();
  }
  order();
}

void population :: SaveBElem(int *a){
  for (int i=0; i<cities; i++){
    gen[0].SetCity(i,a[i]);
  }
}

void population :: GetBElem(int *a){
  for (int i=0; i<cities; i++){
    a[i]=gen[0].GetCity(i);
  }
}

double population :: GetAve(){
  int p=(int)n_element/2;
  double mean=0;
  for(int i=0; i<p; i++){
    mean+=gen[i].GetL();
  }
  return mean/=p;
}

void population :: PrintBest(int r){
  char *filename;
  if(r==0){
    filename=(char *)"B_coord.0";
  }
  if(r==1){
    filename=(char *)"B_coord.1";
  }
  if(r==2){
    filename=(char *)"B_coord.2";
  }
  if(r==3){
    filename=(char *)"B_coord.3";
  }
  ofstream fout(filename);
  int j=0;
  if(!fout) {
    cout<<"cannot open output_file"<<endl;
    exit(0);
     }
  for (int i=0; i<cities; i++){
    j=gen[0].GetCity(i)-1;
    fout <<x[j]<<"\t"<<y[j]<< endl;
  }
}
