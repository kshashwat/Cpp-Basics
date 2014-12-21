#include <iostream>
#include <vector>
#include <map>

using namespace std;

void test1(map<string, int>* map) {
  cout << (*map)["c"] << endl;
  cout << map->size() << endl;
}

int main(int args, char** argvs) {
  map<string, int> map1;
  map1["a"] = 1;
  map1["b"] = 2;
  //test1(&map1);
  cout << map1.size() << endl;
  cout << map1["c"] << endl;
  cout << map1.size() << endl;
}

