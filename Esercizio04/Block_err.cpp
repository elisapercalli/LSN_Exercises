#include "Block_err.h"

using namespace std;
double DevSt (const vector <double> av, const vector <double> av2, int n){
  if (n==0)
    return 0;
  else{
    return sqrt((av2[n]-pow(av[n],2))/(n+1));
  }
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
  ave.assign(N,0);
  av2.assign(N,0);
  sum_prog.assign(N,0);
  su2_prog.assign(N,0);
  err_prog.assign(N,0);
}
void Block_err :: SetAve(double r, int n){
  ave[n]=r;
  av2[n]=pow(ave[n],2);
}
void Block_err :: Calc(int n){
  for (int j=0; j<n+1; j++){
    sum_prog[n]+=ave[j];
    su2_prog[n]+=av2[j];
  }
  sum_prog[n]/=(n+1);
  su2_prog[n]/=(n+1);
  err_prog[n]= DevSt(sum_prog, su2_prog, n);
}
void Block_err :: Print(char * filename, int i){
    ofstream fout(filename, ios::app);
  if(!fout) {
    cout<<"cannot open output_file"<<endl;
    exit(0);
     }
  fout <<setprecision(10)<<sum_prog[i]<< "\t"<<err_prog[i]<< endl;
}
