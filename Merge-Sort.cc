#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

void print_intvc(const vector<int>& vc) {
  for (int i = 0; i < vc.size()-1; i++) {
    cout << vc[i] << ", "; 
  }
  cout << vc[vc.size()-1] << endl;
}

vector<int> random_perm(int n) {
  int random_num;
  srand(time(0));
  vector<int> perm;
  for (int i = 0; i < n; i++) {
    perm.push_back(i);
  }
  for (int i = 0; i < n; i++) {
    random_num = rand() % (n-i) + i;
    if (i != random_num) {
      perm[i] += perm[random_num];
      perm[random_num] = perm[i] - perm[random_num];
      perm[i] -= perm[random_num]; 
    }
  }  
  return perm;
}

vector<int> merge_seq(const vector<int>& sorted1, const vector<int>& sorted2) {
  vector<int> merged_seq;
  int cur1 = 0;
  int cur2 = 0;
  for (int i = 0; i < sorted1.size()+sorted2.size(); i++) {
    if (cur1 == sorted1.size()) {
      merged_seq.push_back(sorted2[cur2]);
      cur2++;
    }
    else if (cur2 == sorted2.size()) {
      merged_seq.push_back(sorted1[cur1]);
      cur1++;
    }
    else if (sorted1[cur1] < sorted2[cur2]) {
      merged_seq.push_back(sorted1[cur1]);
      cur1++;
    }
    else {
      merged_seq.push_back(sorted2[cur2]);
      cur2++;
    }
  }
  return merged_seq;
}

vector<int> MergeSort(const vector<int>& seq) {
  vector<int> sorted;
  if (seq.size() == 1) {
    sorted.push_back(seq[0]);
    return sorted;
  }
  vector<int> subseq1;
  vector<int> subseq2;
  for (int i = 0; i < (int)(seq.size()/2); i++) {
    subseq1.push_back(seq[i]);
  }
  for (int i = 0; i < (int)((seq.size()+1)/2); i++) {
    subseq2.push_back(seq[i+(int)(seq.size()/2)]);
  }
  vector<int> sorted_subseq1 = MergeSort(subseq1);
  vector<int> sorted_subseq2 = MergeSort(subseq2);
  sorted = merge_seq(sorted_subseq1, sorted_subseq2);
  return sorted;
}

void test_merge(int trials) {
  double time_elapsed;
  time_t t1, t2;
  vector<int> seq; 
  vector<int> sorted;
  for (int i = 0; i < 11; i++) {
    time_elapsed = 0;
    for (int j = 0; j < trials; j++) {
      seq = random_perm(pow(2, i+10));
      time(&t1);
      sorted = MergeSort(seq);
      time(&t2);
      time_elapsed += difftime(t2, t1); 
    }    
    time_elapsed /= trials;
    cout << time_elapsed << endl;
  }
}

int main(int args, char** argv) {
  int n;
  cout << "How many trials? ";
  cin >> n;
  test_merge(n);
}



