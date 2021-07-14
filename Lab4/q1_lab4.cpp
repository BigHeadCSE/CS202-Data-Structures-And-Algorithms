#include <stdio.h>
#include <ostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>

enum COLOR { RED, BLACK };

int id = 0;
class Node {
    public:
        int node_id;
        int val;
        COLOR color;
        Node *left, *right, *parent;

        explicit Node(int val) : val(val) {
        node_id = id++;
        parent = left = right = NULL;

        // std::cout << "add node " << node_id << " " << val << "\n";
        // Node is created during insertion
        // Node is red at insertion
        color = RED;
        }

        // returns pointer to uncle
        Node *uncle() {
        // If no parent or grandparent, then no uncle
        if (parent == NULL || parent->parent == NULL)
        return NULL;

        if (parent->isOnLeft())
        // uncle on right
        return parent->parent->right;
        else
        // uncle on left
        return parent->parent->left;
        }

        // check if node is left child of parent
        bool isOnLeft() { return this == parent->left; }

        // returns pointer to sibling
        Node *sibling() {
        // sibling null if no parent
        if (parent == NULL)
        return NULL;

        if (isOnLeft())
        return parent->right;

        return parent->left;
        }

        // moves node down and moves given node in its place
        void moveDown(Node *nParent) {
        if (parent != NULL) {
        if (isOnLeft()) {
          parent->left = nParent;
        } else {
          parent->right = nParent;
        }
        }
        nParent->parent = parent;
        parent = nParent;
        }

        bool hasRedChild() {
        return (left != NULL && left->color == RED) ||
          (right != NULL && right->color == RED);
        }
};

class RBTree {
    Node *root;

    // left rotates the given node
    void leftRotate(Node *x) {
    // new parent will be node's right child
    auto *nParent = x->right;

    // update root if current node is root
    if (x == root) {
      root = nParent;
    }

    x->moveDown(nParent);

    // connect x with new parent's left element
    x->right = nParent->left;
    // connect new parent's left element with node
    // if it is not null
    if (nParent->left != NULL) {
      nParent->left->parent = x;
    }

    // connect new parent with x
    nParent->left = x;
    }

    void rightRotate(Node *x) {
    // new parent will be node's left child
    auto *nParent = x->left;

    // update root if current node is root
    if (x == root) {
      root = nParent;
    }

    x->moveDown(nParent);

    // connect x with new parent's right element
    x->left = nParent->right;
    // connect new parent's right element with node
    // if it is not null
    if (nParent->right != NULL) {
      nParent->right->parent = x;
    }

    // connect new parent with x
    nParent->right = x;
    }

    void swapColors(Node *x1, Node *x2) {
    COLOR temp_node;
    temp_node = x1->color;
    x1->color = x2->color;
    x2->color = temp_node;
    }

    void swapValues(Node *u, Node *v) {
    int temp_node;
    temp_node = u->val;
    u->val = v->val;
    v->val = temp_node;
    }

    // fix red red at given node
    void fixRedRed(Node *x) {
    // if x is root color it black and return
    if (x == root) {
      x->color = BLACK;
      return;
    }

    // initialize parent, grandparent, uncle
    auto *parent = x->parent, *grandparent = parent->parent,
      *uncle = x->uncle();

    if (parent->color != BLACK) {
      if (uncle != NULL && uncle->color == RED) {
        // uncle red, perform recoloring and recurse
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        fixRedRed(grandparent);
      } else {
        // Else perform LR, LL, RL, RR
        if (parent->isOnLeft()) {
          if (x->isOnLeft()) {
            // for left right
            swapColors(parent, grandparent);
          } else {
            leftRotate(parent);
            swapColors(x, grandparent);
          }
          // for left left and left right
          rightRotate(grandparent);
        } else {
          if (x->isOnLeft()) {
            // for right left
            rightRotate(parent);
            swapColors(x, grandparent);
          } else {
            swapColors(parent, grandparent);
          }

          // for right right and right left
          leftRotate(grandparent);
        }
      }
    }
  }

  // find node that do not have a left child
  // in the subtree of the given node
  Node *successor(Node *x) {
    auto *temp_node = x;

    while (temp_node->left != NULL) {
      temp_node = temp_node->left;
    }

    return temp_node;
  }

  // find node that replaces a deleted node in BST
  Node *BSTreplace(Node *x) {
    // when node have 2 children
    if (x->left != NULL && x->right != NULL) {
      return successor(x->right);
    }

    // when leaf
    if (x->left == NULL && x->right == NULL) {
      return NULL;
    }

    // when single child
    if (x->left != NULL) {
      return x->left;
    }

    return x->right;
  }

  // deletes the given node
  void deleteNode(Node *v) {
    auto *u = BSTreplace(v);

    // True when u and v are both black
    bool uvBlack = ((u == NULL || u->color == BLACK) &&
        (v->color == BLACK));
    auto *parent = v->parent;

    if (u == NULL) {
      // u is NULL therefore v is leaf
      if (v == root) {
        // v is root, making root null
        root = NULL;
      } else {
        if (uvBlack) {
          // u and v both black
          // v is leaf, fix double black at v
          fixDoubleBlack(v);
        } else {
          // u or v is red
          if (v->sibling() != NULL) {
            // sibling is not null, make it red"
            v->sibling()->color = RED;
          }
        }

        // delete v from the tree
        if (v->isOnLeft()) {
          parent->left = NULL;
        } else {
          parent->right = NULL;
        }
      }
      delete v;
      return;
    }

    if (v->left == NULL || v->right == NULL) {
      // v has 1 child
      if (v == root) {
        // v is root, assign the value of u to v, and delete u
        v->val = u->val;
        v->left = v->right = NULL;
        delete u;
        }
        else {
        // Detach v from tree and move u up
        if (v->isOnLeft()) {
          parent->left = u;
        }
        else {
          parent->right = u;
        }
        delete v;
        u->parent = parent;

        if (uvBlack) {
          // u and v both black, fix double black at u
          fixDoubleBlack(u);
        }
        else {
          // u or v red, color u black
          u->color = BLACK;
          }
        }
      return;
      }

    // v has 2 children, swap values with successor and recurse
    swapValues(u, v);
    deleteNode(u);
  }

