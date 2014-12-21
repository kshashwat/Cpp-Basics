/*
ID: kshashw1
PROG: milk
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <math.h>
#include <map>
#include <vector>
#include <utility>

using namespace std;

void quick_sort(const vector<long long>& arr, vector<long long>* output, long long mindex, long long maxdex) {
  if (mindex >= maxdex) {return;} 

  long long curdex = mindex;
  for (long long i = mindex; i < maxdex; i++) {
    if (arr[(*output)[i]] <= arr[(*output)[maxdex]]) {
      swap((*output)[i], (*output)[curdex]);
      curdex++;
    }
  }
  swap((*output)[curdex], (*output)[maxdex]); 
  quick_sort(arr, &(*output), mindex, curdex-1);
  quick_sort(arr, &(*output), curdex+1, maxdex);
}

void print_vc(const vector<long long>& arr) {
  for (long long i = 0; i < arr.size(); i++) {cout << arr[i] << endl;}
  cout << "-------------" << endl;
}

int main() {
  ifstream fin ("milk.in");
  ofstream fout ("milk.out");

  long long milk_required; long long num_farmers; vector<long long> prices; vector<long long> amounts; long long curprice; long long curamount;
  fin >> milk_required >> num_farmers;
  vector<long long> priority_order; for (long long i = 0; i < num_farmers; i++) {priority_order.push_back(i); fin >> curprice >> curamount;
  prices.push_back(curprice); amounts.push_back(curamount);}

  if (num_farmers == 0 || milk_required == 0) {fout << 0 << endl; return 0;}

  quick_sort(prices, &priority_order, 0, priority_order.size()-1);
  long long cursupplier_index = 0; long long money_spent = 0;

  while (milk_required > 0) {
    if (amounts[priority_order[cursupplier_index]] >= milk_required) {
      money_spent += (milk_required * prices[priority_order[cursupplier_index]]);
      milk_required = 0;
    }
    else {
      money_spent += (amounts[priority_order[cursupplier_index]]*prices[priority_order[cursupplier_index]]);
      milk_required -= amounts[priority_order[cursupplier_index]];
      cursupplier_index++;
    }
  }
  fout << money_spent << endl;
  return 0;
}
