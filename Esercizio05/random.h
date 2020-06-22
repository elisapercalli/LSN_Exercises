#ifndef __Random__
#define __Random__

class Random {

private:
  int m1,m2,m3,m4,l1,l2,l3,l4,n1,n2,n3,n4;
  int x,y,z;
  double teta, fi;

protected:

public:
  // constructors
  Random();
  // destructor
  ~Random();
  // methods
  void SetRandom(int * , int, int);
  void SaveSeed();
  double Rannyu(void);
  double Rannyu(double min, double max);
  double Gauss(double mean, double sigma);
  double Exp(double mean);
  double Lorentz(double loc, double scale);
  double prova();
  void RanSolidAngle();
  void RanWalk();
  double GetTeta() {return teta;};
  double GetFi() {return fi;};
  int GetX(){return x;};
  int GetY() {return y;};
  int GetZ() {return z;};
};

#endif // __Random__
void SetGen (Random *); //funzione per settare il seed del generatore
