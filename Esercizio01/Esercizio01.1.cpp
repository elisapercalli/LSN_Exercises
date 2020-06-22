#include <cmath>
#include <cstdlib>
#include <string>
#include "random.h"
#include "funzioni.h"
#include <vector>
#include <algorithm>

using namespace std;

//esercizio 01.1 parte 1
int main() {
   Random *rnd=new Random();
   SetGen (rnd);
   int M=100000;
   int N=100;
   int L=M/N;
   vector <double> r(M),ave(N),x;
   for (int i=0; i<M; i++)
     r[i]=rnd->Rannyu();
   for (int i=0; i<N; i++)
     x.push_back(i*M/N);
   double sum;
    for (int i=0; i<N; i++){
     sum=0;
     int k=0;
     for (int j=0; j<L; j++){
       k=j+i*L;
       sum +=r[k];
     }
     ave[i]=sum/L;
   }

   Block_err unif(ave,M,N); //classe che calcola la media a blocchi
   unif.Calc();

   //stampa dei risultati
   char *filename1=(char*) "x.dat";
   char *filename2=(char*) "stat.dat";
   print(filename1, x);
   unif.Print(filename2);

   //esercizio 01.1 parte 2
   for (int i=0; i<N; i++){
    sum=0;
    int k=0;
    for (int j=0; j<L; j++){
      k=j+i*L;
      sum +=pow(r[k]-0.5,2);
    }
    ave[i]=sum/L;
   }
   unif.SetVector(ave);
   unif.Calc();
   filename1=(char*) "stat2.dat";
   unif.Print(filename1);

   //esercizio 01.1 parte 3 (chi quadro)
   Random *rnd1=new Random(); //uso un nuovo generatore per tenere separati i due conti, per riproducibilità
   SetGen (rnd1);
   M=100;
   int n=10000;
   vector<double> v1(n), vn(M), X(M);
   X.assign(M,0);

   for (int j=0; j<M; j++){     //ciclo che rifà tutto 100 volte
     for (int i=0; i<n; i++){   //ciclo che setta i 10^4 numeri casuali
       v1[i]=rnd1->Rannyu();
     }
     vn.assign(M,0);             //riempio vn di zeri
     sort(v1.begin(),v1.end());  //ordino i numeri casuali per poterli contare
     int l=0;
     for (int i=0; i<M; i++){   //ciclo che fa scorrere gli intervalli e conta
        while(v1[l]>=(double)i/M && v1[l]<(double)(i+1)/M && l<n){
          vn[i]+=1;
          l++;
        }
        X[j]+=pow((vn[i]-100),2)/100; //calcolo chi quadro j-esimo
     }
   }
   filename1=(char*) "CHI.dat"; //  stampo su filename
   print (filename1, X);

   return 0;
 }
