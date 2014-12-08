
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

// when target node's children root heaps, 
// max_heapify alters input tree to make it into a heap.
// it also returns the final index to which the key associated to target ends up.
// O(log heapsize)
int max_heapify(int target, vector<int>* heap) {
  bool done = false;
  int heapsize = heap->size();
  while (!done) {
    if (leftc(target) >= heapsize) {
      return target;  //Neither child in heap
    }
    if (rightc(target) >= heapsize) {
      if ((*heap)[leftc(target)] > (*heap)[target]) {
        swap((*heap)[leftc(target)], (*heap)[target]);
        return leftc(target);
      }
      return target;
    }
    if ((*heap)[target] >= (*heap)[leftc(target)] && (*heap)[target] >= (*heap)[rightc(target)]) {
      return target;
    }
    if ((*heap)[leftc(target)] >= (*heap)[target] && (*heap)[leftc(target)] >= (*heap)[rightc(target)]) {
      swap((*heap)[leftc(target)], (*heap)[target]);
      target = leftc(target);
    }
    else {
      swap((*heap)[rightc(target)], (*heap)[target]);
      target = rightc(target);
    }
  } 
  return -1;
}

// modify input array into a heap
// O(heapsize)
void build_max_heap(vector<int>* arr) {
  int heapsize = arr->size();
  for (int i = 0; i < heapsize; i++) {
    max_heapify(heapsize-1-i, arr);
  }
  return;
}

// sort input array in place (final order increasing)
// O(n log n), n = length
vector<int> HeapSort(vector<int>* arr) {
  vector<int> sorted;
  int heapsize = (*arr).size();
  for (int i = 0; i < heapsize; i++) {
    sorted.push_back(0);
  }
  build_max_heap(&(*arr));
  while (heapsize > 0) {
    swap((*arr)[0], (*arr)[heapsize-1]);
    sorted[heapsize-1] = (*arr)[heapsize-1];
    heapsize--;
    (*arr).pop_back();
    max_heapify(0, &(*arr));
  } 
  return sorted;
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
int heap_extract_max(vector<int>* heap) {
  int max = (*heap)[0];
  swap((*heap)[0], (*heap)[heap->size()-1]);
  (*heap).pop_back();
  max_heapify(0, &(*heap));
  return max;
}

// increases key of heap node
// O(log n), n = heapsize
void heap_increase_key(int target_node, int new_key, vector<int>* heap) {
  if ((*heap)[target_node] >= new_key) {
    return;
  }
  (*heap)[target_node] = new_key;
  bool done = false;
  while (!done) {
    if ((*heap)[target_node] <= (*heap)[parent(target_node)]) {
      done = true;
    }
    else {
      swap((*heap)[target_node], (*heap)[parent(target_node)]);
      target_node = parent(target_node);
    }
  }
}

//inserts key into heap
// O(log n), n = heapsize
void heap_insert(vector<int>* heap, int new_key) { 
  (*heap).push_back(INT_MIN_VAL);
  heap_increase_key(heap->size()-1, new_key, &(*heap));
}

// deletes key from heap
// O(log n), n = heapsize
void heap_delete(int target, vector<int>* heap) {
  (*heap)[target] = INT_MIN_VAL;
  int new_target = max_heapify(target, &(*heap));
  int new_key = (*heap)[heap->size()-1];
  (*heap).pop_back();
  heap_increase_key(new_target, new_key, &(*heap)); 
}

// decrease a node's key
// O(log n), n = heapsize
void heap_decrease_key(int target, int new_key, vector<int>* heap) {
  if (new_key >= (*heap)[target]) {
    return;
  }
  (*heap)[target] = new_key;
  max_heapify(target, &(*heap));
  return;
}

// checks if input is actually a max heap
// O(n), n = heapsize
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
  cout << "Sort how many numbers? ";
  cin >> n;
  vector<int> seq = random_perm(n);
  print_intvc(seq);
  vector<int> sorted = HeapSort(&seq);
  print_intvc(sorted);
  seq = random_perm(n);
  build_max_heap(&seq);
  cout << "Heap building: " << check_heap(&seq) << endl;
  heap_delete(6, &seq); 
  cout << "Heap deleting: " << check_heap(&seq) << endl;
}
