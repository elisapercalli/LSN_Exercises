#ifndef __Random__
#define __Random__

class Random {

private:
  int m1,m2,m3,m4,l1,l2,l3,l4,n1,n2,n3,n4;
  double m_x, m_y;

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
  void RanAngle(double);
  double GetX(){return m_x;};
  double GetY(){return m_y;};
  int RanInt(int n, int x);
};

#endif // __Random__
void SetGen (Random *); //funzione per settare il seed del generatore
