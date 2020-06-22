#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include "random.h"
#include "element.h"
#include "Metropolis.h"

using namespace std;

int main() {
  int n_cit=32, N=2*pow(10,2), accu=0, Nmax=1000;
  double r=1, box=1, T0=150, T, old;
  Random *rand=new Random();
  vector <double> x_round,y_round, x_square, y_square, L;
  char *filename;
  SetGen(rand);

//settiamo le citta
  for (int i=0; i<n_cit; i++){
    x_square.push_back(rand->Rannyu(0,box));
    y_square.push_back(rand->Rannyu(0,box));
  }

  for(int i=0; i<n_cit; i++){
    rand->RanAngle(r);
    x_round.push_back(rand->GetX());
    y_round.push_back(rand->GetY());
  }

  element *circle=new element(n_cit, x_round, y_round);
  circle->SetStart();
  circle->Length();
  Metropolis SA(circle, rand);
  SA.SetTemp(T0);
  old=SA.GetL();
  T=T0;
  for(int j=0; j<N; j++){
    accu=0;
    for (int i=0; i<Nmax; i++){
      SA.Run();
      if(SA.GetL()==old){
        accu++;
      }else{
        accu=0;
      }
      old=SA.GetL();
      if(accu>=100)
        break;
    }
    L.push_back(SA.GetL());
    T*=0.9;
    SA.SetTemp(T);
  }

  filename=(char *)"L_round.dat";
  print(filename,L);
  filename=(char *)"coord_best_round.dat";
  SA.Print(filename);

  element *square=new element(n_cit, x_square, y_square);
  square->SetStart();
  square->Length();
  SA.SetSP(square);
  SA.SetTemp(T0);
  old=SA.GetL();
  T=T0;
  for(int j=0; j<N; j++){
    accu=0;
    for (int i=0; i<Nmax; i++){
      SA.Run();
      if(SA.GetL()==old){
        accu++;
      }else{
        accu=0;
      }
      old=SA.GetL();
      if(accu>=400)
        break;
    }
    L[j]=SA.GetL();
    T*=0.9;
    SA.SetTemp(T);
  }

  filename=(char *)"L_square.dat";
  print(filename,L);
  filename=(char *)"coord_best_square.dat";
  SA.Print(filename);

  //2284 3775 29 2118
  rand->SaveSeed();
  return 0;
}
