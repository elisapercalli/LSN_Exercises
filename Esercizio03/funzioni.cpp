#include "funzioni.h"

using namespace std;
double DevSt (const vector <double> av, const vector <double> av2, int n){
  if (n==0)
    return 0;
  else{
    return sqrt((av2[n]-pow(av[n],2))/(n+1));
  }
}
void SetGen (Random *rnd){
  int seed[4];
  int p1, p2;
  ifstream Primes("Primes");
  if (Primes.is_open()){
     Primes >> p1 >> p2 ;
  } else cerr << "PROBLEM: Unable to open Primes" << endl;
  Primes.close();

  ifstream input("seed.in");
  string property;
  if (input.is_open()){
     while ( !input.eof() ){
        input >> property;
        if( property == "RANDOMSEED" ){
           input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
           rnd->SetRandom(seed,p1,p2);
        }
     }
     input.close();
  } else cerr << "PROBLEM: Unable to open seed.in" << endl;
}
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

Block_err :: Block_err(){
  M=0;
  N=0;
}
Block_err :: ~Block_err(){}
Block_err :: Block_err(vector <double> r, int m, int n){
  M=m;
  N=n;
  L=int(M/N);
  for(int i=0; i< N; i++){
    ave.push_back(r[i]);
    av2.push_back(pow(r[i],2));
  }
  sum_prog.assign(N,0);
  su2_prog.assign(N,0);
  err_prog.assign(N,0);
}
Block_err :: Block_err(int m, int n){
  M=m;
  N=n;
  L=M/N;
  ave.assign(N,0);
  av2.assign(N,0);
  sum_prog.assign(N,0);
  su2_prog.assign(N,0);
  err_prog.assign(N,0);
}
void Block_err :: SetBlock(int m, int n){
  M=m;
  N=n;
  L=int(M/N);
}
void Block_err :: SetVector(vector<double> r){
  if (M==0 or N==0)
  cerr<< "you have to set the blocks before"<<endl;
  else {
    ave.assign(N,0);
    for(int i=0; i< N; i++){
      ave[i]=r[i];
      av2[i]=pow(r[i],2);
    }
    sum_prog.assign(N,0);
    su2_prog.assign(N,0);
    err_prog.assign(N,0);
  }
}
void Block_err :: SetAve(vector<double> r){
  double sum;
   for (int i=0; i<N; i++){
    sum=0;
    int k=0;
    for (int j=0; j<L; j++){
      k=j+i*L;
      sum +=r[k];
    }
    ave[i]=sum/L;
    av2[i]=pow(ave[i],2);
  }
  sum_prog.assign(N,0);
  su2_prog.assign(N,0);
  err_prog.assign(N,0);
}
void Block_err :: Calc(){
  for (int i=0; i<N; i++){
    for (int j=0; j<i+1; j++){
      sum_prog[i]+=ave[j];
      su2_prog[i]+=av2[j];
    }
    sum_prog[i]/=(i+1);
    su2_prog[i]/=(i+1);
    err_prog[i]= DevSt(sum_prog, su2_prog, i);
  }
  mean=sum_prog[N-1];
  error=err_prog[N-1];
}
double Block_err :: GetMean(){
  return mean;
}
double Block_err :: GetErr(){
  return error;
}
void Block_err :: Print(char * filename){
  ofstream fout(filename);
  if(!fout) {
    cout<<"cannot open output_file"<<endl;
    exit(0);
     }
  for (int i=0; i<N; i++)
    fout <<sum_prog[i]<< "\t"<<err_prog[i]<< endl;
}
