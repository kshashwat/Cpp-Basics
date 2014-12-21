/*
ID: kshashw1
PROG: sprime
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <math.h>

using namespace std;

typedef long long ll;

vector<ll> list_all_primes() {
  vector<ll> primes;
  bool isprime;
  ll curindex;
  ll a;
  primes.push_back(2);
  for (ll i = 3; i < 10000; i++) {
    isprime = true;
    curindex = 0;
    a = primes[curindex];
    while (a*a <= i) {
      if (i % a == 0) {
        isprime = false;
        a = i+1;
      }
      else {
        curindex++;
        a = primes[curindex];
      }
    }
    if (isprime) {primes.push_back(i);}
  }
  return primes;
}

bool is_prime(const vector<ll>& plist, ll num) {
  bool isprime = true;
  ll curindex = 0;
  ll a = plist[curindex];
  while (a*a <= num) {
    if (num % a == 0) {
      a = num+1;
      isprime = false;
    }
    else {
      curindex++;
      a = plist[curindex];
    }
  }
  if (isprime) {return true;}
  return false;
}

vector<ll> list_sprimes(ll len, const vector<ll>& plist) {
  if (len == 1) {
    vector<ll> output;
    output.push_back(2);
    output.push_back(3);
    output.push_back(5);
    output.push_back(7);
    return output;
  }
  vector<ll> stumps = list_sprimes(len-1, plist);
  vector<ll> output;
  for (ll i = 0; i < stumps.size(); i++) {
    if (is_prime(plist, stumps[i]*10+1)) {
      output.push_back(stumps[i]*10+1);
    }
    if (is_prime(plist, stumps[i]*10+3)) {
      output.push_back(stumps[i]*10+3);
    }
    if (is_prime(plist, stumps[i]*10+5)) {
      output.push_back(stumps[i]*10+5);
    }
    if (is_prime(plist, stumps[i]*10+7)) {
      output.push_back(stumps[i]*10+7);
    }
    if (is_prime(plist, stumps[i]*10+9)) {
      output.push_back(stumps[i]*10+9);
    }
  }
  return output;
}

int main() {
  ifstream fin ("sprime.in");
  ofstream fout ("sprime.out");

  ll N;
  fin >> N;
  vector<ll> plist = list_all_primes();

  vector<ll> sprimes = list_sprimes(N, plist);
  for (ll i = 0; i < sprimes.size(); i++) {
    fout << sprimes[i] << endl;
  }
  return 0;
}
