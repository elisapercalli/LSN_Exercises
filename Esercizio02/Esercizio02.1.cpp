#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include "random.h"
#include "funzioni.h"
#include "integral.h"

using namespace std;

int main(){
  int M=pow(10,5);   //lanci totali
  int N=100;        //blocchi
  unsigned int L=M/N;
  vector <double> v(N,0), vsamp(N,0);
  Random *rnd=new Random();
  SetGen(rnd);
  funzione *cos=new funzione();
  funzione2 *cosSamp=new funzione2();
  integral monte(0,1,cos,rnd);

  for (int i=0; i<N; i++)     //calcolo integrale unif
    v[i]=monte.media(L);

  monte.SetFunction(cosSamp); //calcolo integrale imp samp
  for (int i=0; i<N; i++)
    vsamp[i]=monte.ImpSamp(L);

  //medie a blocchi e stampa
  Block_err integ (v,M,N);
  integ.Calc();
  char *filename=(char*) "integral.dat";
  integ.Print(filename);

  integ.SetVector(vsamp);
  integ.Calc();
  filename=(char*) "imp.samp.dat";
  integ.Print(filename);

  rnd->SaveSeed();

  return 0;
}
