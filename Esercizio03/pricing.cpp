#include "pricing.h"

using namespace std;


Pricing :: Pricing(){}
Pricing :: ~Pricing(){}
Pricing :: Pricing(double r, double s, double T, double K, double S0, Random *rnd){
  m_r=r;
  m_s=s;
  m_T=T;
  m_K=K;
  m_S0=S0;
  m_R=rnd;
}
double Pricing :: DirPrice(){
  double w=m_R->Gauss(0,m_T);
  double S=m_S0*exp(m_T*(m_r-0.5*m_s*m_s)+w*m_s);
  return S;
}
double Pricing :: DiscPrice(int nstep){
  double t=m_T/nstep;
  double Sold=m_S0;
  double Snew=0;
  vector <double> Z(nstep,0);
  for (int i=0; i<nstep; i++)
    Z[i]=m_R->Gauss(0,1);
  for(int i=0; i<nstep; i++){
    Snew=Sold*exp((m_r-0.5*m_s*m_s)*t+m_s*Z[i]*sqrt(t));
    Sold=Snew;
  }
  return Snew;
}
double Pricing :: PutDirect(){
  double S=DirPrice();
  double C=exp(-m_r*m_T)*max(0.,m_K-S);
  return C;
}
double Pricing :: PutDiscrete(int nstep){
  double S=DiscPrice(nstep);
  double C=exp(-m_r*m_T)*max(0.,m_K-S);
  return C;
}
double Pricing :: CallDirect(){
  double S=DirPrice();
  double C=exp(-m_r*m_T)*max(0.,S-m_K);
  return C;
}
double Pricing :: CallDiscrete(int nstep){
  double S=DiscPrice(nstep);
  double C=exp(-m_r*m_T)*max(0.,S-m_K);
  return C;
}
