/*
ID: kshashw1
PROG: wormhole
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <math.h>

using namespace std;

vector<vector<long long> > list_pairings(vector<long long> *arr) {
  vector<vector<long long> > output;
  if (arr->size() == 2) {
    vector<long long> unique_pair;
    unique_pair.push_back((*arr)[0]);
    unique_pair.push_back((*arr)[1]);
    output.push_back(unique_pair);
    return output;
  }
  vector<vector<long long> > current_holder;
  vector<long long> current_addendum;
  for (long long i = 1; i < arr->size(); i++) {
    current_addendum.push_back((*arr)[i]);
    current_addendum.push_back((*arr)[0]);
    swap((*arr)[i], (*arr)[arr->size()-1]);
    (*arr).pop_back();
    swap((*arr)[0], (*arr)[arr->size()-1]);
    (*arr).pop_back();
    current_holder = list_pairings(&(*arr));
    for (long long j = 0; j < current_holder.size(); j++) {
      current_holder[j].push_back(current_addendum[0]);
      current_holder[j].push_back(current_addendum[1]);
      output.push_back(current_holder[j]);
    }
    (*arr).push_back(current_addendum[1]);
    swap((*arr)[0], (*arr)[arr->size()-1]);
    (*arr).push_back(current_addendum[0]);
    swap((*arr)[i], (*arr)[arr->size()-1]);
    current_addendum.pop_back();
    current_addendum.pop_back();
  }
  return output;
}

void printvcvc(const vector<vector<long long> >& arr) {
  for (long long i = 0; i < arr.size(); i++) {
    for (long long j = 0; j < arr[i].size(); j++) {
      cout << arr[i][j] << " ";
    }
    cout << endl;
  }
}

long long next_wormkey(const vector<long long>& wormx, const vector<long long>& wormy, long long cur_wormkey) {
  vector<long long> min;
  for (long long i = 0; i < wormx.size(); i++) {
    if (wormy[cur_wormkey] == wormy[i] && wormx[cur_wormkey] < wormx[i] && min.size() == 0) {
      min.push_back(i);
    }
    else if (wormy[cur_wormkey] == wormy[i] && wormx[cur_wormkey] < wormx[i] && min.size() > 0 && wormx[i] < wormx[min[0]]) {
      min[0] = i;
    }
  }
  if (min.size() > 0) {return min[0];}
  return -1;
}

bool check_loop(const vector<long long>& wormx, const vector<long long>& wormy, const vector<long long>& pairing, long long cur_key) {
  long long i = cur_key;
  long long iterations = 0;
  bool cur_iter_done;
  while (i != -1 && !(i == cur_key && iterations > 0)) {
    iterations++;
    i = next_wormkey(wormx, wormy, i);
    if (i != -1) {
      cur_iter_done = false;
      for (long long j = 0; j < pairing.size(); j++) {
        if (pairing[j] == i && !cur_iter_done) {
          if (j % 2 == 0) {
            i = pairing[j+1];
            cur_iter_done = true;
          }
          else {
            i = pairing[j-1];
            cur_iter_done = true;
          }
        }
      }
    }
  }
  if (i == cur_key) {return true;}
  return false;
}

int main() {
  ifstream fin ("wormhole.in");
  ofstream fout ("wormhole.out");

  long long N;
  fin >> N;
  vector<long long> wormx;
  vector<long long> wormy;
  long long input_int;
  for (long long i = 0; i < N; i++) {
    fin >> input_int;
    wormx.push_back(input_int);
    fin >> input_int;
    wormy.push_back(input_int);
  }

  vector<long long> nodes;
  for (long long i = 0; i < N; i++) {
    nodes.push_back(i);
  }
  vector<vector<long long> > pairings = list_pairings(&nodes);
  bool cur_loop;
  long long loops_found = 0;

  for (long long i = 0; i < pairings.size(); i++) {
    cur_loop = false;
    for (long long j = 0; j < N; j++) {
      if (check_loop(wormx, wormy, pairings[i], j)) {
        cur_loop = true;
      }
    }
    if (cur_loop) {loops_found++;}
  }

  fout << loops_found << endl;
  return 0;
}
