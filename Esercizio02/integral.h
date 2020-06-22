#include <cstdlib>
#include <cmath>
#include <vector>
#include "random.h"
#define _USE_MATH_DEFINES


using namespace std;

class funzionebase {
public:
virtual	double eval(double x) const=0;
};

class funzione: public funzionebase {
public:
	funzione();
	~funzione();
	virtual double eval (double x) const {return (0.5*M_PI*cos(0.5*M_PI*x));};
private:
	double m_a,m_b;
};

class funzione2: public funzionebase {
public:
	funzione2();
	~funzione2();
	virtual double eval (double x) const {return (0.25*M_PI*cos(0.5*M_PI*x)/(1-x));};
private:
	double m_a,m_b;
};

class integral {
public:
	integral (double a, double b, Random *r);
	integral (double a, double b, funzionebase* f, Random *r);
	void setA(double a){m_a=a;};
	void setB(double b){m_b=b;};
	void SetFunction(funzionebase *f){m_f=f;};
	double simpson(unsigned int nstep);
	double simpson(double prec);
	double media (unsigned int nstep);
	double ImpSamp(unsigned int nstep);
	double hitmiss (unsigned int nstep, double max);
	double getH(){return m_h;};

private:
	double m_a, m_b;
	double m_sum;
	double m_h;
	int m_sign;
	double m_integral;
	funzionebase *m_f;
	double m_prec;
	Random *m_R;
};
