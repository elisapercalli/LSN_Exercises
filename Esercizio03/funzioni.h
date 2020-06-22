#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "random.h"

using namespace std;

double DevSt (const vector <double>, const vector <double>, int);
void SetGen (Random *); //funzione per settare il seed del generatore
void print (char *, vector<double>);

class Block_err {
private:
  vector <double> ave, av2, sum_prog, su2_prog, err_prog;
  int N,M,L;
  double mean, error;

public:
  Block_err();
  Block_err(vector <double>, int, int);
  Block_err (int, int);
  ~Block_err();
  void SetBlock(int,int);
  void SetVector(vector<double>);
  void SetAve(vector<double>);
  void Calc();
  double GetMean();
  double GetErr();
  void Print(char *);
};
