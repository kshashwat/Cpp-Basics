/* 
ID: kshashw1
PROG: crypt1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <math.h>

using namespace std;

bool search(long long key, const vector<long long>& arr) {
  for (long long i = 0; i < arr.size(); i++) {
    if (arr[i] == key) {
      return true;
    }
  }
  return false;
}

bool digits_valid(long long key, long long key_digits, const vector<long long>& digits) {
  long long powten = 1;
  for (long long i = 0; i < key_digits; i++) {
    if (!search((key/(powten))%10, digits)) {
      return false;
    }
    powten *= 10;
  }
  return true;
}

int main() {
  ifstream fin ("crypt1.in");
  ofstream fout ("crypt1.out");

  long long num_digits;
  long long solns = 0;
  fin >> num_digits;

  vector<long long> digits;
  long long input;

  for (long long i = 0; i < num_digits; i++) {
    fin >> input;
    digits.push_back(input);
  }

  for (long long i = 10; i < 100; i++) {
    for (long long j = 100; j < 1000; j++) {
      if (digits_valid(i, 2, digits) && digits_valid(j, 3, digits)) {
        if ((i%10)*j < 1000 && ((i/10)%10)*j < 1000) {
          if (digits_valid((i%10)*j, 3, digits) && digits_valid(((i/10)%10)*j, 3, digits)) {
            if (i*j < 10000 && digits_valid(i*j, 4, digits)) {
              solns++;
            }
          }
        }
      }
    }
  }
  fout << solns << endl;
  return 0;
}
