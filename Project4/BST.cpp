// Tung Kieu
// COSC 2436
// Professor Rizk

#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

struct Node {
    string data;
    struct Node* left, * right;
    Node(string data_in) {
        data = data_in;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    Node* root;
    bool is_ascend;     // mirror status, true is small->larger, false is larger->small
public:
    BST() {
        root = nullptr;
        is_ascend = true;
    }
    // insert new node
    void insert(string data_in);

    // print BST tree from most left to most right
    string printLR(Node* root);

    // print BST tree on given level
    string printLevel(Node* root, int given_level, int cur_level);

    // compare two string. If the one is digits and other is string, then return -1
    // if str1 > str2 , return 1. if str1 < str2, return 2. if two are equal, return 0
    int compareString(string str1, string str2);

    Node* getRoot();

    // set Mirror and swap all nodes according to current mirror status
    void setMirror();

    void swapTree(Node* root);
};

// Check if current string is digits
bool is_digits(string str) {
    return str.find_first_not_of("0123456789") == std::string::npos;
}

// ===================== Implementation of Member function ================

void BST::insert(string data_in) {
    Node* new_node = new Node(data_in);
    if (this->root == nullptr) {
        this->root = new_node;
    }
    else {
        Node* prev = nullptr;
        Node* temp = this->root;
        // ------- go to node (here, that is 'prev') to be attach new node -----
        while (temp) {
            int compare_result = this->compareString(temp->data, data_in);  // calculate the order between two strings
            if (compare_result < 0) {   // one is digit while another is not
                return;                 // discard this case
            }
            else {
                prev = temp;
                if (compare_result == 1) {
                    if (this->is_ascend) {      // if left is smaller and right is bigger, add smaller string into left node
                        temp = temp->left;
                    }
                    else {                      // if left is bigger and right is smaller, add smaller string into right node
                        temp = temp->right;
                    }
                }
                else if (compare_result == 2) {
                    prev = temp;
                    if (this->is_ascend) {
                        temp = temp->right;
                    }
                    else {
                        temp = temp->left;
                    }
                }
            }
        }

        // attach new node to 'prev'
        int compare_result = this->compareString(prev->data, data_in);
        if (compare_result < 0) {
            return;
        }
        else {
            if (compare_result == 1) {
                if (this->is_ascend) {
                    prev->left = new_node;
                }
                else {
                    prev->right = new_node;
                }
            }
            else {
                if (this->is_ascend) {
                    prev->right = new_node;
                }
                else {
                    prev->left = new_node;
                }
            }
        }
    }
}

string BST::printLR(Node* cur_root) {
    string result = "";
    if (cur_root == nullptr) return "";

    // first print on left tree of the node 
    result = result + printLR(cur_root->left);

    // then print current node 
    result = result + cur_root->data + " ";

    // last print right child 
    result = result + printLR(cur_root->right);
    return result;
}

string BST::printLevel(Node* cur_root, int given_level, int cur_level = 0) {
    string result = "";
    if (cur_root == nullptr) {
        return "";
    }

    // first print on left tree of the node 
    result = result + printLevel(cur_root->left, given_level, cur_level + 1);

    // then print current node if current level equals to given level
    if (cur_level == given_level) {
        result = result + cur_root->data + " ";
    }

    // last print right child 
    result = result + printLevel(cur_root->right, given_level, cur_level + 1);
    return result;
}

Node* BST::getRoot() {
    return this->root;
}

void BST::setMirror() {
    this->is_ascend = !this->is_ascend;
    swapTree(this->root);
}

// swap all nodes of current BST 
void BST::swapTree(Node* cur_root) {
    if (cur_root == nullptr) {
        return;
    }
    // swap two childs of current root.
    Node* temp = cur_root->left;
    cur_root->left = cur_root->right;
    cur_root->right = temp;

    // Continue swap for child nodes
    swapTree(cur_root->left);
    swapTree(cur_root->right);
}

int BST::compareString(string str1, string str2) {
    bool is_digits1 = is_digits(str1);
    bool is_digits2 = is_digits(str2);
    if (is_digits1 != is_digits2) {
        return -1;
    }
    if (is_digits1) {   // In case of two strings are digits, compare them by numerical order
        int val1 = atoi(str1.c_str());
        int val2 = atoi(str2.c_str());
        if (val1 > val2) {
            return 1;
        }
        else if (val1 < val2) {
            return 2;
        }
        else {
            return 0;
        }
    }
    else {              // In case of two strings are not digits, compare them alphabetically
        if (str1 > str2) {
            return 1;
        }
        else if (str1 < str2) {
            return 2;
        }
        else {
            return 0;
        }
    }
}

// ===================== Main Function ====================
int main() {
    BST bst;

    // Insert test data
    bst.insert("20");
    bst.insert("10");
    bst.insert("30");
    bst.insert("5");
    bst.insert("15");

    // Print the BST in left-to-right order
    cout << "In-Order Print (Left to Right): " << bst.printLR(bst.getRoot()) << endl;

    // Print nodes at level 0
    cout << "Nodes at Level 0: " << bst.printLevel(bst.getRoot(), 0) << endl;

    // Print nodes at level 1
    cout << "Nodes at Level 1: " << bst.printLevel(bst.getRoot(), 1) << endl;

    // Print nodes at level 2
    cout << "Nodes at Level 2: " << bst.printLevel(bst.getRoot(), 2) << endl;

    // Set mirror and print again
    bst.setMirror();
    cout << "In-Order Print After Mirror (Right to Left): " << bst.printLR(bst.getRoot()) << endl;

    return 0;
}