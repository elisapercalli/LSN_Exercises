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
  trial *gs=new trial();

  int M=2*pow(10,5), N=100, block, L=M/N;
  double jump=1.5, x0=0, x, mean, mu, sigma, energy, ave_en, en_min=0, mu_min, sigma_min;
  char *filename1=(char *)"output.energy";

  Block_err varGS(M,N);
  Metropolis MCMC(gs, jump, rnd);

  sigma=0.5;

  for (int j=0; j<5; j++){ //ciclo sui sigma
    gs->Set_sigma(sigma);
    mu=0.5;
    for (int k=0; k<10; k++){ //ciclo sui mu
      block=0;
      mean=0;
      gs->Set_mu(mu);
      MCMC.SetSP(x0);
      MCMC.Equilibrate(100);
      for (int i=1; i<=M; i++){
        MCMC.RunU();
        x=MCMC.GetX();
        energy=Ham(x,mu,sigma);
        mean+=energy/L;
        if(i%L==0){
          varGS.SetAve(mean, block);
          varGS.Calc(block);
          block++;
          mean=0;
        }
      }
      ave_en=varGS.GetMean();
      cout<<"sigma: "<<sigma<<"\t"<<"mu: "<<mu<<"\t"<<"energia media: "<<ave_en<<endl;
      //varGS.Print(filename1);
      varGS.Reset();
      cout <<"Accettanza del "<<MCMC.Acc()/M*100<< " %"<<endl;
      if(ave_en<en_min){
        en_min=ave_en;
        mu_min=mu;
        sigma_min=sigma;
      }
      mu+=0.05;
    }
    jump+=0.25;
    sigma+=0.05;
  }
  cout<<"sigma: "<<sigma_min<<"\t"<<"mu: "<<mu_min<<"\t"<<"energia media: "<<en_min<<endl;


//sigma=0.62 mu=0.795

//rnd->SaveSeed();
//2284 3775 29 2118
//282 1276 2960 3377
//2018 2415 3433 2674

  return 0;
}
