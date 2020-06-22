#include "element.h"

element :: element(){}

element :: element(int p, vector<double> x0, vector<double> y0){
  n_cities =p;
  path.assign(n_cities,0);
  L=0;
  for (int i=0; i<n_cities; i++){
    x.push_back(x0[i]);
    y.push_back(y0[i]);
  }
}

element :: element(element *old){
  n_cities=old->GetN();
  for(int i=0; i<n_cities; i++){
    x.push_back(old->GetX(i));
    y.push_back(old->GetY(i));
    path.push_back(old->GetCity(i));
  }
}

element :: ~element(){}

void element :: SetStart(){
  for (int i=0; i<n_cities; i++){
    path[i]=i+1;
  }
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

void element :: mutate(Random * rnd){
  int i=rnd->Rannyu(0,4);
  int c, d;
  if(i<1){
    c=rnd->RanInt(1,n_cities);
    do {
      d=rnd->RanInt(1,n_cities);
    }while(c==d);
    perm(c,d);
  }
  if(i>=1 && i<2){
    c=rnd->RanInt(1,n_cities-1);
    d=rnd->RanInt(1,n_cities-2);
    mut_shift(c,d,rnd);
  }
  if(i>=2 && i<3){
    c=rnd->RanInt(1,n_cities/2);
    mut_cont(c,rnd);
  }
  if(i>=3){
    c=rnd->RanInt(1,n_cities-1);
    mut_inv(c,rnd);
  }
}


void element :: Length(){
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
