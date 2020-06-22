#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "random.h"

#ifndef __Pricing__
#define __Pricing__

class Pricing {
private:
  double m_r, m_s, m_T, m_K, m_S0;
  Random *m_R;

public:
  Pricing();
	~Pricing();
  Pricing(double r, double s, double T, double K, double S0, Random *rnd);
  double DirPrice();    //funzione che prezza direttamente
  double DiscPrice(int nstep);    //funzione che prezza discretamente
  //applicazioni funzioni precedenti alla put e la call
  double PutDirect();
  double PutDiscrete(int nstep);
  double CallDirect();
  double CallDiscrete(int nstep);
};

#endif
