/*
ID: kshashw1
PROG: milk3
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <math.h>

using namespace std;

vector<vector<vector<bool> > > trip_splits(long long total) {
  vector<vector<vector<bool> > > splits;
  vector<vector<bool> > dummy;
  vector<bool> dummy2;
  for (long long i = 0; i <= total; i++) {
    dummy2.push_back(false);
  }
  for (long long i = 0; i <= total; i++) {
    dummy.push_back(dummy2);
  }
  for (long long i = 0; i <= total; i++) {
    splits.push_back(dummy);
  }
  return splits;
}

vector<long long> pour(long long milk_holder, long long milk_target, const vector<long long> milk_list, const vector<long long> milk_capacities) {
  vector<long long> new_milk_list = milk_list;
  if (milk_list[milk_holder] >= (milk_capacities[milk_target]-milk_list[milk_target])) {
    new_milk_list[milk_target] = milk_capacities[milk_target];
    new_milk_list[milk_holder] -= (milk_capacities[milk_target]-milk_list[milk_target]);
  }
  else { 
    new_milk_list[milk_holder] = 0;
    new_milk_list[milk_target] += milk_list[milk_holder];
  }
  return new_milk_list;
}

void search_splits(vector<vector<vector<bool> > >* splits, const vector<long long> milk_list, const vector<long long> milk_capacities) {
  (*splits)[milk_list[0]][milk_list[1]][milk_list[2]] = true;
  vector<long long> new_list;
  for (long long i = 0; i < 3; i++) {
    for (long long j = 0; j < 3; j++) {
      if (i != j) {
        new_list = pour(i, j, milk_list, milk_capacities);
        if (!(*splits)[new_list[0]][new_list[1]][new_list[2]]) {
          (*splits)[new_list[0]][new_list[1]][new_list[2]] = true;
          search_splits(&(*splits), new_list, milk_capacities);
        }
      }
    }
  }
  return;
}

int main() {
  ifstream fin ("milk3.in");
  ofstream fout ("milk3.out");
  vector<long long> capacities;
  vector<long long> milk_list;
  long long input_reader;
  fin >> input_reader;
  capacities.push_back(input_reader);
  milk_list.push_back(0);
  fin >> input_reader;
  capacities.push_back(input_reader);
  milk_list.push_back(0);
  fin >> input_reader;
  capacities.push_back(input_reader);
  milk_list.push_back(input_reader);

  vector<vector<vector<bool> > > splits = trip_splits(capacities[2]);
  search_splits(&splits, milk_list, capacities);

  long long total = capacities[2];
  long long last_written = -1;
  for (long long i = 0; i <= total; i++) {
    for (long long j = 0; j <= total; j++) {
      for (long long k = 0; k <= total; k++) {
        if (splits[k][j][i] && (k == 0) && (last_written != i) && (last_written != -1)) {
          fout << " " << i;
          last_written = i;
        }
        else if (splits[k][j][i] && (k == 0) && (last_written == -1)) {
          fout << i;
          last_written = i;
        }
      }
    }
  }
  fout << endl;
  return 0;

}
