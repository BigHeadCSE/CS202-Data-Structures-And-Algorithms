/*
Author- S Samarth Reddy (b19109) Group 25
    This RB tree supports insert and search operations. It supports rangeAvg(i,j) I did not have enough time to implement Delete operation.
        tree.insert[i,x] - insert integer x at location/index i.
        tree.search[i] -   search for the integer at index i.
    The internal nodes store the sum of its left and right children.

    The elements have been hard coded.
*/

#include <iostream>
#include <queue>
using namespace std;

enum COLOR { RED, BLACK };

class Node {
public:
    int val;
    int num;
    COLOR color;
    Node* left, * right, * parent;

    Node(int val) : val(val) {
        parent = left = right = NULL;

        // Node is created during insertion
        // Node is red at insertion
        color = RED;
        num = 1;
    }

    // returns pointer to uncle
    Node* uncle() {
        // If no parent or grandparent, then no uncle
        if (parent == NULL or parent->parent == NULL)
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
    Node* sibling() {
        // sibling null if no parent
        if (parent == NULL)
            return NULL;

        if (isOnLeft())
            return parent->right;

        return parent->left;
    }

    // moves node down and moves given node in its place
    void moveDown(Node* nParent) {
        if (parent != NULL) {
            if (isOnLeft()) {
                parent->left = nParent;
            }
            else {
                parent->right = nParent;
            }
        }
        nParent->parent = parent;
        parent = nParent;
    }

    bool hasRedChild() {
        return (left != NULL and left->color == RED) or (right != NULL and right->color == RED);
    }
};


class RBTree {
    Node* root;

    // left rotates the given node
    void leftRotate(Node* x) {
        // new parent will be node's right child
        Node* nParent = x->right;

        // update root if current node is root
        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        // connect x with new parent's left element
        x->right = nParent->left;
        // connect new parent's left element with node
        // if it is not null
        if (nParent->left != NULL)
            nParent->left->parent = x;

        // connect new parent with x
        nParent->left = x;
        fixSum(x);
    }

    void rightRotate(Node* x) {
        // new parent will be node's left child
        Node* nParent = x->left;

        // update root if current node is root
        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        // connect x with new parent's right element
        x->left = nParent->right;
        // connect new parent's right element with node
        // if it is not null
        if (nParent->right != NULL)
            nParent->right->parent = x;

        // connect new parent with x
        nParent->right = x;
        fixSum(x);
    }

    void swapColors(Node* x1, Node* x2) {
        COLOR temp;
        temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }

    void swapValues(Node* u, Node* v) {
        int temp;
        temp = u->val;
        u->val = v->val;
        v->val = temp;
    }

