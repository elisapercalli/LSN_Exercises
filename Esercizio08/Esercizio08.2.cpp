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

  int M=pow(10,6), N=100, block=0, L=M/N;
  double jump=2.5, x0=0, x, mean=0, mu, sigma, energy;
  char *filename1=(char *)"output.energy";
  char *filename2=(char *)"output.radius";
  // prepare histo
  int nbins=100;
  double x_min=-2.5, x_max=2.5, bin_size=(x_max-x_min)/(double)nbins;
  vector <double> r(nbins,0);

  Block_err varGS(M,N);
  Metropolis MCMC(gs, jump, rnd);

  sigma=0.62;
  mu=0.795;
  gs->Set_par(mu,sigma);
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
    for(int j=0; j<nbins; j++){
      if(x>x_min+j*bin_size && x<=x_min+(j+1)*bin_size)
        r[j]+=1;
    }
  }
  varGS.Print(filename1);
  cout <<"Accettanza del "<<MCMC.Acc()/M*100<< " %"<<endl;

  //normalization of histo
  for(int i=0; i<nbins; i++)
    r[i]/=(M*bin_size);
  print(filename2, r);

  return 0;
}
