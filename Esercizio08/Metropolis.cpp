#include "Metropolis.h"

trial :: trial(){
}
trial :: trial(double mu, double sigma){
	m_mu=mu;
	m_sigma=sigma;
}
trial :: ~trial(){
}
void trial :: Set_par(double mu, double sigma){
	m_mu=mu;
	m_sigma=sigma;
}
double trial:: eval(double x)const{
	double p=exp(-pow(x-m_mu,2)/(2*m_sigma*m_sigma))+exp(-pow(x+m_mu,2)/(2*m_sigma*m_sigma));
	return p*p;
}

Metropolis :: Metropolis (){}
Metropolis :: ~Metropolis(){}
Metropolis :: Metropolis (distribution *p, double delta, Random* rand){
  P=p;
  d=delta;
  R=rand;
  acc=0;
}
void Metropolis :: SetSP(double start){
	x=start;
  acc=0;
}

void Metropolis :: Equilibrate (int N){
  for (int i=0; i<N; i++)
    RunU();
	acc=0;
}

void Metropolis :: RunU(){
  double prop;
  double A;
  prop=R->Rannyu(x-d, x+d);
  A=min(1. ,P->eval(prop)/P->eval(x));
  double r=R->Rannyu();
  if (r<A){
    x=prop;
    acc+=1;
  }
}
