#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

//================ Auxiliary functions ==================
/*
return string surrounding by 'from' and 'to'
for example, str = "hello (world)", from = '(', to = ')', then result = "world"
*/
string getInner(string str, char from, char to) {
    string result;
    stringstream result_stream;
    bool is_in = false;
    size_t pos_from = str.find(from);
    size_t pos_to = str.find(to);
    if (pos_from == string::npos || pos_to == string::npos) {
        return str;
    }
    for (unsigned int i = 0; i <= str.length(); i++) {
        if (str[i] == to) {
            is_in = false;
            result = result_stream.str();
            break;
        }
        if (is_in) {
            result_stream << str[i];
        }
        if (str[i] == from) {
            is_in = true;
        }
    }
    return result;
}

/* Remove latest trailing characters ' ', '\0' , '\r' and '\n' */
string trim(string str) {
    string str_temp = str;
    for (int i = str.size() - 1; i >= 0; i--) {
        if (str[i] == '\r' || str[i] == '\n' || str[i] == '\0' || str[i] == ' ') {
            str_temp = str.substr(0, i);
        }
        else {
            break;
        }
    }
    return str_temp;
}

// ------ AVL Tree ---------

struct Node {
    int data;
    struct Node* left, * right;
    Node(int data_in) {
        data = data_in;
        left = nullptr;
        right = nullptr;
    }
};

class AVL_BST {
private:
    Node* root;

    Node* insertNode(Node* node, int data);
    Node* deleteNode(Node* node, int data);
    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    Node* singleRightRotation(Node* node);
    Node* singleLeftRotation(Node* node);
    Node* rightLeftRotation(Node* node);
    Node* leftRightRotation(Node* node);

public:
    AVL_BST() {
        root = nullptr;
    }
    void insert(int data);
    void remove(int data);
    string printLevel(Node* root, int given_level, int cur_level);
    void printAVL();
    Node* getRoot();
};

// ===================== Implementation of Member function ================

Node* AVL_BST::insertNode(Node* node, int data) {
    if (node == nullptr) {
        node = new Node(data);
    }
    else {
        if (data < node->data) {    // left case
            node->left = this->insertNode(node->left, data);
            int balance = this->getBalanceFactor(node);
            if (balance > 1) {
                if (data < node->left->data) {
                    node = this->singleRightRotation(node);
                }
                else {
                    node = this->leftRightRotation(node);
                }
            }
        }
        else if (node->data < data) {      // right case
            node->right = this->insertNode(node->right, data);
            int balance = this->getBalanceFactor(node);
            if (balance < -1) {
                if (node->right->data < data) {
                    node = this->singleLeftRotation(node);
                }
                else {
                    node = this->rightLeftRotation(node);
                }
            }
        }
    }
    return node;
}

Node* AVL_BST::deleteNode(Node* root, int data) {
    if (root == nullptr) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    }
    else {
        if (root->left != nullptr and root->right != nullptr) {
            Node* succParent = root;
            Node* succ = root->right;
            while (succ->left != nullptr) {
                succParent = succ;
                succ = succ->left;
            }
            if (succParent != root)
                succParent->left = succ->right;
            else
                succParent->right = succ->right;
            root->data = succ->data;
            delete succ;
        }
        else {
            if (root->left == nullptr)
                root = root->right;
            else if (root->right == nullptr)
                root = root->left;
        }
    }
    int balance = this->getBalanceFactor(root);
    if (balance > 1) {
        int left_balance = this->getBalanceFactor(root->left);
        if (left_balance >= 0) {
            root = this->singleRightRotation(root);
        }
        else {
            root = this->leftRightRotation(root);
        }
    }
    else if (balance < -1) {
        int right_balance = this->getBalanceFactor(root->right);
        if (right_balance <= 0) {
            root = this->singleLeftRotation(root);
        }
        else {
            root = this->rightLeftRotation(root);
        }
    }
    return root;
}

void AVL_BST::insert(int data) {
    this->root = insertNode(this->root, data);
}
void AVL_BST::remove(int data) {
    this->root = deleteNode(this->root, data);
}

// get height of given node
int AVL_BST::getHeight(Node* node) {
    if (node == nullptr) {
        return -1;
    }
    int left_height = getHeight(node->left);
    int right_height = getHeight(node->right);
    return max(left_height, right_height) + 1;
}

// get balance factor of given node
int AVL_BST::getBalanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return this->getHeight(node->left) - this->getHeight(node->right);
}

// Rotation functions
Node* AVL_BST::singleRightRotation(Node* A) {
    Node* B = A->left;
    Node* T3 = B->right;
    A->left = T3;
    B->right = A;
    return B;
}

Node* AVL_BST::singleLeftRotation(Node* A) {
    Node* B = A->right;
    Node* T2 = B->left;
    B->left = A;
    A->right = T2;
    return B;
}

Node* AVL_BST::rightLeftRotation(Node* A) {
    Node* B = A->right;
    Node* updated_B = this->singleRightRotation(B);
    A->right = updated_B;
    return this->singleLeftRotation(A);
}

Node* AVL_BST::leftRightRotation(Node* A) {
    Node* B = A->left;
    Node* updated_B = this->singleLeftRotation(B);
    A->left = updated_B;
    return this->singleRightRotation(A);
}

string AVL_BST::printLevel(Node* cur_root, int given_level, int cur_level = 0) {
    string result = "";
    if (cur_root == nullptr) {
        return "";
    }

    result = result + this->printLevel(cur_root->left, given_level, cur_level + 1);
    if (cur_level == given_level) {
        result = result + to_string(cur_root->data) + " ";
    }
    result = result + printLevel(cur_root->right, given_level, cur_level + 1);
    return result;
}

void AVL_BST::printAVL() {
    int height = this->getHeight(this->root);
    for (int i = 0; i <= height; i++) {
        string level_str = this->printLevel(this->root, i, 0);
        level_str = trim(level_str);
        cout << level_str << endl;
    }
}

Node* AVL_BST::getRoot() {
    return this->root;
}

// ===================== Main Function ====================
int main() {
    AVL_BST avl_tree;

    // Insert test data
    avl_tree.insert(30);
    avl_tree.insert(20);
    avl_tree.insert(10);
    avl_tree.insert(40);
    avl_tree.insert(50);

    // Print AVL tree level by level
    cout << "AVL Tree after insertions:" << endl;
    avl_tree.printAVL();

    // Remove a node
    avl_tree.remove(20);
    cout << "\nAVL Tree after removing 20:" << endl;
    avl_tree.printAVL();

    // Remove another node
    avl_tree.remove(30);
    cout << "\nAVL Tree after removing 30:" << endl;
    avl_tree.printAVL();

    // Remove another node
    avl_tree.remove(10);
    cout << "\nAVL Tree after removing 10:" << endl;
    avl_tree.printAVL();

    // Final state of the AVL Tree
    cout << "\nFinal AVL Tree:" << endl;
    avl_tree.printAVL();

    return 0;
}