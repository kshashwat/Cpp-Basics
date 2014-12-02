/*
ID: kshashw1
PROG: gift1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
  ifstream fin ("gift1.in");
  ofstream fout ("gift1.out");

  int n; fin >> n;
  string str;
  string str2;
  map<string, int> output;
  for (int i = 0; i < n; i++) {
    str.clear();
    fin >> str;
    output[str] = 0;
  }

  int money_pile;
  int num_donations;
  int indiv_donation;
  for (int i = 0; i < n; i++) {
    str.clear();
    fin >> str;
    fin >> money_pile;
    fin >> num_donations;
    indiv_donation = (int)(money_pile / num_donations);
    output[str] -= (indiv_donation * num_donations);
    for (int j = 0; j < num_donations; j++) {
      str2.clear();
      fin >> str2;
      output[str2] += indiv_donation; 
    }
  }

  for (const auto& pair : output) {
    fout << pair.first << " " << pair.second << endl;
  }

  return 0;
}
