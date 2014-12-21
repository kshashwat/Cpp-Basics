/*
ID: kshashw1
PROG: namenum
LANG: C++11
*/

#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

long long num(char c) {
  if (c == 'A' || c == 'B' || c == 'C') { return 2; }
  if (c == 'D' || c == 'E' || c == 'F') { return 3;}
  if (c == 'H' || c == 'I' || c == 'G') { return 4;}
  if (c == 'K' || c == 'L' || c == 'J') { return 5;}
  if (c == 'N' || c == 'O' || c == 'M') { return 6;}
  if (c == 'P' || c == 'R' || c == 'S') {return 7;}
  if (c == 'T' || c == 'U' || c == 'V') {return 8;}
  return 9;
}

long long strcode(string str) {
  long long code = 0;
  long long x;
  for (int i = 0; i < str.length(); i++) {
    x = num(str[i]);
    for (int j = 0; j < str.length()-1-i; j++) {
      x *= 10;
    }
    //if (str == "KRISTOPHER" ) {cout << x << str[i]  << endl; }
    code += x;
  }
  return code;
}

int main() { 
  ifstream fin ("namenum.in");
  ofstream fout ("namenum.out");
  ifstream dict ("dict.txt");
  vector<string> names;
  string name;
  while (!dict.eof()) {
    name.clear();
    dict >> name;
    names.push_back(name);
  }

  vector<string> valid_names;
  long long code = 0;
  fin >> code;

  for (int i = 0; i < names.size(); i++) {
    if (strcode(names[i]) == code) {
      fout << names[i] << endl;
      valid_names.push_back(names[i]);
    }
  }

  if (valid_names.size() == 0) {
    fout << "NONE" << endl;
    return 0;
  }
  else {
    return 0;
  } 
 //cout << strcode("KRISTOPHER") << endl; 

}  
