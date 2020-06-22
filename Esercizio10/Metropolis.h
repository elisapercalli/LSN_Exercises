#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "random.h"
#include "element.h"
#define _USE_MATH_DEFINES

using namespace std;

void print (char *, vector<double>);

class Metropolis {
  private:
		element *x;
    double T;
    double acc;
    Random *R;

  public:
  Metropolis();
  Metropolis(element *p, Random* rand);
  ~Metropolis();
	void SetTemp(double p){T=p;};
  void SetSP(element *start);
  void Run();
  double Acc (void){return acc;};
	double GetL(){return x->GetL();};
	void Print(char *);

};
