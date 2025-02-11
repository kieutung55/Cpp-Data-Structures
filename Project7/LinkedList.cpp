#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

template <typename T>
struct T_Node {
    T data;
    struct T_Node* next;
    T_Node(T value) {
        data = value;
        next = nullptr;
    }
    T_Node() {
        next = nullptr;
    }
};

template <typename T>
class T_LinkedList {
private:
    T_Node<T>* head;
    size_t size;

public:
    T_LinkedList() {
        head = nullptr;
        size = 0;
    }

    // Add new node at given position
    void addAtPos(int pos, T value);
    // Add new node at head or tail depending on flag 'is_head'
    void add(T value, bool is_head = true);

    // Remove node at given position
    void removeAtPos(int pos);
    // Remove node at head or tail depending on flag 'is_head'
    void remove(bool is_head = true);

    // Print all nodes on console
    void print();
};

template<typename T>
void T_LinkedList<T>::addAtPos(int pos, T value) {
    T_Node<T>* new_node = new T_Node<T>(value);

    if (this->head == nullptr) {
        this->head = new_node;
        this->size++;
        return;
    }

    if (pos == 0) {
        new_node->next = this->head;
        this->head = new_node;
    }
    else {
        T_Node<T>* cur_node = this->head;
        int id = 1;
        while (cur_node->next != nullptr && id < pos) {
            cur_node = cur_node->next;
            id++;
        }
        new_node->next = cur_node->next;
        cur_node->next = new_node;
    }
    this->size++;
}

template<typename T>
void T_LinkedList<T>::add(T value, bool is_head) {
    if (is_head) {
        this->addAtPos(0, value);
    }
    else {
        this->addAtPos(this->size, value);
    }
}

template<typename T>
void T_LinkedList<T>::removeAtPos(int pos) {
    if (this->head == nullptr) {
        return;
    }

    if (pos == 0) {
        this->head = this->head->next;
    }
    else {
        T_Node<T>* cur_node = this->head;
        T_Node<T>* before_node = nullptr;
        int id = 0;
        while (cur_node->next != nullptr && id < pos) {
            before_node = cur_node;
            cur_node = cur_node->next;
            id++;
        }
        if (before_node != nullptr) {
            before_node->next = cur_node->next;
        }
    }
    this->size--;
}

template<typename T>
void T_LinkedList<T>::remove(bool is_head) {
    if (is_head) {
        this->removeAtPos(0);
    }
    else {
        this->removeAtPos(this->size - 1);
    }
}

template <typename T>
void T_LinkedList<T>::print() {
    if (this->head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    else {
        T_Node<T>* cu = this->head;
        while (cu != nullptr) {
            cout << cu->data << " ";
            cu = cu->next;
        }
        cout << endl;
    }
}

// ==================== Main Function ====================
int main() {
    // Create linked lists for different data types
    T_LinkedList<int> int_llist;          // LinkedList for type 'int' 
    T_LinkedList<string> str_llist;       // LinkedList for type 'string' 
    T_LinkedList<char> char_llist;        // LinkedList for type 'char' 

    // Example 1: Integer Linked List
    int_llist.add(1, true);  // Add 1 at head
    int_llist.add(2, false); // Add 2 at tail
    int_llist.addAtPos(1, 3); // Add 3 at position 1
    cout << "Integer Linked List: ";
    int_llist.print(); // Should print: 1 3 2

    // Example 2: String Linked List
    str_llist.add("Hello", true); // Add "Hello" at head
    str_llist.add("World", false); // Add "World" at tail
    str_llist.addAtPos(1, "C++");  // Add "C++" at position 1
    cout << "String Linked List: ";
    str_llist.print(); // Should print: Hello C++ World

    // Example 3: Character Linked List
    char_llist.add('A', true); // Add 'A' at head
    char_llist.add('B', false); // Add 'B' at tail
    char_llist.addAtPos(1, 'C'); // Add 'C' at position 1
    cout << "Character Linked List: ";
    char_llist.print(); // Should print: A C B

    // Example 4: Remove elements from Integer Linked List
    int_llist.remove(true); // Remove head
    cout << "After removing head from Integer Linked List: ";
    int_llist.print(); // Should print: 3 2

    int_llist.remove(false); // Remove tail
    cout << "After removing tail from Integer Linked List: ";
    int_llist.print(); // Should print: 3

    // Example 5: Remove from specific position in String Linked List
    str_llist.removeAtPos(1); // Remove at position 1
    cout << "After removing from position 1 in String Linked List: ";
    str_llist.print(); // Should print: Hello World

    return 0;
}