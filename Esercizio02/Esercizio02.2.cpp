#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include "random.h"
#include "funzioni.h"

using namespace std;
int main(){
  Random *rnd=new Random();
  SetGen(rnd);
  int M=10000;        //numero totale di random walk
  int S=100;          //numero massimo di step per random walk
  int N=100;          //numero di blocchi per fare le medie
  Block_err walk(M,N);
  vector <double> x(M,0), y(M,0), z(M,0), r2(M,0), rm(S,0),err(S,0);

//Discrete walk
  for (int i=0; i<S; i++){
    for(int j=0; j<M; j++){
      rnd->RanWalk();
      x[j]+=rnd->GetX();
      y[j]+=rnd->GetY();
      z[j]+=rnd->GetZ();
      r2[j]=x[j]*x[j]+y[j]*y[j]+z[j]*z[j];
    }
    walk.SetAve(r2);
    walk.Calc();
    rm[i]=sqrt(walk.GetMean());
    err[i]=walk.GetErr()*0.5/rm[i];
  }
  char *filename=(char*) "DiscreteWalk.dat";
  print2(filename,rm,err);

//Continous walk
x.assign(M,0);
y.assign(M,0);
z.assign(M,0);
  for (int i=0; i<S; i++){
    for(int j=0; j<M; j++){
      rnd->RanSolidAngle();
      x[j]+=sin(rnd->GetTeta())*cos(rnd->GetFi());
      y[j]+=sin(rnd->GetTeta())*sin(rnd->GetFi());
      z[j]+=cos(rnd->GetFi());
      r2[j]=x[j]*x[j]+y[j]*y[j]+z[j]*z[j];
    }
    walk.SetAve(r2);
    walk.Calc();
    rm[i]=sqrt(walk.GetMean());
    err[i]=walk.GetErr()*0.5/rm[i];
  }
  filename=(char*) "ContinousWalk.dat";
  print2(filename,rm,err);

  return 0;
}
