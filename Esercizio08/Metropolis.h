#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "random.h"
#define _USE_MATH_DEFINES

using namespace std;

class distribution {
public:
	virtual	double eval(double x) const=0;
};

class trial: public distribution {
	private:
		double m_mu;
		double m_sigma;
	public:
		trial();
		trial(double mu, double sigma);
		~trial();
		virtual double eval (double x)const;
		void Set_mu(double m){m_mu=m;};
		void Set_sigma(double s){m_sigma=s;};
		void Set_par(double mu, double sigma);

};

//Metropolis 1D

class Metropolis {
  private:
    double x;
    double d, acc;
    distribution *P;
    Random *R;

  public:
  Metropolis();
  Metropolis(distribution *p, double delta, Random* rand);
  ~Metropolis();
	void SetPDF(distribution *p){P=p;};
  void SetDelta(double s) {d=s;};
  void SetSP(double start);
  void Equilibrate(int N);
  void RunU();
  double GetX (void) {return x;};
  double Acc (void){return acc;};

};