  void fixDoubleBlack(Node *x) {
    if (x == root)
    // Reached root
    return;

    auto *sibling = x->sibling(), *parent = x->parent;
    if (sibling == NULL) {
      // No sibiling, double black pushed up
      fixDoubleBlack(parent);
    } else {
      if (sibling->color == RED) {
        // Sibling red
        parent->color = RED;
        sibling->color = BLACK;
        if (sibling->isOnLeft()) {
          // left case
          rightRotate(parent);
        } else {
          // right case
          leftRotate(parent);
        }
        fixDoubleBlack(x);
      } else {
        // Sibling black
        if (sibling->hasRedChild()) {
          // at least 1 red children
          if (sibling->left != NULL && sibling->left->color == RED) {
            if (sibling->isOnLeft()) {
              // left left
              sibling->left->color = sibling->color;
              sibling->color = parent->color;
              rightRotate(parent);
            } else {
              // right left
              sibling->left->color = parent->color;
              rightRotate(sibling);
              leftRotate(parent);
            }
          } else {
            if (sibling->isOnLeft()) {
              // left right
              sibling->right->color = parent->color;
              leftRotate(sibling);
              rightRotate(parent);
            } else {
              // right right
              sibling->right->color = sibling->color;
              sibling->color = parent->color;
              leftRotate(parent);
            }
          }
          parent->color = BLACK;
        } else {
          // 2 black children
          sibling->color = RED;
          if (parent->color == BLACK) {
            fixDoubleBlack(parent);
          } else {
            parent->color = BLACK;
          }
        }
      }
    }
  }

  // prints level order for given node
  void levelOrder(Node *x) {
    if (x == NULL)
    // return if node is null
    return;

    // queue for level order
    std::queue<Node *> q;
    Node *curr;

    // push x
    q.push(x);

    while (!q.empty()) {
      // while q is not empty
      // dequeue
      curr = q.front();
      q.pop();

      // print node value
      std::cout << curr->val << " ";

      // push children to queue
      if (curr->left != NULL)
        q.push(curr->left);
      if (curr->right != NULL)
        q.push(curr->right);
    }
  }

  // prints inorder recursively
  void inorder(Node *x) {
    if (x == NULL)
    return;
    inorder(x->left);
    std::cout << x->val << " ";
    inorder(x->right);
  }

 public:
  // constructor
  // initialize root
  RBTree() { root = NULL; }

  // destructor
  ~RBTree() {
    auto current = root;
    auto parent = root;
    while (current != NULL) {
      parent = current->parent;
      delete current;
      current = parent;
    }
  }

  Node *getRoot() { return root; }

  // searches for given value
  // if found returns the node (used for delete)
  // else returns the last node while traversing (used in insert)
  Node *search(int& value) {
    auto *temp_node = root;
    while (temp_node != NULL) {
      if (value < temp_node->val) {
        if (temp_node->left == NULL) {
          break;
        } else {
          temp_node = temp_node->left;
        }
      } else if (value == temp_node->val) {
        break;
      } else {
        if (temp_node->right == NULL) {
          break;
        } else {
          temp_node = temp_node->right;
        }
      }
    }

    return temp_node;
  }

  Node* SearchLeft(int& value) {
    auto* ins = insert(value);

    auto* ret = ins->left;

    if (ret == NULL) {
      ret = ins->parent;

      while (ret != NULL && ret->val > value) {
        ret = ret->parent;
      }
    }

    deleteByVal(value);

    return ret;
  }

  // inserts the given value to tree
  Node* insert(int& value) {
    auto *newNode = new Node(value);
    if (root == NULL) {
      // when root is null
      // simply insert value at root
      newNode->color = BLACK;
      root = newNode;
    } else {
      auto *temp_node = search(value);

      if (temp_node->val == value) {
        delete newNode;
        // return if value already exists
        return temp_node;
      }

      // if value is not found, search returns the node
      // where the value is to be inserted

      // connect new node to correct node
      newNode->parent = temp_node;

      if (value < temp_node->val)
        temp_node->left = newNode;
      else
        temp_node->right = newNode;

      // fix red red voilaton if exists
      fixRedRed(newNode);
    }

    return newNode;
  }

  // utility function that deletes the node with given value
  void deleteByVal(int value) {
    if (root == NULL) {
      // Tree is empty
      return;
    }

    Node *v = search(value);

    if (v->val != value) {
      return;
    }

    deleteNode(v);
  }

  // prints inorder of the tree
  void printInOrder() {
    std::cout << "Inorder: " << std::endl;
    if (root == NULL) {
      std::cout << "Tree is empty" << std::endl;
    } else {
      inorder(root);
    }
    std::cout << std::endl;
  }

  // prints level order of the tree
  void printLevelOrder() {
    std::cout << "Level order: " << std::endl;
    if (root == NULL) {
      std::cout << "Tree is empty" << std::endl;
    } else {
      levelOrder(root);
    }
    std::cout << std::endl;
  }
};

int main(){
    RBTree bst;
	bst.insert(8);
	bst.insert(18);
	bst.insert(5);
	bst.insert(15);
	bst.insert(17);
	bst.insert(25);
	bst.insert(40);
	bst.insert(80);
	bst.deleteNode(25);
	bst.inorder();
	return 0;
}
