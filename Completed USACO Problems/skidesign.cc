/*
ID: kshashw1
PROG: skidesign
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <math.h>
#include <utility>

using namespace std;

long long cost(const vector<long long>& heights, long long min) {
  long long cost = 0;
  for (long long i = 0; i < heights.size(); i++) {
    if (heights[i] < min) {
      cost += ((min-heights[i])*(min-heights[i]));
    }
    else if (heights[i] > (min+17)) {
      cost += ((min+17-heights[i])*(min+17-heights[i]));
    }
  }
  return cost;
}

int main() {
  ifstream fin ("skidesign.in");
  ofstream fout ("skidesign.out");

  long long N;
  long long input;
  long long curmin;
  fin >> N;
  vector<long long> heights;
  for (long long i = 0; i < N; i++) {fin >> input; heights.push_back(input);}

  curmin = cost(heights, 0);
  for (long long i = 0; i <= 100; i++) {
    input = cost(heights, i);
    if (input < curmin) {curmin = input;}
  }
  fout << curmin << endl;
  return 0;
}
