/*
ID: kshashw1
PROG: cowjog
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <math.h>
#include <utility>
#include <vector>
#include <map>

using namespace std;

int main() {
  ifstream fin ("cowjog.in");
  ofstream fout ("cowjog.out");

  long long num_cows;
  fin >> num_cows;

  if (num_cows <= 1) {
    fout << num_cows << endl;
    return 0;
  }

  vector<long long> cows;
  long long input;
  for (long long i = 0; i < num_cows; i++) {
    fin >> input; 
    fin >> input;
    cows.push_back(input);
  }

  vector<long long> grps;
  grps.push_back(cows[cows.size()-1]);
  cows.pop_back();

  while (cows.size() > 0) {
    if (cows[cows.size()-1] <= grps[grps.size()-1]) {
      grps.push_back(cows[cows.size()-1]);
    }
    cows.pop_back();
  }

  fout << grps.size() << endl;
  return 0;
}
