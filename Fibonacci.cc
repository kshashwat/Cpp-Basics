#include <iostream>
#include <vector>

using namespace std;

bool collatz(int x, vector<int>* steps) {
  // Handle the error case.
  if (x <= 0) {
    return false;
  }

  steps->clear();
  steps->push_back(x);
  while (x != 1) {
    if (x % 2 == 0) {
      x /= 2;
    } else {
      x = (3*x + 1)/2;
    }
    steps->push_back(x);
  }
  return true;
}

int main() {
  int n = 100;
  vector<int> steps;
  if (!collatz(n, &steps)) {
    cout << "collatz(" << n << ") failed." << endl;
    return 0;
  }
  cout << "Got from " << n << " to 1 in " << steps.size()-1  << " steps." << endl;
  for (int i = 0; i < steps.size(); i++) {
    cout << "Step " << i << ": " << steps[i] << endl;
  }
  return 0;
}
