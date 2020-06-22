#include "Metropolis.h"

prob_1s :: prob_1s(){
};
prob_1s :: ~prob_1s(){
};

double prob_1s:: eval(vector <double> x)const{
	double r=sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
	return pow(M_E,-2*r)/M_PI;
}
pdf_2p :: pdf_2p(){
};
pdf_2p :: ~pdf_2p(){
};

double pdf_2p:: eval(vector <double> x)const {
	double r=sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
	return x[2]*x[2]*pow(M_E,-r)/(32*M_PI);
}

Metropolis :: Metropolis (){}
Metropolis :: ~Metropolis(){}
Metropolis :: Metropolis (distribution *p, double delta, Random* rand, int N){
  P=p;
  d=delta;
  R=rand;
  dim=N;
  acc=0;
}
void Metropolis :: SetSP(vector <double> start){
  x.assign(dim,0);
  for (int i=0; i<dim; i++)
    x[i]=start[i];
  acc=0;
}
double Metropolis:: Getr (void){
  double accu=0;
  for(int i=0; i<dim; i++)
    accu+=x[i]*x[i];
  return sqrt(accu);
}
void Metropolis :: EquilibrateU (int N){
  for (int i=0; i<N; i++)
    RunU();
	acc=0;
}
void Metropolis :: EquilibrateG (int N){
  for (int i=0; i<N; i++)
    RunG();
	acc=0;
}
void Metropolis :: RunU(){
  vector <double> prop(dim);
  double A, appo, dist;
  do {
    appo=0;
    dist=0;
    for (int i=0; i<dim; i++){
      prop[i]=R->Rannyu(x[i]-d, x[i]+d);
      dist=prop[i]-x[i];
      appo+=(dist*dist);
    }
  } while(sqrt(appo)>d);
  A=min(1. ,P->eval(prop)/P->eval(x));
  double r=R->Rannyu();
  if (r<A){
    for(int i=0; i<dim; i++)
      x[i]=prop[i];
    acc+=1;
  }
}
void Metropolis :: RunG(){
  vector <double> prop(dim);
  double A, appo, dist;
  appo=0;
  dist=0;
  for (int i=0; i<dim; i++){
    prop[i]=R->Gauss(x[i],d);
    dist=prop[i]-x[i];
    appo+=(dist*dist);
  }
  A=min(1. ,P->eval(prop)/P->eval(x));
  double r=R->Rannyu();
  if (r<A){
    for(int i=0; i<dim; i++)
      x[i]=prop[i];
    acc+=1;
  }
}
