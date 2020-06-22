#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include "random.h"
#include "mpi.h"
#include "functions.h"

using namespace std;

int main(int argc, char* argv[]) {
  int size, rank;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Status stat1, stat2, stat3, stat4;
  MPI_Request req;

  int n_cit, pop, N, Nex;
  double r, box, m_prob, c_prob;
  Random *rand=new Random();
  Random *Rsame=new Random();
  vector <double> x_square, y_square, L, L_ave1;
  int *Bsend, *Brec, *order;
  int itag1=1, itag2=2, itag3=3, itag4=4;
  //char *filename;
  SetGen(Rsame);            //generatore uguale per tutti (per settare le città e l'ordine di scambio)

	ifstream input_file("input.dat");
	input_file >> n_cit;
	input_file  >> box;
	input_file >> m_prob;
	input_file >> c_prob;
	input_file >> pop;
	input_file  >> N;
  input_file  >> Nex;
	input_file.close();

  //settiamo le citta
  for (int i=0; i<n_cit; i++){
    x_square.push_back(Rsame->Rannyu(0,box));
    y_square.push_back(Rsame->Rannyu(0,box));
  }

  Bsend=new int[n_cit];
  Brec=new int[n_cit];
  order=new int[size];
  for (int i=0; i<size; i++)
    order[i]=i;

  SetGen(rand, rank);         //generatore differenziato

//settiamo la popolazione con città nel quadrato
  population TSP(pop, n_cit, x_square, y_square, rand);
  TSP.SetProb(m_prob, c_prob);
  TSP.start();
  for(int i=0; i<N; i++){
    TSP.generate();
    L.push_back(TSP.GetBest());
    if((i+1)%Nex==0){
      Rsame->swap(order, size);
      if(rank==order[0]){
        TSP.GetBElem(Bsend);
        MPI_Isend(&Bsend[0],n_cit,MPI_INTEGER,order[1],itag1,MPI_COMM_WORLD,&req);
        MPI_Recv(&Brec[0],n_cit,MPI_INTEGER,order[3],itag4,MPI_COMM_WORLD,&stat1);
        TSP.SaveBElem(Brec);
      }
      if(rank==order[1]){
        TSP.GetBElem(Bsend);
        MPI_Isend(&Bsend[0],n_cit,MPI_INTEGER,order[2],itag2,MPI_COMM_WORLD, &req);
        MPI_Recv(&Brec[0],n_cit,MPI_INTEGER,order[0],itag1,MPI_COMM_WORLD, &stat2);
        TSP.SaveBElem(Brec);
      }
      if(rank==order[2]){
        TSP.GetBElem(Bsend);
        MPI_Isend(&Bsend[0],n_cit,MPI_INTEGER,order[3],itag3, MPI_COMM_WORLD,&req);
        MPI_Recv(&Brec[0],n_cit,MPI_INTEGER,order[1],itag2,MPI_COMM_WORLD,&stat3);
        TSP.SaveBElem(Brec);
      }
      if(rank==order[3]){
        TSP.GetBElem(Bsend);
        MPI_Isend(&Bsend[0],n_cit,MPI_INTEGER,order[0],itag4,MPI_COMM_WORLD, &req);
        MPI_Recv(&Brec[0],n_cit,MPI_INTEGER,order[2],itag3,MPI_COMM_WORLD, &stat4);
        TSP.SaveBElem(Brec);
      }
    }
  }

//stampa delle lunghezze e dei best path
  print(rank,L);
  TSP.PrintBest(rank);

  //2284 3775 29 2118
  rand->SaveSeed();
  MPI_Finalize();
  return 0;
}
