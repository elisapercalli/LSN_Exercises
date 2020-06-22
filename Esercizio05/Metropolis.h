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
	virtual	double eval(vector <double> x) const=0;
};

class prob_1s: public distribution {
public:
	prob_1s();
	~prob_1s();
	virtual double eval (vector <double> x)const;
private:
};

class pdf_2p: public distribution {
public:
	pdf_2p();
	~pdf_2p();
	virtual double eval (vector <double> x) const;
private:
};

class Metropolis {
  private:
    vector <double> x;
    double d, acc;
    int dim;
    distribution *P;
    Random *R;

  public:
  Metropolis();
  Metropolis(distribution *p, double delta, Random* rand, int N);
  ~Metropolis();
	void SetPDF(distribution *p){P=p;};
  void SetDelta(double s) {d=s;};
  void SetDim(int N){dim=N;};
  void SetSP(vector <double> start);
  void EquilibrateU(int N);
	void EquilibrateG(int N);
  void RunU();
  void RunG();
  double GetX (void) {return x[0];};
  double GetY (void) {return x[1];};
  double GetZ (void) {return x[2];};
  double Getr (void);
  double Acc (void){return acc;};

};
