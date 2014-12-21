/* 
ID: kshashw1
PROG: palsquare
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <stdio.h>
#include <math.h>

using namespace std;

int digit(int num, int base, int digit_place) {
  int base_power = pow(base, digit_place);
  int truncated = (num / base_power);
  return (truncated % base);
}

bool test_palsq(int test_num, int base) {
  int n = test_num*test_num;
  int highest_pow = log(n)/log(base);
  if ((int)(pow(base, highest_pow+1)) == n) {highest_pow++;}

  for (int i = 0; i < highest_pow+1; i++) {
    cout << "testing whether output throws error" << endl;
    if (digit(n, base, i) != digit(n, base, highest_pow-i)) {
      return false;
    }
  }

  return true;
}

vector<int> bdigits(int n, int base) {
  int highest_pow = log(n)/log(base);

  vector<int> digits;
  for (int i = 0; i < highest_pow+1; i++) {
    digits.push_back(((int)(n / (pow(base,i))) % base));
  }
  return digits;
}

string str_conversion(int digit) {
  if (digit == 10) {return "A";}
  if (digit == 11) {return "B";}
  if (digit == 12) {return "C";}
  if (digit == 13) {return "D";}
  if (digit == 14) {return "E";}
  if (digit == 15) {return "F";}
  if (digit == 16) {return "G";}
  if (digit == 17) {return "H";}
  if (digit == 18) {return "I";}
  if (digit == 19) {return "J";}
  return "Z";
}

int main() {
  ifstream fin ("palsquare.in");
  ofstream fout ("palsquare.out");

  int base; fin >> base;
  bool palsq;
  vector<int> digits;
  vector<int> rdigits;

  for (int i = 1; i <= 300; i++) {
    palsq = test_palsq(i, base);
    if ((palsq)) {
      rdigits = bdigits(i, base);
      for (int j = rdigits.size()-1; j >= 0; j--) {
        if (rdigits[j] < 10) {
          fout << rdigits[j];
        }
        else {
          fout << str_conversion(rdigits[j]); 
        }
      }
      fout << " ";
      digits = bdigits(i*i, base);
      for (int j = digits.size()-1; j >= 0; j--) {
        if (digits[j] < 10) {
          fout << digits[j];
        }
        else {
          fout << str_conversion(digits[j]); 
        }
      }
      fout << endl;
    }
  }

  return 0;
}
