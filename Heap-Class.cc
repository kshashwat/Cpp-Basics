#include <iostream>
#include <utility>
#include <vector>

using namespace std;

const int INT_MIN_VAL = -2147483648;

// print an input array
// O(length)
void print_intvc(const vector<int>& vc) {
  for (int i = 0; i < vc.size()-1; i++) {
    cout << vc[i] << ", "; 
  }
  cout << vc[vc.size()-1] << endl;
}

// return parent of node indexed n
int parent(int n) {
  return (n/2);
}

// return left child of node indexed n
int leftc(int n) {
  return 2*n;
}

// return right child of node indexed n
int rightc(int n) {
  return ((2*n)+1);
}

class Heap {
  public: 
    vector<int> key_vc;
    void insert(int new_key);
    int extract_max();
  private:
    void increase_key(int new_key, int target_node);
    int heapify(int target_node);
};

// when target node's children root heaps, 
// max_heapify alters input tree to make it into a heap.
// it also returns the final index to which the key associated to target ends up.
// O(log heapsize)
int Heap::heapify(int target) {
  bool done = false;
  int heapsize = (*this).key_vc.size();
  while (!done) {
    if (leftc(target) >= heapsize) {
      return target;  //Neither child in heap
    }
    if (rightc(target) >= heapsize) {
      if ((*this).key_vc[leftc(target)] > (*this).key_vc[target]) {
        swap((*this).key_vc[leftc(target)], (*this).key_vc[target]);
        return leftc(target);
      }
      return target;
    }
    if ((*this).key_vc[target] >= (*this).key_vc[leftc(target)] && (*this).key_vc[target] >= (*this).key_vc[rightc(target)]) {
      return target;
    }
    if ((*this).key_vc[leftc(target)] >= (*this).key_vc[target] && (*this).key_vc[leftc(target)] >= (*this).key_vc[rightc(target)]) {
      swap((*this).key_vc[leftc(target)], (*this).key_vc[target]);
      target = leftc(target);
    }
    else {
      swap((*this).key_vc[rightc(target)], (*this).key_vc[target]);
      target = rightc(target);
    }
  } 
  return -1;
}

// output a random perm of 0,1,...,n-1
// O(n)
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
      swap(perm[i], perm[random_num]);
    }
  }  
  return perm;
}

// returns and extracts root element of heap
// O(log n), n = heapsize
int Heap::extract_max() {
  int max = (*this).key_vc[0];
  swap((*this).key_vc[0], (*this).key_vc[(*this).key_vc.size()-1]);
  (*this).key_vc.pop_back();
  (*this).heapify(0);
  return max;
}

// increases key of heap node
// O(log n), n = heapsize
void Heap::increase_key(int target_node, int new_key) {
  if ((*this).key_vc[target_node] >= new_key) {
    return;
  }
  (*this).key_vc[target_node] = new_key;
  bool done = false;
  while (!done) {
    if ((*this).key_vc[target_node] <= (*this).key_vc[parent(target_node)]) {
      done = true;
    }
    else {
      swap((*this).key_vc[target_node], (*this).key_vc[parent(target_node)]);
      target_node = parent(target_node);
    }
  }
}

//inserts key into heap
// O(log n), n = heapsize
void Heap::insert(int new_key) { 
  (*this).key_vc.push_back(INT_MIN_VAL);
  (*this).increase_key((*this).key_vc.size()-1, new_key);
}

bool check_heap(vector<int>* heap) {
  for (int i = 0; i < heap->size(); i++) {
    if (leftc(i) < heap->size() && (*heap)[leftc(i)] > (*heap)[i]) {
      return false;
    }
    if (rightc(i) < heap->size() && (*heap)[rightc(i)] > (*heap)[i]) {
      return false;
    }
  }
  return true;
}

//main
int main(int argc, char** argv) {
  int n;
  cout << "Heap with how many numbers?  ";
  cin >> n;
  int input_num;
  Heap test_heap;
  for (int i = 0; i < n; i++) {
    cout << "Number " << (i+1) << " ";
    cin >> input_num; 
    test_heap.insert(input_num);
  }
  cout << "Heap correct: " << check_heap(&test_heap.key_vc) << endl;
  print_intvc(test_heap.key_vc);
  test_heap.extract_max();
  cout << "Heap correct: " << check_heap(&test_heap.key_vc) << endl;
  print_intvc(test_heap.key_vc);
}
