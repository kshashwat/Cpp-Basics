/*
ID: kshashw1
PROG: marathon
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <math.h>

using namespace std;

long long absd(long long a, long long b) {
  if (a >= b) {return (a-b);}
  return (b-a);
}

long long skip_index(const vector<long long>& x, const vector<long long>& y) {
  long long mindex = 1;
  for (long long i = 1; i <= x.size()-2; i++) {
    if (absd(x[i-1], x[i+1])+absd(y[i-1], y[i+1])-absd(x[i-1],x[i])-absd(x[i],x[i+1])-absd(y[i-1],y[i])-absd(y[i],y[i+1]) <
      absd(x[mindex-1],x[mindex+1])+absd(y[mindex-1],y[mindex+1])-absd(x[mindex-1],x[mindex])-absd(x[mindex],x[mindex+1])-absd(y[mindex-1],y[mindex])
      -absd(y[mindex],y[mindex+1])) {
      mindex = i;
    }
  }
  return mindex;
}

long long dist(const vector<long long>& x, const vector<long long>& y, long long skip_index) {
  long long dist = 0;
  for (long long i = 0; i < skip_index-1; i++) {
    dist += (absd(x[i],x[i+1])+absd(y[i],y[i+1]));
  }
  dist += (absd(x[skip_index-1],x[skip_index+1])+absd(y[skip_index-1],y[skip_index+1]));
  for (long long i = skip_index+1; i < x.size()-1; i++) {
    dist += (absd(x[i],x[i+1])+absd(y[i],y[i+1]));
  }
  return dist;
}

int main() {
  ifstream fin ("marathon.in");
  ofstream fout ("marathon.out");

  long num_checks;
  long input;
  fin >> num_checks;
  vector<long long> x;
  vector<long long> y;

  for (long long i = 0; i < num_checks; i++) {
    fin >> input;
    x.push_back(input);
    fin >> input;
    y.push_back(input);
  }

  long long skip_index_val = skip_index(x, y);
  long long dist_val = dist(x, y, skip_index_val);
  fout << dist_val << endl;
  return 0;
}
