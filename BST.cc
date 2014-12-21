//g++ -Wall -Werror -g -rdynamic -o

#include <iostream>
#include <map>
#include <utility>
#include <math.h>
#include <vector>

using namespace std;

//class and struct declarations
struct BSTNode {
  ~BSTNode();

  int key;
  BSTNode* right = nullptr;
  BSTNode* left = nullptr;
  BSTNode* parent = nullptr;
};

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

  bool contains(int target) const;
  void print_tree() const;

  void insert(int target);
  void del(int target);

 private:
  BSTNode* search(int target) const;
  BSTNode* succ(BSTNode* target) const;
  BSTNode* pred(BSTNode* target) const;
  void print_subtree(BSTNode* target) const;

  void subtree_del(BSTNode* target);

  BSTNode* root = nullptr;
};

void BST::print_tree() const {
  print_subtree(root);
  cout << endl;
}

void BST::print_subtree(BSTNode* target) const {
  if (target->left != nullptr) {print_subtree(target->left);}
  if (target != nullptr) {cout << target->key << " ";}
  if (target->right != nullptr) {print_subtree(target->right);}
}

bool BST::contains(int key) const {
  BSTNode* target = BST::search(key);
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

//search for a given key
BSTNode* BST::search(int target) const {
  BSTNode* cur_node = root;
  while (true) {
    if (cur_node == nullptr) {
      return nullptr;
    }
    else if (cur_node->key == target) {
      return cur_node;
    }
    else if (cur_node->key > target) {
      cur_node = cur_node->left;
    }
    else {
      cur_node = cur_node->right;
    }
  }
  return nullptr;
}

//insert a given key
void BST::insert(int target) {
  BSTNode* cur_node = root;
  if (cur_node == nullptr) {
    root = new BSTNode;
    root->key = target;
    return;
  }
  while (true) {
    if (target >= cur_node->key && cur_node->right == nullptr) {
      cur_node->right = new BSTNode;
      cur_node->right->key = target;
      cur_node->right->parent = cur_node;
      cur_node->right->right = nullptr;
      cur_node->right->left = nullptr;
      return;
    }
    if (target <= cur_node->key && cur_node->left == nullptr) {
      cur_node->left = new BSTNode;
      cur_node->left->key = target;
      cur_node->left->parent = cur_node;
      cur_node->left->right = nullptr;
      cur_node->left->left = nullptr;
      return;
    }
    if (target >= cur_node->key) {
      cur_node = cur_node->right;
    }
    else {
      cur_node = cur_node->left;
    }
  }
}

//return pointer to the node which has the smallest key greater than the given node's key
BSTNode* BST::succ(BSTNode* target) const {
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

//return pointer to the node which has the largest key less than the given node's key
BSTNode* BST::pred(BSTNode* target) const {
  if (target->left != nullptr) {
    BSTNode* cur_node = target->left;
    while (true) {
      if (cur_node->right == nullptr) {
        return cur_node;
      }
      else {
        cur_node = cur_node->right;
      }
    }
  }
  BSTNode* cur_node = target;
  while (true) {
    if (cur_node->parent == nullptr) {
      return nullptr;
    }
    if (cur_node->parent->right == cur_node) {
      return cur_node->parent;
    }
    else {
      cur_node = cur_node->parent;
    }
  }
  return nullptr;
}

//delete a given key and its node 
void BST::del(int key) {
  BSTNode* target = BST::search(key);
  if (target == nullptr) {return;}
  
  if (target->right == nullptr && target->left == nullptr) {
    if (target->parent == nullptr) {
      delete target;
      return;
    }
    else if (target->parent->left == target) {
      target->parent->left = nullptr;
      delete target;
      return;
    }
    else { 
      target->parent->right = nullptr;
      delete target;
      return;
    }
  }

  if (target->right == nullptr && target->left != nullptr) {
    if (target->parent == nullptr) {
      target->left->parent = nullptr;
      root = target->left;
      delete target;
      return;
    }
    else if (target->parent->left == target) {
      target->parent->left = target->left;
      target->left->parent = target->parent;
      delete target;
      return;
    }
    else {
      target->parent->right = target->left;
      target->left->parent = target->parent;
      delete target;
      return;
    }
  }

  if (target->right != nullptr && target->left == nullptr) {
    if (target->parent == nullptr) {
      target->right->parent = nullptr;
      root = target->right;
      delete target;
      return;
    }
    else if (target->parent->left == target) {
      target->parent->left = target->right;
      target->right->parent = target->parent;
      delete target;
      return;
    }
    else {
      target->parent->right = target->right;
      target->right->parent = target->parent;
      delete target;
      return;
    }
  }

  BSTNode* succ_node = succ(target);
  int succ_key = succ_node->key;
  cout << succ_key << " " << target->key << endl;
  del(succ_key);
  target->key = succ_key;
  return;
}

int main() {
  BST tree;
  tree.insert(8);
  tree.insert(6);
  tree.insert(7);
  tree.insert(1);
  tree.insert(60);
  tree.print_tree();
  cout << tree.contains(60) << endl;
  tree.del(60);
  tree.print_tree();
  cout << tree.contains(60) << endl;
  tree.insert(60);
  tree.print_tree();
  cout << tree.contains(60) << endl;

  return 0;
}
