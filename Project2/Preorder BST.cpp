#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct node {
    int data;
    node* left;
    node* right;
};

node* newNode(int item) {
    node* temp = new node;
    temp->data = item;
    temp->left = temp->right = nullptr;
    return temp;
}

/* This defines a class named BST that represents a binary search tree.
It has a single member variable, root, which is a pointer to the root node of the tree. */

class BST {
private:
    node* root;

public:
    BST() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void preorder(ostream& file) {
        preorder(file, root, "x");
    }

private:
    /*This is a recursive function that inserts a new node with the given key value into the binary search tree rooted at node.
    If node is nullptr, it creates a new node with newNode function and returns a pointer to it.
    If key is less than the data of node, it inserts the new node into the left subtree of node.
    Otherwise, it inserts the new node into the right subtree of node. The function returns a pointer to the root of the modified subtree. */

    node* insert(node* node, int key) {

        if (node == nullptr) {
            return newNode(key);
        }

        if (key < node->data)
            node->left = insert(node->left, key);

        else
            node->right = insert(node->right, key);

        return node;
    }

/*This is a recursive function that performs a preorder traversal of the binary tree rooted at root.
Printing to the output file the data value of each node, along with a route string that indicates the path from the root to the current node.
The route string is accumulated during the recursive traversal, with an "l" appended to it for every left turn and an "r" appended to it for every right turn.
The function prints the output in the format "[route] data" and moves on to the left and right subtrees of the current node recursively.
If the root is nullptr, the function does nothing. */

    void preorder(ostream& file, node* root, string route) {
        if (root != nullptr) {
            file << "[" << route << "] " << root->data << endl;
            preorder(file, root->left, route + "l");
            preorder(file, root->right, route + "r");
        }
    }
};

int main() {
    const int numFiles = 3; // Adjust based on the number of expected input files

    for (int i = 1; i <= numFiles; ++i) {
        string inputFileName = "input" + to_string(i) + ".txt";
        string outputFileName = "output" + to_string(i) + ".txt";

        // Check if the input file exists
        ifstream checkFile(inputFileName);
        if (checkFile.is_open()) {
            checkFile.close(); // Close the file if it exists

            BST bst;
            ifstream inputFile(inputFileName);
            int value;

            // Read integers from the input file and insert them into the BST
            while (inputFile >> value) {
                bst.insert(value); // Insert into the BST
            }

            inputFile.close();

            // Generate output file with preorder traversal of the BST
            ofstream outputFile(outputFileName);
            if (outputFile.is_open()) {
                bst.preorder(outputFile); // Call preorder traversal
                outputFile.close();
            }
        }
        else {
            cerr << endl;
        }
    }

    return 0;
}