/*
ID: kshashw1
PROG: numtri
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <math.h>

using namespace std;

long long max_sum(const vector<vector<long long> > tree, vector<long long>* sums, vector<long long>* sums_helper) {
  for (long long i = 0; i < tree[tree.size()-1].size(); i++) {
    (*sums)[i] = tree[tree.size()-1][i];
  }
  if (tree.size() >= 2) {
  for (long long i = tree.size()-2; i >= 0; i--) {
    (*sums_helper).pop_back();
    for (long long j = 0; j < tree[i].size(); j++) {
      if ((*sums)[j] > (*sums)[j+1]) {
        (*sums_helper)[j] = tree[i][j] + (*sums)[j];
      }
      else {
        (*sums_helper)[j] = tree[i][j] + (*sums)[j+1];
      }
    }
    for (long long j = 0; j < tree[i].size(); j++) {
      (*sums)[j] = (*sums_helper)[j];
    }
    (*sums).pop_back();
  }
  }
  return (*sums)[0];
}

int main() {
  ifstream fin ("numtri.in");
  ofstream fout ("numtri.out");

  vector<vector<long long> > tree;
  vector<long long> sums;
  vector<long long> sums_helper;
  vector<long long> dummy;
  long long num_rows;
  long long int_input;
  fin >> num_rows;
  for (long long i = 0; i < num_rows; i++) {
    tree.push_back(dummy);
    sums.push_back(0);
    sums_helper.push_back(0);
    for (long long j = 0; j < i+1; j++) {
      fin >> int_input;
      tree[i].push_back(int_input);
    }
  }
  sums.push_back(0);
  sums_helper.push_back(0);
  fout << max_sum(tree, &sums, &sums_helper) << endl;
  return 0;
}
