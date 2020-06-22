#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include "random.h"

using namespace std;

void print (char *, vector<double>);
void print (int, vector<double>);

class element{
  private:
    int n_cities;
    vector<int> path;
    double L;

  public:
    element();
    element(int);
    ~element();
    void SetCity(int i, int v){path[i]=v;};
    double GetCity(int i){return path[i];};
    void SetStart();
    void copy(element);
    void perm(int, int);
    void mut_shift(int, int, Random*);
    void mut_cont(int, Random*);
    void mut_inv(int, Random*);
    void Length(vector<double>, vector<double>);
    double GetL(){return L;};
    void check();
    void clean();
    void print();
    int pbc(int);
    bool operator<(element a){return GetL()<a.GetL();};

};

class population {
  private:
    int n_element;
    int cities;
    vector <element> gen;
    vector <element> new_gen;
    Random *rnd;
    vector <double> x;
    vector <double> y;
    double r_mut, r_cross;

  public:
    population();
    population(int, int, vector<double>, vector<double>, Random *);
    ~population();
    void SetProb(double, double);
    void start();
    void order();
    int select();
    void SetElem(int i, element x){new_gen[i]=x;};
    void SaveBElem(int*);
    void mutate(int);
    void crossover(int, int);
    void generate();
    double GetBest(){return gen[0].GetL();};
    void GetBElem(int*);
    double GetAve();
    void PrintBest(int);
};
