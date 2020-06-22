#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include "random.h"
#include "functions.h"

using namespace std;

int main() {
  int n_cit, pop, N;
  double r, box, m_prob, c_prob;
  Random *rand=new Random();
  vector <double> x_round,y_round, x_square, y_square, L1, L_ave1, L2, L_ave2;
  char *filename;
  SetGen(rand);

	ifstream input_file("input.dat");
	input_file >> n_cit;
	input_file >> r;
	input_file  >> box;
	input_file >> m_prob;
	input_file >> c_prob;
	input_file >> pop;
	input_file  >> N;
	input_file.close();

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

//settiamo la popolazione con citta nel cerchio
  population TSP1(pop, n_cit, x_round, y_round, rand);
  TSP1.SetProb(m_prob, c_prob);
  TSP1.start();
  for(int i=0; i<N; i++){
    TSP1.generate();
    L1.push_back(TSP1.GetBest());
    L_ave1.push_back(TSP1.GetAve());
  }

//settiamo la popolazione con città nel quadrato
  population TSP2(pop, n_cit, x_square, y_square, rand);
  TSP2.SetProb(m_prob, c_prob);
  TSP2.start();
  for(int i=0; i<N; i++){
    TSP2.generate();
    L2.push_back(TSP2.GetBest());
    L_ave2.push_back(TSP2.GetAve());
  }

//stampa delle lunghezze e dei best path
  filename=(char *)"L_round.dat";
  print(filename,L1);
  filename=(char *)"L_ave_round.dat";
  print(filename,L_ave1);
  filename=(char *)"L_square.dat";
  print(filename,L2);
  filename=(char *)"L_ave_square.dat";
  print(filename,L_ave2);
  filename=(char *)"coord_best_round.dat";
  TSP1.PrintBest(filename);
  filename=(char *)"coord_best_square.dat";
  TSP2.PrintBest(filename);

  //2284 3775 29 2118
  rand->SaveSeed();
  return 0;
}
