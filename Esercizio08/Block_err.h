#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

double DevSt (const vector <double>, const vector <double>, int);
void print (char *, vector<double>);
double Ham (double x, double mu, double sigma);

class Block_err {
private:
  vector <double> ave, av2, sum_prog, su2_prog, err_prog;
  int N,M,L;

public:
  Block_err();
  Block_err(vector <double>, int, int);
  Block_err (int, int);
  ~Block_err();
  void SetBlock(int,int);
  void SetAve(double r, int n);
  double GetMean(){return sum_prog[N-1];};
  void Reset();
  void Calc(int n);
  void Print(char *);
};
