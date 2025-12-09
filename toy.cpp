#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <cassert>
#include <map>
#include "SoftTree.cpp"

double randnorm() {
  double x=0;
  for (uint i=0; i<12; i++)
    x += (double)rand()/RAND_MAX; 
  return x-6;
}

// Regression toy dataset generator
void generateToy(vector< vector<double> > &X, vector<double> &Y) {
  uint d=1; // dimension
  uint n=300; // number of instances
  uint i,j;
  
  for (i=0; i<n; i++)
  {
    vector<double> x;
    for (j=0; j<d; j++)
      x.push_back(((double)rand()/RAND_MAX)*6-3);
    X.push_back(x);
    Y.push_back(sin(2*x[0]) + randnorm()*0.04);
  }
}

int main(int argc, char *argv[])
{
	vector< vector< double> > X, V, U;
	vector<double> Y, R, T;
	
	//srand(time(NULL)); // random seed
	srand(123457);
	
	cout.precision(5);
	cout.setf(ios::fixed,ios::floatfield);
	
	// Toy dataset regression
	generateToy(X, Y);  // training set
	generateToy(V, R);  // validation set (acts as prepruning set)
	
	SoftTree st = SoftTree(X, Y, V, R);
	
	double y;

	// Dump train inputs/targets for downstream reuse.
	ofstream trainf("train.txt");
	for(uint i=0; i<X.size(); i++) {
          trainf << X[i][0] << " " << Y[i] << endl;
	}
	trainf.close();

	ofstream outf("out"); // validation outputs (with preds)
	for(uint i=0; i<V.size(); i++) {
          y = st.evaluate(V[i]);
          outf << V[i][0] << " " << R[i] << " " << y << endl;
	}
	
	cout << "Number of nodes: " << st.size() << endl;
	st.print();
      	
	return 0;
	
}
