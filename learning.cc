/*
ID: kshashw1
PROG: learning
LANG: C++11
*/

/* 

PROGRAM GOAL: You own a set of N cows (1 <= N <= 50,000). Each cow has a distinct integral weight (between 1 and 1 billion inclusive),
and is either SPOTTED or UNSPOTTED. Given a random weight W (1 <= W <= 1 bn), you predict a new cow (not part of your original N) of weight W
to be SPOTTED if the closest weight cow in your set of N is SPOTTED, and UNSPOTTED if the closest weight cow in your set of N is UNSPOTTED. 
If there are two closest cows, you predict SPOTTED if at least one of the two closest cows is SPOTTED.

You are given a set of B-A+1 new cows (1 <= A <= B <= 1 bn) with weights A, A+1, ..., B. How many cows are predicted to be spotted?
TIME LIMIT: 1 second */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <math.h>
#include <utility>

using namespace std;

void quicksort(const vector<long long>& data, long long mindex, long long maxdex, vector<long long>* target_arr) {
  if (mindex >= maxdex) {return;}

  long long curdex = mindex;
  long long middex = (mindex+maxdex)/2;
  swap((*target_arr)[middex], (*target_arr)[maxdex]);
  for (long long i = mindex; i < maxdex; i++) {
    if (data[(*target_arr)[i]] <= data[(*target_arr)[maxdex]]) {
      swap((*target_arr)[i], (*target_arr)[curdex]);
      curdex++;
    }
  }
  swap((*target_arr)[maxdex], (*target_arr)[curdex]);
  quicksort(data, mindex, curdex-1, &(*target_arr));
  quicksort(data, curdex+1, maxdex, &(*target_arr));
  return;
}

long long A_index(const vector<long long>& weight, const vector<long long>& order, long long A) {
  for (long long i = 0; i < order.size()-1; i++) {
    if (weight[order[i]] <= A && weight[order[i+1]] > A) {return i;}
  }
  if (weight[order[order.size()-1]] <= A) {return (order.size()-1);}
  return 0;
}

long long B_index(const vector<long long>& weight, const vector<long long>& order, long long B) {
  for (long long i = order.size()-1; i >= 1; i--) {
    if (weight[order[i]] >= B && weight[order[i-1]] < B) {return i;}
  }
  if (weight[order[0]] >= B) {return 0;}
  return (order.size()-1);
}

long long spotteds(const vector<long long>& weight, const vector<long long>& order, const vector<long long>& spot, long long mindex, long long maxdex) {
  long long spotteds = 0;
  for (long long i = mindex; i < maxdex; i++) {
    if ((weight[order[i]]-weight[order[i+1]]) % 2 != 0) {
      if (spot[order[i]] == 1) {
        spotteds += ((weight[order[i+1]]-weight[order[i]]+1)/2);
      }
      if (spot[order[i+1]] == 1) {
        spotteds += ((weight[order[i+1]]-weight[order[i]])/2);
      }
    }
    else {
      if (spot[order[i]] == 1) {
        spotteds += ((weight[order[i+1]]-weight[order[i]])/2);
      }
      if (spot[order[i+1]] == 1) {
        spotteds += ((weight[order[i+1]]-weight[order[i]]-1)/2);
      }
      spotteds += ((spot[order[i]]+spot[order[i+1]]+1)/2);
    }
  }
  spotteds += spot[order[maxdex]];
  return spotteds;
}