    // fix red red at given node
    void fixRedRed(Node* x) {
        // if x is root color it black and return
        if (x == root) {
            x->color = BLACK;
            return;
        }

        // initialize parent, grandparent, uncle
        Node* parent = x->parent, * grandparent = parent->parent, * uncle = x->uncle();

        if (parent->color != BLACK) {
            if (uncle != NULL && uncle->color == RED) {
                // uncle red, perform recoloring and recurse
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                fixRedRed(grandparent);
            }
            else {
                // Else perform LR, LL, RL, RR
                if (parent->isOnLeft()) {
                    if (x->isOnLeft()) {
                        // for left left
                        swapColors(parent, grandparent);
                    }
                    else {
                        // for left right
                        leftRotate(parent);
                        swapColors(x, grandparent);
                    }
                    // for left left and left right
                    rightRotate(grandparent);
                }
                else {
                    if (x->isOnLeft()) {
                        // for right left
                        rightRotate(parent);
                        swapColors(x, grandparent);
                    }
                    else {
                        // for right right
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
    Node* successor(Node* x) {
        Node* temp = x;

        while (temp->left != NULL)
            temp = temp->left;

        return temp;
    }

    Node* searchTreeHepler(Node* temp, int i) {
        if (temp->left == NULL && temp->right == NULL) return temp;

        if (temp->left->num < i) {
            return searchTreeHepler(temp->right, i - temp->left->num);
        }
        else {
            return searchTreeHepler(temp->left, i);
        }
    }

    // Last index so that last index can be added
    Node* rightmost(Node* temp) {
        if (temp->right == NULL) return temp;
        return rightmost(temp->right);
    }

    // prints in-order leaves recursively
    void inorderleaf(Node* x) {
        if (x == NULL)
            return;
        inorderleaf(x->left);
        if (x->left == NULL && x->right == NULL) cout << x->val << " ";
        inorderleaf(x->right);
    }

    // prints in-order recursively
    void inorder(Node* x) {
        if (x == NULL)
            return;
        inorder(x->left);
        cout << x->val << " ";
        inorder(x->right);
    }

    void printHelper(Node* roots, string indent, bool last) {
        // print the tree structure on the screen
        if (roots != NULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "     ";
            }
            else {
                cout << "L----";
                indent += "|    ";
            }

            string sColor = (roots->color == RED) ? "RED" : "BLACK";
            cout << roots->val << " [" << roots->num << "] " << "(" << sColor << ")" << endl;
            printHelper(roots->left, indent, false);
            printHelper(roots->right, indent, true);
        }
    }

    int rangeSum(Node* nodeZ, int i, int j) {
        if (j - i + 1 == nodeZ->num) return nodeZ->val;
        int leftval = nodeZ->left->num ? nodeZ->left->num : 0;
        if (j <= leftval) return rangeSum(nodeZ->left, i, j);
        if (i > leftval) return rangeSum(nodeZ->right, i - leftval, j - leftval);
        return (rangeSum(nodeZ->left, i, leftval) + rangeSum(nodeZ->right, 1, j - leftval));
    }

public:
    // constructor
    // initialize root
    RBTree() { root = NULL; }

    Node* getRoot() { return root; }

    int search(int i) {
        int value = searchTreeHepler(this->root, i)->val;
        cout << "Element at index " << i << ":  " << value << "\n" << endl;
        return value;
    }

    void fixSum(Node* node) {
        if (node == NULL) return;
        node->val = ((node->left->val) + (node->right->val));
        node->num = (node->left->num) + (node->right->num);
        return fixSum(node->parent);
    }

    // inserts the given value to tree
    void insert(int i, int n) {
        Node* newNode = new Node(n);
        if (root == NULL) {
            // when root is null
            // simply insert value at root
            newNode->color = BLACK;
            root = newNode;
        }
        else if (i > root->num) {
            Node* rnode = rightmost(this->root);
            rnode->right = newNode;
            newNode->parent = rnode;
            fixRedRed(newNode);

            if (newNode->parent->left == NULL) {
                Node* tmpo = new Node(newNode->parent->val);
                tmpo->parent = newNode->parent;
                newNode->parent->left = tmpo;
            }
            fixSum(newNode->parent);

        }
        else {
            Node* temp = searchTreeHepler(this->root, i);

            // connect new node to correct node
            newNode->parent = temp;
            temp->left = newNode;

            // fix red red violation if exists
            fixRedRed(newNode);

            if (newNode->parent->right == NULL) {
                Node* tmpo = new Node(newNode->parent->val);

                tmpo->parent = newNode->parent;
                newNode->parent->right = tmpo;
            }
            fixSum(newNode->parent);
        }
    }

    // prints in-order leaves of the tree
    void printInOrderleaf() {
        cout << "In-order of leaf nodes: " << endl;
        if (root == NULL)
            cout << "Tree is empty" << endl;
        else
            inorderleaf(root);
        cout << endl;
    }
    // prints in-order of the tree
    void printInOrder() {
        cout << "In-order: " << endl;
        if (root == NULL)
            cout << "Tree is empty" << endl;
        else
            inorder(root);
        cout << endl;
    }

    // print the tree structure on the screen
    void prettyPrint() {
        if (root != NULL) {
            printHelper(this->root, "", true);
        }
    }

    void rangeAvg(int i, int j) {
        float summ = rangeSum(this->root, i, j);
        float average = summ / (j - i + 1);
        cout << "Average: " << average << endl;
    }
};

int main() {
    RBTree tree;

    //insert starts from index 1
    tree.insert(1, 7);
    tree.insert(1, 3);
    tree.insert(1, 8);
    tree.insert(1, 0);
    tree.insert(2, 2);
    tree.insert(2, 8);
    tree.insert(3, 1);
    tree.insert(2, 6);
    tree.insert(2, 3);
    tree.insert(8, 5);
    tree.insert(11, 20);

    tree.search(4);
    tree.search(10);

    tree.printInOrderleaf();

    cout << endl;
    tree.printInOrder();

    // Easy to visualize the tree
    cout << "\nPretty print:" << endl;
    tree.prettyPrint();

    tree.rangeAvg(2, 5);

    return 0;
}
