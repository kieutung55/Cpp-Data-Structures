#include <iostream>
#include <algorithm>

using namespace std;

/* This defines a struct named node that represents a binary tree node.
   It contains an integer data and two pointers, left and right, which point to the left and right child nodes respectively. */
struct node {
    int data;
    node* left;
    node* right;
};

/* This function creates a new node with data set to the given item
   and its left and right pointers set to nullptr. */
node* newNode(int item) {
    node* temp = new node;
    temp->data = item;
    temp->left = temp->right = nullptr;
    return temp;
}

/* This defines a class named BST that represents a binary search tree.
   It has a single member variable, root, which is a pointer to the root node of the tree. */
class BST {
    node* root;
};

/* This is a recursive function that inserts a new node with the given key value into the binary search tree rooted at node.
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

/* This is a recursive function that performs a preorder traversal of the binary tree rooted at root.
   Printing to the console the data value of each node, along with a route string that indicates the path from the root to the current node.
   The route string is accumulated during the recursive traversal, with an "l" appended to it for every left turn and an "r" appended to it for every right turn.
   The function prints the output in the format "[route] data" and moves on to the left and right subtrees of the current node recursively.
   If the root is nullptr, the function does nothing. */
void preorder(ostream& output, node* root, string route) {
    if (root != nullptr) {
        output << "[" << route << "] " << root->data << endl;
        preorder(output, root->left, route + "l");
        preorder(output, root->right, route + "r");
    }
}

// Main function for testing
int main() {
    node* root = nullptr;

    // Example integers to insert into the BST
    int examples[] = { 50, 30, 70, 20, 40 }; // Five example values

    // Insert each example into the BST
    for (int value : examples) {
        root = insert(root, value);
    }

    // Preorder traversal
    cout << "Preorder traversal of the BST:" << endl;
    preorder(cout, root, "x");

    return 0;
}