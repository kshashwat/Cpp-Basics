/*
ID: kshashw1
PROG: dualpal
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <math.h>

using namespace std;

long long digit(long long test_num, long long base, long long digit_place) {
  long long truncated = test_num / (pow(base, digit_place));
  return (truncated % base);
}

bool pal(long long test, long long base) {
  long long highest_pow = log(test)/log(base);
  if (pow(base, highest_pow+1) == test) {highest_pow++;}

  for (int i = 0; i <= highest_pow; i++) {
    if (digit(test, base, i) != digit(test, base, highest_pow-i)) {
      return false;
    }
  }
  return true;
}

int main() {
  ifstream fin ("dualpal.in");
  ofstream fout ("dualpal.out");

  long long nums; fin >> nums;
  long long min; fin >> min; min++;
  long long num_found = 0;
  long long num_pal_hits = 0;
  
  while (num_found < nums) {
    num_pal_hits = 0;
    for (int i = 2; i <= 10; i++) {
      if (pal(min, i)) {num_pal_hits++;}
    }
    if (num_pal_hits >= 2) {fout << min << endl; num_found++;}
    min++;
  }

  return 0;
}
