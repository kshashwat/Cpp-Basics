#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

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

void Insertion_Sort(vector<int>* seq) {
  int cur_index;
  bool done;
  for (int i = 0; i < seq->size(); i++) {
    done = false;
    cur_index = i;
    while (!done) {
      if (cur_index == 0) {
        done = true;
      }
      else {
        if ((*seq)[cur_index] < (*seq)[cur_index-1]) {
          (*seq)[cur_index] += (*seq)[cur_index-1];
          (*seq)[cur_index-1] = (*seq)[cur_index] - (*seq)[cur_index-1];
          (*seq)[cur_index] -= (*seq)[cur_index-1];
          cur_index--;
        }
        else {
          done = true;
        }
      }
    }
  }
}

void print_intvc(const vector<int>& vc) {
  for (int i = 0; i < vc.size()-1; i++) {
    cout << vc[i] << ", "; 
  }
  cout << vc[vc.size()-1] << endl;
}

void test_insert() {
  double t = 0; time_t t1, t2;
  vector<int> seq;
  for (int i = 0; i < 50; i++) {
    seq = random_perm(32000);
    time(&t1); 
    Insertion_Sort(&seq);
    time(&t2);
    t += difftime(t2,t1);
  }
  t /= 50;
  cout << t << endl;
}

int main(int argc, char** argv) {
  test_insert();
}
