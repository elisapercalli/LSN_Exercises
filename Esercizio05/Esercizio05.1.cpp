#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include "random.h"
#include "Metropolis.h"
#include "Block_err.h"

using namespace std;

int main() {
  Random *rnd=new Random();
  SetGen(rnd);
  prob_1s *ps=new prob_1s();
  pdf_2p *pp=new pdf_2p();

  int n=3, M=pow(10,7), N=1000, block=0, L=M/N;
  double jump=1.5, var=0.7, ri, mean=0, ri2, mean2=0;
  char *filename1=(char *)"groundstateU.dat";
  char *filename2=(char *)"groundstateG.dat";
  vector <double> x0{3,3,3}, x1{7,7,7};

  Block_err hydrogenU(M,N);
  Block_err hydrogenG(M,N);
  Metropolis MCMC(ps, jump, rnd, n);
  Metropolis MCMCgauss(ps, var, rnd, n);

//orbitale 1s
  MCMC.SetSP(x0);

  MCMC.EquilibrateU(200);
  MCMCgauss.SetSP(x0);
  MCMCgauss.EquilibrateG(400);
  for (int i=1; i<=M; i++){
    MCMC.RunU();
    ri=MCMC.Getr();
    mean+=ri/L;
    MCMCgauss.RunG();
    ri2=MCMCgauss.Getr();
    mean2+=ri2/L;
    if(i%L==0){
      hydrogenU.SetAve(mean, block);
      hydrogenU.Calc(block);
      //hydrogenU.Print(filename1, block);
      hydrogenG.SetAve(mean2, block);
      hydrogenG.Calc(block);
      //hydrogenG.Print(filename2,block);
      if(block%10==0){
        hydrogenU.Print(filename1, block);
        hydrogenG.Print(filename2,block);
      }
      block++;
      mean=0;
      mean2=0;
    }
  }
  cout <<"Unif 1s: accettanza del "<<MCMC.Acc()/100000<< " %"<<endl;
  cout <<"Gauss 1s: accettanza del "<<MCMCgauss.Acc()/100000<< " %"<<endl;

//Orbitale 2p
  filename1=(char *)"excitedstateU.dat";
  filename2=(char *)"excitedstateG.dat";
  block =0;
  mean=0;
  mean2=0;
  hydrogenU.SetBlock(M,N);
  hydrogenG.SetBlock(M,N);
  MCMC.SetPDF(pp);
  MCMC.SetSP(x1);
  MCMC.SetDelta(3.5);
  MCMC.EquilibrateU(200);
  MCMCgauss.SetPDF(pp);
  MCMCgauss.SetSP(x1);
  MCMCgauss.SetDelta(1.8);
  MCMCgauss.EquilibrateG(400);
  for (int i=1; i<=M; i++){
    MCMC.RunU();
    ri=MCMC.Getr();
    mean+=ri/L;
    MCMCgauss.RunG();
    ri2=MCMCgauss.Getr();
    mean2+=ri2/L;
    if(i%L==0){
      hydrogenU.SetAve(mean, block);
      hydrogenU.Calc(block);
    //  hydrogenU.Print(filename1, block);
      hydrogenG.SetAve(mean2, block);
      hydrogenG.Calc(block);
      //hydrogenG.Print(filename2,block);
      if(block%10==0){
        hydrogenU.Print(filename1, block);
        hydrogenG.Print(filename2,block);
      }
      block++;
      mean=0;
      mean2=0;
    }
  }
  cout <<"Unif 2p: accettanza del "<<MCMC.Acc()/100000<< " %"<<endl;
  cout <<"Gauss 2p: accettanza del "<<MCMCgauss.Acc()/100000<< " %"<<endl;

  return 0;
}
