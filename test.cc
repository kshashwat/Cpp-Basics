#include <iostream>

using namespace std;

int incre(int* a) {
  (*a)++;
  return (*a);
}

int static_incre(int a) {
  return (a+1);
}

int main() {
  int a = 1;
  cout << a << endl;
  cout << static_incre(a) << " " << a << endl;
  cout << incre(&a) << " " << a << endl;
}
