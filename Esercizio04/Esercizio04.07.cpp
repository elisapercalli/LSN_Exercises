#include "Esercizio04.07.h"
using namespace std;

int main(){
  Input();             //Inizialization
  int nconf = 1;
  for(int istep=1; istep <= nstep; ++istep){
     Move();           //Move particles with Verlet algorithm
     if(istep%iprint == 0) cout << "Number of time-steps: " << istep << endl;
     if(istep%10 == 0){
        Measure();     //Properties measurement
//        ConfXYZ(nconf);//Write actual configuration in XYZ format //Commented to avoid "filesystem full"!
        nconf += 1;
     }
     if(istep%(10*L) == 0){
       MeasureAve();
       nblock+=1;
     }
  }
  Gofr(nblock-1);
  ConfFinal();         //Write final configuration to restart

  return 0;
}
