#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include "random.h"

using namespace std;

#ifndef __element__
#define __element__

class element{
  private:
    int n_cities;
    vector<int> path;
    vector<double> x, y;
    double L;

  public:
    element();
    element(int, vector <double>, vector<double>);
    element(element *);
    ~element();
    void SetCity(int i, int v){path[i]=v;};
    double GetCity(int i){return path[i];};
    void SetStart();
    void perm(int, int);
    void mut_shift(int, int, Random*);
    void mut_cont(int, Random*);
    void mut_inv(int, Random*);
    void mutate(Random *);
    void Length();
    double GetL(){return L;};
    void check();
    void print();
    int pbc(int);
    int GetN(){return n_cities;};
    double GetX(int i){return x[i];};
    double GetY(int i){return y[i];};

};

#endif
