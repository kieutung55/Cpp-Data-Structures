#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

struct Node {
    int data;
    struct Node* left, * right;
    Node(int data_in) {
        data = data_in;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    Node* root;

public:
    BST() {
        root = nullptr;
    }
    void insert(int data_in);
    void remove(int data);
    Node* deleteNode(Node* root, int data);
    string printInorder(Node* root);
    string printPreorder(Node* root);
    string printPostorder(Node* root);
    Node* getRoot();
};

// ===================== Implementation of Member function ================

void BST::insert(int data_in) {
    Node* new_node = new Node(data_in);
    if (this->root == nullptr) {
        this->root = new_node;
    }
    else {
        Node* prev = nullptr;
        Node* temp = this->root;
        while (temp) {
            if (temp->data > data_in) {
                prev = temp;
                temp = temp->left;
            }
            else if (temp->data < data_in) {
                prev = temp;
                temp = temp->right;
            }
        }
        if (prev->data > data_in)
            prev->left = new_node;
        else
            prev->right = new_node;
    }
}

void BST::remove(int data) {
    this->root = deleteNode(this->root, data);
}

Node* BST::deleteNode(Node* root, int data) {
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
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        else if (root->left == nullptr) {
            Node* right_node = root->right;
            delete root;
            return right_node;
        }
        else if (root->right == nullptr) {
            Node* left_node = root->left;
            delete root;
            return left_node;
        }
        else {
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
    }
    return root;
}

string BST::printInorder(Node* cur_root) {
    string result = "";
    if (cur_root == nullptr) return "";

    result = result + printInorder(cur_root->left);
    result = result + to_string(cur_root->data) + " ";
    result = result + printInorder(cur_root->right);
    return result;
}

string BST::printPreorder(Node* cur_root) {
    string result = "";
    if (cur_root == nullptr) return "";

    result = result + to_string(cur_root->data) + " ";
    result = result + printPreorder(cur_root->left);
    result = result + printPreorder(cur_root->right);
    return result;
}

string BST::printPostorder(Node* cur_root) {
    string result = "";
    if (cur_root == nullptr) return "";

    result = result + printPostorder(cur_root->left);
    result = result + printPostorder(cur_root->right);
    result = result + to_string(cur_root->data) + " ";
    return result;
}

Node* BST::getRoot() {
    return this->root;
}

// ==================== Main Function ====================
int main() {
    BST bst = BST();

    // Example 1: Insert nodes
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);

    // Print traversals after insertion
    cout << "Inorder after insertions: " << bst.printInorder(bst.getRoot()) << endl;  // Should print: 2 3 4 5 7
    cout << "Preorder after insertions: " << bst.printPreorder(bst.getRoot()) << endl; // Should print: 5 3 2 4 7
    cout << "Postorder after insertions: " << bst.printPostorder(bst.getRoot()) << endl; // Should print: 2 4 3 7 5

    // Example 2: Remove a leaf node
    bst.remove(2);
    cout << "Inorder after removing 2: " << bst.printInorder(bst.getRoot()) << endl; // Should print: 3 4 5 7

    // Example 3: Remove a node with one child
    bst.remove(3);
    cout << "Inorder after removing 3: " << bst.printInorder(bst.getRoot()) << endl; // Should print: 4 5 7

    // Example 4: Remove a node with two children
    bst.remove(5);
    cout << "Inorder after removing 5: " << bst.printInorder(bst.getRoot()) << endl; // Should print: 4 7

    // Example 5: Remove the last remaining node
    bst.remove(7);
    bst.remove(4);
    cout << "Inorder after removing all nodes: " << bst.printInorder(bst.getRoot()) << endl; // Should print an empty line

    return 0;
}