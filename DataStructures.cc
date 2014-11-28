#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// This method is VERY BAD for one reason.
// One is that it takes a bare vector as in input.
// When it is called, the entire vector is COPIED into this function.
//
// If we modify the vector in this function, it will NOT change the
// one outside. It is a COPY.
int sum1(vector<int> input) {
  int value = 0;
  for (int i = 0; i < input.size(); i++) {
    value += input[i];
  }
  return value;
}

// This is the RIGHT way to do sum.
// I take the vector BY CONST REFERENCE - const ...&.
// This allows me to use the vector the same way I did in the function
// above, but it does not cause a copy - it uses the existing one in place.
//
// However, we can't modify the vector outside, because it's CONST.
// NEVER take a reference that is not CONST.
int sum2(const vector<int>& input) {
  int value = 0;
  // C++11 extension to the language - no indices needed.
  // Doesn't work in many cases, eg, when iterating over two arrays of the same length.
  // Also, you might not want to use C++11 features. (They will cause warnings unless you use std=c++11)
  for (int element : input) {
    value += element;
  }
  return value;
}

// Suppose we really want to modify the input - say, compute the sum but also make all elements 0.
// We take a pointer.
int sum3(vector<int>* input) {
  int value = 0;
  // POINTER needs -> instead of *.
  // If the pointer is NULL, this will cause the program to crash.
  // input->size() is exactly the same as (*input).size()
  for (int i = 0; i < input->size(); i++) {
    // Pointer needs to be converted to reference by the * prefix operator.
    // If the pointer is NULL, this will cause the program to crash.
    value += (*input)[i];
    (*input)[i] = 0;
  }
  return value;
}

int main(int argc, char** argv) {
  string str = "asdf";
  vector<int> numbers;
  for (int i = 0; i < 10; i++) {
    numbers.push_back(i*i);
  }
  for (int i = 1; i < 10; i++) {
    numbers[i - 1] += numbers[i];
  }

  vector<int> ten_threes(10, 3);

  cout << "sum1(ten_threes) = " << sum1(ten_threes) << endl;
  // vector is AUTOMATICALLY CONVERTED to const vector& for sum2.
  cout << "sum2(ten_threes) = " << sum2(ten_threes) << endl;
  // vector must be referenced to get a pointer using & prefix operator.
  cout << "sum3(&ten_threes) = " << sum3(&ten_threes) << endl;
  // Check that the final sum is 0.
  cout << "sum1(ten_threes) = " << sum1(ten_threes) << endl;

  map<string,int> names;
  names["asdf"] = 2;
  names["blah"] = 3;
  // Easiest way to iterate is using C++11 syntax.
  for (const auto& pair : names) {
    cout << pair.first << ": " << pair.second << endl;
  }

  return 0;
}
