/*
ID: kshashw1
PROG: gift1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int find_person_index(vector<string>* people, string target_person) {
  for (int i = 0; i < people->size(); i++) {
    if ((*people)[i] == target_person) {
      return i;
    }
  }
  return -1;
}

int main() {
  ifstream fin ("gift1.in");
  ofstream fout ("gift1.out");

  vector<int> money_change;
  vector<string> people;
  string str;

  int n; fin >> n;
  for (int i = 0; i < n; i++) {
    str.clear();
    fin >> str;
    people.push_back(str);
    money_change.push_back(0);
  }

  int money; 
  int num_donations;
  int donation_size;
  int index;

  for (int i = 0; i < n; i++) {
    str.clear();
    fin >> str >> money >> num_donations;
    if (num_donations != 0) {
      donation_size = (int)(money / num_donations);
      index = find_person_index(&people, str);
      money_change[index] -= (donation_size * num_donations); 
      for (int j = 0; j < num_donations; j++) {
        str.clear();
        fin >> str;
        index = find_person_index(&people, str);
        money_change[index] += donation_size;
      }   
    }
  }

  for (int i = 0; i < n; i++) {
    fout << people[i] << " " << money_change[i] << endl;
  }

  return 0;
}
