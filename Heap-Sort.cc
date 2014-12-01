#include <iostream>
#include <vector>

using namespace std;

const int INT_MIN_VAL = -2147483648;

// return parent of node indexed n
int parent(int n) {
  return (int)(n/2);
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
int max_heapify(vector<int>* heap, int heapsize, int target) {
  bool done = false;
  while (!done) {
    if (leftc(target) >= heapsize) {
      return target;
    }
    if (rightc(target) >= heapsize) {
      if ((*heap)[leftc(target)] > (*heap)[target]) {
        (*heap)[leftc(target)] += (*heap)[target];
        (*heap)[target] = (*heap)[leftc(target)] - (*heap)[target];
        (*heap)[leftc(target)] -= (*heap)[target];
        return leftc(target);
      }
      return target;
    }
    if ((*heap)[target] >= (*heap)[leftc(target)] && (*heap)[target] >= (*heap)[rightc(target)]) {
      return target;
    }
    if ((*heap)[leftc(target)] >= (*heap)[target] && (*heap)[leftc(target)] >= (*heap)[rightc(target)]) {
      (*heap)[leftc(target)] += (*heap)[target];
      (*heap)[target] = (*heap)[leftc(target)] - (*heap)[target];
      (*heap)[leftc(target)] -= (*heap)[target];  
      target = leftc(target);
    }
    else {
      (*heap)[rightc(target)] += (*heap)[target];
      (*heap)[target] = (*heap)[rightc(target)] - (*heap)[target];
      (*heap)[rightc(target)] -= (*heap)[target];
      target = rightc(target);
    }
  } 
  return -1;
}

// modify input array into a heap
// O(heapsize)
void build_max_heap(vector<int>* arr, int heapsize) {
  for (int i = 0; i < (int)((heapsize+1)/2)+1; i++) {
    max_heapify(arr, heapsize, (int)((heapsize+1)/2)-i);
  }
  return;
}

// sort input array in place (final order increasing)
// O(n log n), n = length
void HeapSort(vector<int>* arr) {
  int heapsize = (*arr).size();
  build_max_heap(&(*arr), heapsize);
  while (heapsize > 1) {
    (*arr)[0] += (*arr)[heapsize-1];
    (*arr)[heapsize-1] = (*arr)[0] - (*arr)[heapsize-1];
    (*arr)[0] -= (*arr)[heapsize-1];
    heapsize--;
    max_heapify(&(*arr), heapsize, 0);
  } 
  return;
}

// print an input array
// O(length)
void print_intvc(const vector<int>& vc) {
  for (int i = 0; i < vc.size()-1; i++) {
    cout << vc[i] << ", "; 
  }
  cout << vc[vc.size()-1] << endl;
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
      perm[i] += perm[random_num];
      perm[random_num] = perm[i] - perm[random_num];
      perm[i] -= perm[random_num]; 
    }
  }  
  return perm;
}

// returns and extracts root element of heap
// O(log n), n = heapsize
int heap_extract_max(vector<int>* heap) {
  int max = (*heap)[0];
  (*heap)[0] += (*heap)[heap->size()-1];
  (*heap)[heap->size()-1] = (*heap)[0] - (*heap)[heap->size()-1];
  (*heap)[0] -= (*heap)[heap->size()-1];
  (*heap).pop_back();
  max_heapify(&(*heap), heap->size()-1, 0);
  return max;
}

// increases key of heap node
// O(log n), n = heapsize
void heap_increase_key(vector<int>* heap, int target_node, int new_key) {
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
      (*heap)[target_node] += (*heap)[parent(target_node)];
      (*heap)[parent(target_node)] = (*heap)[target_node] - (*heap)[parent(target_node)];
      (*heap)[target_node] -= (*heap)[parent(target_node)];
      target_node = parent(target_node);
    }
  }
}

//inserts key into heap
// O(log n), n = heapsize
void heap_insert(vector<int>* heap, int new_key) { 
  (*heap).push_back(INT_MIN_VAL);
  heap_increase_key(&(*heap), heap->size()-1, new_key);
}

// deletes key from heap
// O(log n), n = heapsize
void heap_delete(vector<int>* heap, int target) {
  (*heap)[target] = INT_MIN_VAL;
  int new_target = max_heapify(&(*heap), heap->size(), target);
  int new_key = (*heap)[heap->size()-1];
  (*heap).pop_back();
  heap_increase_key(&(*heap), new_target, new_key); 
}

// decrease a node's key
// O(log n), n = heapsize
void heap_decrease_key(vector<int>* heap, int target, int new_key) {
  if (new_key >= (*heap)[target]) {
    return;
  }
  (*heap)[target] = new_key;
  max_heapify(&(*heap), heap->size(), target);
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
  HeapSort(&seq);
  print_intvc(seq);
  seq = random_perm(n);
  print_intvc(seq);
  build_max_heap(&seq, seq.size());
  print_intvc(seq);
  cout << check_heap(&seq) << endl;
  heap_delete(&seq, 6); 
  print_intvc(seq);
  cout << check_heap(&seq) << endl;
}
