#include <cmath>
#include <cstdlib>
#include <string>
#include "random.h"
#include "funzioni.h"
#include <vector>

using namespace std;

int main(){

  Random* rnd=new Random();
  SetGen(rnd);
  int r=10000;
  int N;
  char *filename;
  vector <double> vs1, vs2, vs10, vs100, ve1, ve2, ve10, ve100, vl1, vl2, vl10, vl100;
  vs1.assign(r,0);
  vs2.assign(r,0);
  vs10.assign(r,0);
  vs100.assign(r,0);
  ve1.assign(r,0);
  ve2.assign(r,0);
  ve10.assign(r,0);
  ve100.assign(r,0);
  vl1.assign(r,0);
  vl2.assign(r,0);
  vl10.assign(r,0);
  vl100.assign(r,0);

  for (int i=0; i<r; i++){      //ciclo che lo rifà 10^4 volte
    N=1;                        //Primo giro per N=1
    vs1[i]=rnd->Rannyu();
    ve1[i]=rnd->Exp(1);
    vl1[i]=rnd->Lorentz(0,1);
    
    N=2;                        //Primo ciclo per N=2
    for(int j=0; j<N; j++){
      vs2[i]+=(rnd->Rannyu())/N;
      ve2[i]+=(rnd->Exp(1))/N;
      vl2[i]+=(rnd->Lorentz(0,1))/N;
    }
    N=10;                       //Primo ciclo per N=10
    for(int j=0; j<N; j++){
      vs10[i]+=(rnd->Rannyu())/N;
      ve10[i]+=(rnd->Exp(1))/N;
      vl10[i]+=(rnd->Lorentz(0,1))/N;
    }
    N=100;                       //Primo ciclo per N=100
    for(int j=0; j<N; j++){
      vs100[i]+=(rnd->Rannyu())/N;
      ve100[i]+=(rnd->Exp(1))/N;
      vl100[i]+=(rnd->Lorentz(0,1))/N;
    }
  }
  filename=(char*) "standard.dat";
  print4(filename,vs1, vs2, vs10, vs100);
  filename=(char*) "exponential.dat";
  print4(filename,ve1, ve2, ve10, ve100);
  filename=(char*) "lorentz.dat";
  print4(filename,vl1, vl2, vl10, vl100);

  return 0;
}
