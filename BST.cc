//g++ -Wall -Werror -g -rdynamic -o

#include <iostream>
#include <map>
#include <utility>
#include <math.h>
#include <vector>

using namespace std;

//class and struct declarations
struct BSTNode {
  BSTNode(int key, BSTNode* parent);
  ~BSTNode();

  int key;
  BSTNode* right = nullptr;
  BSTNode* left = nullptr;
  BSTNode* parent = nullptr;
};

BSTNode::BSTNode(int k, BSTNode* p) : key(k), parent(p) {}

BSTNode::~BSTNode() {
  if (left != nullptr) {
    delete left;
  }
  if (right != nullptr) {
    delete right;
  }
}

class BST {
 public:
  ~BST();

  bool Contains(int target) const;
  void Print() const;

  void Insert(int target);
  void Delete(int target);

 private:
  BSTNode* Search(int target) const;
  BSTNode* Next(BSTNode* target) const;
  void PrintSubtree(BSTNode* target) const;

  BSTNode* root = nullptr;
};

void BST::Print() const {
  PrintSubtree(root);
  cout << endl;
}

void BST::PrintSubtree(BSTNode* target) const {
  if (target->left != nullptr) {PrintSubtree(target->left);}
  if (target != nullptr) {cout << target->key << " ";}
  if (target->right != nullptr) {PrintSubtree(target->right);}
}

bool BST::Contains(int key) const {
  BSTNode* target = Search(key);
  if (target == nullptr) {
    return false;
  }
  return true;
}

BST::~BST() {
  if (root != nullptr) {
    delete root;
  }
}

BSTNode* BST::Search(int key) const {
  BSTNode* cur_node = root;
  while (cur_node != nullptr && cur_node->key != key) {
    if (cur_node->key > key) {
      cur_node = cur_node->left;
    } else {
      cur_node = cur_node->right;
    }
  }
  return cur_node;
}

//insert a given key
void BST::Insert(int key) {
  if (root == nullptr) {
    root = new BSTNode(key, nullptr);
    return;
  }
  BSTNode* cur_node = root;
  while (true) {
    if (key >= cur_node->key) {
      if (cur_node->right == nullptr) {
        cur_node->right = new BSTNode(key, cur_node);
        return;
      }
      cur_node = cur_node->right;
    } else {
      if (cur_node->left == nullptr) {
        cur_node->left = new BSTNode(key, cur_node);
        return;
      }
      cur_node = cur_node->left;
    }
  }
}

//return pointer to the node which has the smallest key greater than the given node's key
BSTNode* BST::Next(BSTNode* target) const {
  if (target->right != nullptr) {
    BSTNode* cur_node = target->right;
    while (true) {
      if (cur_node->left == nullptr) {
        return cur_node;
      }
      else {
        cur_node = cur_node->left;
      }
    }
  }
  BSTNode* cur_node = target;
  while (true) {
    if (cur_node->parent == nullptr) {
      return nullptr;
    }
    if (cur_node->parent->left == cur_node) {
      return cur_node->parent;
    }
    else {
      cur_node = cur_node->parent;
    }
  }
  return nullptr;
}

//delete a given key and its node 
void BST::Delete(int key) {
  BSTNode* target = Search(key);
  if (target == nullptr) {
    return;
  }
  
  if (target->right == nullptr && target->left == nullptr) {
    if (target->parent != nullptr) {
      if (target->parent->left == target) {
        target->parent->left = nullptr;
      } else {
        target->parent->right = nullptr;
      }
    }
    delete target;
    return;
  }

  if (target->right == nullptr && target->left != nullptr) {
    if (target->parent == nullptr) {
      target->left->parent = nullptr;
      root = target->left;
    } else if (target->parent->left == target) {
      target->parent->left = target->left;
      target->left->parent = target->parent;
    } else {
      target->parent->right = target->left;
      target->left->parent = target->parent;
    }
    delete target;
    return;
  }

  if (target->right != nullptr && target->left == nullptr) {
    if (target->parent == nullptr) {
      target->right->parent = nullptr;
      root = target->right;
    } else if (target->parent->left == target) {
      target->parent->left = target->right;
      target->right->parent = target->parent;
    } else {
      target->parent->right = target->right;
      target->right->parent = target->parent;
    }
    delete target;
    return;
  }

  BSTNode* succ_node = Next(target);
  int succ_key = succ_node->key;
  cout << succ_key << " " << target->key << endl;
  Delete(succ_key);
  target->key = succ_key;
  return;
}

int main() {
  BST tree;
  tree.Insert(8);
  tree.Insert(6);
  tree.Insert(7);
  tree.Insert(1);
  tree.Insert(60);
  tree.Print();
  cout << tree.Contains(60) << endl;
  tree.Delete(60);
  tree.Print();
  cout << tree.Contains(60) << endl;
  tree.Insert(60);
  tree.Print();
  cout << tree.Contains(60) << endl;

  return 0;
}