int main() {
  ifstream fin ("learning.in");
  ofstream fout ("learning.out");

  long long N;
  long long A;
  long long B;
  fin >> N >> A >> B;

  vector<long long> weight;
  vector<long long> spot;
  vector<long long> order;
  string input_str;
  long long input_int;

  for (long long i = 0; i < N; i++) {
    input_str.clear();
    fin >> input_str >> input_int;
    if (input_str == "NS") {
      spot.push_back(0);
    }
    else {
      spot.push_back(1);
    }
    weight.push_back(input_int);
    order.push_back(i);
  }

  quicksort(weight, 0, N-1, &order);

  long long Adex = A_index(weight, order, A);
  long long Bdex = B_index(weight, order, B);

  long long spotted_cows = 0;
  if (A == B) {
    if (((weight[order[Bdex]] - A) <= (weight[order[Adex]]-A)) && (spot[order[Bdex]] == 1)) {
      fout << 1 << endl;
      return 0;
    }
    if (((weight[order[Adex]] - A) <= (weight[order[Bdex]]-A)) && (spot[order[Adex]] == 1)) {
      fout << 1 << endl;
      return 0;
    }
    fout << 0 << endl;
    return 0;
  }
  if (weight[order[Adex]] >= B) {
    spotted_cows = (spot[order[Adex]]*(B-A+1));
    fout << spotted_cows << endl;
    return 0;
  }
  if (weight[order[Bdex]] <= A) {
    spotted_cows = (spot[order[Bdex]]*(B-A+1));
    fout << spotted_cows << endl;
    return 0;
  }
  

  spotted_cows += spotteds(weight, order, spot, Adex, Bdex);

  if (weight[order[Adex]] > A) {
    if (spot[order[Adex]] == 1) {
      spotted_cows += (weight[order[Adex]] - A);
    }
  }
  if (weight[order[Bdex]] < B) {
    if (spot[order[Bdex]] == 1) {
      spotted_cows += (B-weight[order[Bdex]]);
    }
  }

  if (weight[order[Adex]] < A) {
    if (Adex == N-1) {
      if (spot[order[N-1]] == 1) {
        spotted_cows -= (A - weight[order[Adex]]);
      }
    }
    else if ((weight[order[Adex]] - weight[order[Adex+1]]) % 2 == 0) {
      long long trans = (weight[order[Adex]]+weight[order[Adex+1]])/2;
      if (A-1 < trans) {
        spotted_cows -= spot[order[Adex]]*(A-weight[order[Adex]]);
      }
      else {
        spotted_cows -= spot[order[Adex]]*(trans-weight[order[Adex]]);
        spotted_cows -= ((weight[order[Adex]]+weight[order[Adex+1]]+1)/2);
        spotted_cows -= spot[order[Adex+1]]*(A-trans-1);
      }
    }
    else {
      long long trans = ((weight[order[Adex+1]]+weight[order[Adex]])/2);
      if (A-1 <= trans) {
        spotted_cows -= spot[order[Adex]]*(A-weight[order[Adex]]);
      }
      else {
        spotted_cows -= spot[order[Adex]]*(trans-weight[order[Adex]]+1);
        spotted_cows -= spot[order[Adex+1]]*(A-1-trans);
      }
    }
  }

  if (weight[order[Bdex]] > B) {
    if (Bdex == 0) {
      if (spot[order[0]] == 1) {
        spotted_cows -= (weight[order[Bdex]-B]);
      }
    }
    else if ((weight[order[Bdex]] - weight[order[Bdex-1]]) % 2 == 0) {
      long long trans = (weight[order[Bdex]]+weight[order[Bdex-1]])/2;
      if (B+1 > trans) {
        spotted_cows -= spot[order[Bdex]]*(weight[order[Bdex]]-B);
      }
      else {
        spotted_cows -= spot[order[Bdex]]*(weight[order[Bdex]]-trans);
        spotted_cows -= ((weight[order[Bdex]]+weight[order[Bdex-1]]+1)/2);
        spotted_cows -= spot[order[Bdex-1]]*(trans-1-B);
      }
    }
    else {
      long long trans = ((weight[order[Bdex-1]]+weight[order[Bdex]])/2);
      if (B+1 > trans) {
        spotted_cows -= spot[order[Bdex]]*(weight[order[Bdex]]-B);
      }
      else {
        spotted_cows -= spot[order[Bdex]]*(weight[order[Bdex]]-trans);
        spotted_cows -= spot[order[Bdex-1]]*(trans-B);
      }
    }
  }

  fout << spotted_cows << endl;
  return 0;
}
