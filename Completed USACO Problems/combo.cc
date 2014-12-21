/*
ID: kshashw1
PROG: combo
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <math.h>

using namespace std;

int main() {
  ifstream fin ("combo.in");
  ofstream fout ("combo.out");

  long long N;
  fin >> N;

  long long f1, f2, f3, m1, m2, m3;
  fin >> f1 >> f2 >> f3 >> m1 >> m2 >> m3;

  vector<long long> u1, u2, u3;

  long long cur1, cur2, cur3;
  bool newdial;
  for (long long i = -2; i <= 2; i++) {
    for (long long j = -2; j <= 2; j++) {
      for (long long k = -2; k <= 2; k++) {
        cur1 = (f1+i)%N;
        cur2 = (f2+j)%N;
        cur3 = (f3+k)%N;
        if (cur1 <= 0) {cur1 += N;}
        if (cur2 <= 0) {cur2 += N;}
        if (cur3 <= 0) {cur3 += N;}
        newdial = true;
        for (long long l = 0; l < u1.size(); l++) {
          if (cur1 == u1[l] && cur2 == u2[l] && cur3 == u3[l]) {
            newdial = false;
          }
        }
        if (newdial) {
          u1.push_back(cur1);
          u2.push_back(cur2);
          u3.push_back(cur3);
          //cout << cur1 << " " << cur2 << " " << cur3 << endl;
        }
        cur1 = (m1+i)%N; cur2 = (m2+j)%N; cur3 = (m3+k)%N;
        if (cur1 <= 0) {cur1 += N;}
        if (cur2 <= 0) {cur2 += N;}
        if (cur3 <= 0) {cur3 += N;}
        newdial = true;
        for (long long l = 0; l < u1.size(); l++) {
          if (cur1 == u1[l] && cur2 == u2[l] && cur3 == u3[l]) {
            newdial = false;
          }
        }
        if (newdial) {
          u1.push_back(cur1);
          u2.push_back(cur2);
          u3.push_back(cur3);
          //cout << cur1 << " " <<  cur2 << " " << cur3 << endl;
        }
      }
    }
  }
  fout << u1.size() << endl;
  return 0;
}
