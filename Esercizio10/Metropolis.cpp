#include "Metropolis.h"

void print (char *filename, vector<double> v){
  ofstream fout(filename);
  int dim=v.size();
  if(!fout) {
  	cout<<"cannot open output_file"<<endl;
  	exit(0);
  	 }
  for (int i=0; i<dim; i++)
  	fout <<v[i]<< endl;
}

Metropolis :: Metropolis (){}
Metropolis :: ~Metropolis(){}
Metropolis :: Metropolis (element *p, Random* rand){
  R=rand;
	x=p;
	x->Length();
  acc=0;
}

void Metropolis :: SetSP(element *start){
	x=start;
  acc=0;
}

void Metropolis :: Run(){
  element *prop=new element(x);
  double A, L1=x->GetL(), L2;
  prop->mutate(R);
	prop->Length();
	L2=prop->GetL();
	if(L2<L1){
		x=prop;
		acc+=1;
	}else{
  	A=min(1., exp(-(L2-L1)/T));
  	double r=R->Rannyu();
  	if (r<A){
    	x=prop;
    	acc+=1;
  	}
	}
}

void Metropolis :: Print(char* filename){
	ofstream fout(filename);
	int dim=x->GetN();
	if(!fout) {
		cout<<"cannot open output_file"<<endl;
		exit(0);
		 }
	for (int i=0; i<dim; i++){
		int j=x->GetCity(i)-1;
		fout <<x->GetX(j)<< "\t"<<x->GetY(j) <<endl;
	}
}
