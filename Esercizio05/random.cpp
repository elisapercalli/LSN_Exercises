#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "random.h"
#define _USE_MATH_DEFINES

using namespace std;

Random :: Random(){}

Random :: ~Random(){}

void Random :: SaveSeed(){
   ofstream WriteSeed;
   WriteSeed.open("seed.out");
   if (WriteSeed.is_open()){
      WriteSeed << l1 << " " << l2 << " " << l3 << " " << l4 << endl;;
   } else cerr << "PROBLEM: Unable to open random.out" << endl;
  WriteSeed.close();
  return;
}

double Random :: Exp(double mean){
  double appo=Rannyu();
  return (-1/mean*log(1-appo));
}

double Random :: Lorentz(double loc, double scale){
  double p=Rannyu();
  return loc+(scale*tan(M_PI*(p-0.5)));
}

double Random :: Gauss(double mean, double sigma) {
   double s=Rannyu();
   double t=Rannyu();
   double x=sqrt(-2.*log(1.-s))*cos(2.*M_PI*t);
   return mean + x * sigma;
}

double Random :: prova(){
  double y=Rannyu();
  return 1-pow((1-y),0.5);
}

double Random :: Rannyu(double min, double max){
   return min+(max-min)*Rannyu();
}

double Random :: Rannyu(void){
  const double twom12=0.000244140625;
  int i1,i2,i3,i4;
  double r;

  i1 = l1*m4 + l2*m3 + l3*m2 + l4*m1 + n1;
  i2 = l2*m4 + l3*m3 + l4*m2 + n2;
  i3 = l3*m4 + l4*m3 + n3;
  i4 = l4*m4 + n4;
  l4 = i4%4096;
  i3 = i3 + i4/4096;
  l3 = i3%4096;
  i2 = i2 + i3/4096;
  l2 = i2%4096;
  l1 = (i1 + i2/4096)%4096;
  r=twom12*(l1+twom12*(l2+twom12*(l3+twom12*(l4))));

  return r;
}

void Random :: RanSolidAngle(){
  double x,y,z;
  do {
    x=Rannyu(-1,1);
    y=Rannyu(-1,1);
    z=Rannyu(-1,1);
  } while(sqrt(x*x+y*y+z*z)>1);
  teta=atan2(pow(x*x+y*y,0.5),z);
  fi=atan2(y,x)+M_PI;
}

void Random :: RanWalk(){
  double r=Rannyu(0,3);
  double s=Rannyu(-1,1);
  int sum=1;
  if (s<0)
    sum=-1;
  if (r<1) {
    x=sum;
    y=0;
    z=0;
  } else {
    if (r<2) {
      x=0;
      y=sum;
      z=0;
    } else{
      x=0;
      y=0;
      z=sum;
    }
  }
}

void Random :: SetRandom(int * s, int p1, int p2){
  m1 = 502;
  m2 = 1521;
  m3 = 4071;
  m4 = 2107;
  l1 = s[0]%4096;
  l2 = s[1]%4096;
  l3 = s[2]%4096;
  l4 = s[3]%4096;
  l4 = 2*(l4/2)+1;
  n1 = 0;
  n2 = 0;
  n3 = p1;
  n4 = p2;

  return;
}
void SetGen (Random *rnd){
  int seed[4];
  int p1, p2;
  ifstream Primes("Primes");
  if (Primes.is_open()){
     Primes >> p1 >> p2 ;
  } else cerr << "PROBLEM: Unable to open Primes" << endl;
  Primes.close();

  ifstream input("seed.in");
  string property;
  if (input.is_open()){
     while ( !input.eof() ){
        input >> property;
        if( property == "RANDOMSEED" ){
           input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
           rnd->SetRandom(seed,p1,p2);
        }
     }
     input.close();
  } else cerr << "PROBLEM: Unable to open seed.in" << endl;
}
