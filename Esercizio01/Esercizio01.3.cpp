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
  int M=100000;    //numero di lanci
  int N=100;       //numero di blocchi in cui divido i lanci
  int P=M/N;       //numero di lanci in ogni blocco
  vector<double> PI(N);
  int hit=0;
  double y0,L,d,teta,y1,y2;
  L=5;  //lunghezza sbarretta
  d=8;  //lunghezza cella

  for (int i=0; i<N; i++){         //ciclo su tutti i blocchi
    hit=0;
    for (int k=0; k<P; k++){        //ciclo che fa P lanci
      teta=Teta(rnd);               //genero angolo
      y0=rnd->Rannyu(0,d);          //genero punto
      y1=y0-(0.5*L*sin(teta));      //calcolo y degli estremi della barretta
      y2=y0+(0.5*L*sin(teta));
      if(y2<y1){
        double appo=y2;
        y2=y1;
        y1=appo;
      }
      if (y1<=0 || y2 >=d)          //confronto barretta con righe
        hit++;
    }
    PI[i]=2*L*P/(d*hit);            //Calcolo PI
  }
  Block_err greco(PI, M, N);
  greco.Calc();
  char *filename=(char*) "PI.dat";
  greco.Print(filename);

  return 0;
}
