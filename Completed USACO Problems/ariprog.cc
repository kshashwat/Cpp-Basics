/*
ID: kshashw1
PROG: ariprog
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <math.h>
#include <utility>
#include <map>
#include <vector>
#include <string>

using namespace std;

void quicksort(vector<vector<long long> >* seqs, long long mindex, long long maxdex) {
  if (mindex >= maxdex) {return;}
  long long middex = (maxdex+mindex)/2;
  swap((*seqs)[middex], (*seqs)[maxdex]);
  long long curdex = mindex;
  for (long long i = mindex; i < maxdex; i++) {
    if ((*seqs)[i][1] < (*seqs)[maxdex][1] || ((*seqs)[i][1] == (*seqs)[maxdex][1] && (*seqs)[i][0] < (*seqs)[maxdex][0])) {
      swap((*seqs)[curdex], (*seqs)[i]);
      curdex++;
    }
  }
  swap((*seqs)[curdex], (*seqs)[maxdex]);
  quicksort(&(*seqs), mindex, curdex-1);
  quicksort(&(*seqs), curdex+1, maxdex);
}

int main() {
  ifstream fin ("ariprog.in");
  ofstream fout ("ariprog.out");

  long long N, M;
  fin >> N >> M;

  long long max =2*M*M;
  vector<bool> bisqs;

  for (long long i = 0; i <= max; i++) {
    bisqs.push_back(false);
  }
  for (long long i = 0; i <= M; i++) {
    for (long long j = i; j <= M; j++) {
      bisqs[i*i + j*j] = true;
    }
  }

  vector<long long> dummy;
  vector<vector<long long> >  bisq_list;
  for (long long i = 0; i < N-1; i++) {
    bisq_list.push_back(dummy);  
  }
  for (long long i = 0; i <= max; i++) {
    if (bisqs[i]) {
      bisq_list[i % (N-1)].push_back(i);
    }
  }

  long long diff;
  vector<vector<long long> > seqs;
  bool newseq;

  /*for (long long i = 0; i <= max; i++) {
    for (long long j = 1; j <= (max-i)/(N-1); j++) {
      if (bisqs[i] && bisqs[i+(N-1)*j]) {
      dummy.push_back(i);
      dummy.push_back(j);
      seqs.push_back(dummy);
      dummy.pop_back();
      dummy.pop_back();}
    }
  }*/

  for (long long k = 0; k < bisq_list.size(); k++) {
    for (long long i = 0; i < bisq_list[k].size(); i++) {
      for (long long j = i+1; j < bisq_list[k].size(); j++) {
        diff = (bisq_list[k][j]-bisq_list[k][i])/(N-1);
        if (!(N > 3 && (diff % 2 == 1)) && !(diff % 4 == 2 && bisq_list[k][j] % 2 == 1) 
        && !(diff % 4 == 2 && bisq_list[k][i] % 2 == 1)) {
          newseq = true;
          for (long long l = 2; l < N; l++) {
            if (!bisqs[bisq_list[k][i] + (l-1)*diff]) {newseq = false;}
          }
          if (newseq) {
            dummy.push_back(bisq_list[k][i]);
            dummy.push_back(diff);
            seqs.push_back(dummy);
            dummy.pop_back();
            dummy.pop_back();
          }
        }
      }
    }
  }

  /*for (long long i = 1; i <= N; i++) {
    for (long long j = 0; j < seqs.size();) {
      if (!bisqs[seqs[j][0]+(i-1)*seqs[j][1]]) {
        swap(seqs[j], seqs[seqs.size()-1]);
        seqs.pop_back();
        j--;
      }
      j++;
    }
  }*/

  if (seqs.size() == 0) {
    fout << "NONE" << endl;
    //cout << "NONE" << endl;
    return 0;
  }

  quicksort(&seqs, 0, seqs.size()-1); 

  for (long long i = 0; i < seqs.size(); i++) {
    fout << seqs[i][0] << " " << seqs[i][1] << endl;
    //cout << seqs[i][0] << " " << seqs[i][1] << endl;
  }
  return 0;
}
