/* 
ID: kshashw1
PROG: barn1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <math.h>

using namespace std;

vector<long long> filled_runs(const vector<long long>& arr) {
  bool inrun = false;
  long long curindex = 0;
  vector<long long> runs;

  while (curindex < arr.size()) {
    if (inrun && arr[curindex] == 1) {
      runs[runs.size()-1]++;
    }
    else if (inrun && arr[curindex] == 0) {
      inrun = false;
    }
    else if (!inrun && arr[curindex] == 1) {
      runs.push_back(1);
      inrun = true;
    }
    curindex++;
  }
  return runs;
}

vector<long long> empty_runs(const vector<long long>& arr) {
  bool inrun = true;
  vector<long long> runs;

  long long mincow = arr.size(); 
  long long maxcow = -1;

  for (long long i = 0; i < arr.size(); i++) {
    if (arr[i] == 1 && i < mincow) {mincow = i;}
    if (arr[i] == 1 && i > maxcow) {maxcow = i;}
  }

  long long curindex = mincow;

  while (curindex <= maxcow) {
    if (inrun && arr[curindex] == 0) {
      runs.push_back(1);
      inrun = false;
    }
    else if (!inrun && arr[curindex] == 0) {
      runs[runs.size()-1]++;
    }
    else if (!inrun && arr[curindex] == 1) {
      inrun = true;
    }
    curindex++;
  }
  return runs;
}

void insertion_sort(vector<long long>* arr, long long mindex, long long maxdex) {
  if (mindex >= maxdex) {
    return;
  }

  long long curdex = mindex;
  for (long long i = mindex; i < maxdex; i++) {
    if ((*arr)[i] <= (*arr)[maxdex]) {
      swap((*arr)[i], (*arr)[curdex]);
      curdex++;
    }
  }
  swap((*arr)[curdex], (*arr)[maxdex]);
  insertion_sort(&(*arr), mindex, curdex-1);
  insertion_sort(&(*arr), curdex+1, maxdex);
  return;
}

void printvc(const vector<long long>& arr) {for (int i = 0; i < arr.size(); i++) {cout << arr[i] << endl;} return; }

int main() {
  ifstream fin ("barn1.in");
  ofstream fout ("barn1.out");

  long long maxboards;
  long long stalls = 0;
  long long num_cows = 0;
  long long input_reader;

  fin >> maxboards >> stalls >> num_cows;

  vector<long long> barn;
  for (long long i = 0; i < stalls+1; i++) {barn.push_back(0);}
  for (long long i = 0; i < num_cows; i++) {
    input_reader = 0;
    fin >> input_reader;
    barn[input_reader] = 1;
  }

  vector<long long> cowruns = filled_runs(barn);
  vector<long long> emptyruns = empty_runs(barn);

  if (cowruns.size() <= maxboards) {
    fout << num_cows << endl;
    return 0;
  }

  insertion_sort(&emptyruns, 0, emptyruns.size()-1);
  long long wasted_stalls = 0;
  for (long long i = 0; i < cowruns.size()-maxboards; i++) {
    wasted_stalls += emptyruns[i];
  }

  fout << (num_cows + wasted_stalls) << endl;

  return 0;
}
