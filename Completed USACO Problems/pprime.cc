/*
ID: kshashw1
PROG: pprime
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <math.h>

using namespace std;

typedef long long ll;

vector<ll> primes(ll upper_limit) {
  vector<ll> output;
  bool is_prime;
  bool done;
  ll test_index;
  output.push_back(2);
  output.push_back(3);
  output.push_back(5);
  for (ll i = 7; i <= upper_limit; i++) {
    is_prime = true;
    done = false;
    test_index = 0;
    while (!done) {
      if ((i % output[test_index]) == 0) {
        is_prime = false;
        done = true;
      }
      else {
        test_index++;
        if (test_index == output.size()) {
          done = true;
        }
      }
    }
    if (is_prime) {output.push_back(i);}
  }
  return output;
}

bool isprime(const vector<ll> plist, ll num) {
  bool prime = true;
  ll curindex = 0;
  ll a = plist[curindex];
  while (a*a <= num) {
    if (num % a == 0) {
      prime = false;
      a = num+1;
    }
    else {
      curindex++;
      a = plist[curindex];
    }
  }
  return prime;
}

int main() {
  ifstream fin ("pprime.in");
  ofstream fout ("pprime.out");

  ll a; 
  ll b;
  fin >> a >> b;

  vector<ll> plist = primes(3400);
  ll curcand;

  for (ll i = 2; i <= 11; i++) {
    if (i >= a && i <= b) {
      if (isprime(plist, i)) {
        fout << i << endl;
      }
    }
  }

  for (ll i = 1; i < 10; i++) {
    for (ll j = 0; j < 10; j++) {
      curcand = 101*i + 10*j;
      if (isprime(plist, curcand) && curcand >= a && curcand <= b) {fout << curcand << endl;}
    }
  }

  for (ll i = 1; i < 10; i++) {
    for (ll j = 0; j < 10; j++) {
      for (ll k = 0; k < 10; k++) {
        curcand = 10001*i + 1010*j + 100*k;
        if (isprime(plist, curcand) && curcand >= a && curcand <= b) {fout << curcand << endl;}
      }
    }
  }

  for (ll i = 1; i < 10; i++) {
    for (ll j = 0; j < 10; j++) {
      for (ll k = 0; k < 10; k++) {
        for (ll l = 0; l < 10; l++) {
          curcand = 1000001*i + 100010*j + 10100*k + 1000*l;
          if (isprime(plist, curcand) && curcand >= a && curcand <= b) {fout << curcand << endl;}
        }
      }
    }
  }

  return 0;
}
