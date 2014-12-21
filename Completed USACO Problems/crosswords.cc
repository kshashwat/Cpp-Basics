/*
ID: kshashw1
PROG: crosswords
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <math.h>
#include <utility>

using namespace std;

int main() {
  ifstream fin ("crosswords.in");
  ofstream fout ("crosswords.out");

  long long N; 
  long long M;
  string input_str;

  fin >> N >> M;
  vector<string> table;
  for (long long i = 0; i < N; i++) {
    input_str.clear();
    fin >> input_str;
    table.push_back(input_str);
  }

  vector<long long> x;
  vector<long long> y;

  long long num_clues = 0;

  for (long long i = 0; i < N; i++) {
    for (long long j = 0; j < M; j++) {
      if (j == 0 && table[i][0] == '.' && table[i][1] == '.' && table[i][2] == '.') {
        x.push_back(i+1);
        y.push_back(j+1);
        num_clues++;
      }
      else if (j > 0 && j <= M-3 && table[i][j-1] == '#' && table[i][j] == '.' && table[i][j+1] == '.'  && table[i][j+2] == '.') {
        x.push_back(i+1);
        y.push_back(j+1);
        num_clues++;
      }
      else if (i == 0 && table[0][j] == '.' && table[1][j] == '.' && table[2][j] == '.') {
        x.push_back(i+1);
        y.push_back(j+1);
        num_clues++;
      }
      else if (i > 0 && i <= N-3 && table[i-1][j] == '#' && table[i][j] == '.' && table[i+1][j] == '.'  && table[i+2][j] == '.') {
        x.push_back(i+1);
        y.push_back(j+1);
        num_clues++;
      }
    }
  }

  if (num_clues == 0) {
    fout << 0 << endl;
    return 0;
  }
  
  fout << num_clues << endl;
  for (long long i = 0; i < num_clues; i++) {
    fout << x[i] << " " << y[i] << endl;
  }
  return 0;
}
