#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include "random.h"
#include "funzioni.h"
#include "pricing.h"

using namespace std;

int main(){
  //inizializzazione variabili
  int M=100000;     //total of simulations
  int N=100;        //number of blocks
  int Nstep=100;    //steps per il calcolo discretizzato
  double S=100;     //asset price (S(0))
  double T=1;       //delivery time
  double K=100;     //strike price
  double r=0.1;     //risk-free interest rate
  double s=0.25;    //volatility (sigma)
  vector<double> C1p(M,0), C1c(M,0), C2p(M,0), C2c(M,0);
  Random *rnd=new Random();
  SetGen(rnd);
  Block_err price(M,N);
  Pricing europe(r,s,T,K,S,rnd);

//calcolo dei prezzi
  for (int i=0; i<M; i++){
    C1p[i]=europe.PutDirect();
    C2p[i]=europe.PutDiscrete(Nstep);
    C1c[i]=europe.CallDirect();
    C2c[i]=europe.CallDiscrete(Nstep);
  }

//calcolo media a blocchi e stampo
  char *filename=(char*) "DirectPut.dat";
  price.SetAve(C1p);
  price.Calc();
  price.Print(filename);
  filename=(char*) "DiscretePut.dat";
  price.SetAve(C2p);
  price.Calc();
  price.Print(filename);
  filename=(char*) "DirectCall.dat";
  price.SetAve(C1c);
  price.Calc();
  price.Print(filename);
  filename=(char*) "DiscreteCall.dat";
  price.SetAve(C2c);
  price.Calc();
  price.Print(filename);
  rnd->SaveSeed();
  return 0;
}
