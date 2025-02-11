#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Node {
    int command;
    int priority;
    struct Node* next;
    Node(int c, int p) {
        command = c;
        priority = p;
        next = nullptr;
    }
    Node() {
        command = -1000;
        priority = -1000;
        next = nullptr;
    }
};

class PriorityQueue {
private:
    Node* head;

public:
    PriorityQueue() {
        head = nullptr;
    }
    // Return command of head node
    int peek();

    // Pop head node
    void pop();

    // Add new node according to its priority    
    void add(int c, int p);

    bool isEmpty();
};

// ===================== Implementation of Member function ================

int PriorityQueue::peek() {
    if (this->head == nullptr) {
        return -10000;
    }
    else {
        return this->head->command;
    }
}

void PriorityQueue::pop() {
    if (this->head != nullptr) {
        this->head = this->head->next;
    }
}

/*
    Add new node according to its priority in the queue
*/
void PriorityQueue::add(int c, int p) {
    Node* temp = new Node(c, p);
    if (this->head == nullptr) {
        this->head = temp;
        return;
    }
    Node* start = this->head;
    if (this->head->priority > p) {
        temp->next = this->head;
        this->head = temp;
    }
    else {
        while (start->next != nullptr && start->next->priority < p) {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
}

bool PriorityQueue::isEmpty() {
    return this->head == nullptr;
}

// ==================== Main Function ====================
int main() {
    PriorityQueue p_queue = PriorityQueue();

    // Example commands with priorities
    // Format: (command, priority)
    // Commands: close(0), open(1), lock(2), unlock(3)
    p_queue.add(1, 2); // open with priority 2
    p_queue.add(3, 1); // unlock with priority 1
    p_queue.add(0, 3); // close with priority 3
    p_queue.add(2, 4); // lock with priority 4
    p_queue.add(1, 0); // open with priority 0

    int open_status = 0;    // 0: closed, 1: opened
    int lock_status = 1;    // 0: locked, 1: unlocked

    // Process commands in order of priority
    while (!p_queue.isEmpty()) {
        int command = p_queue.peek();
        p_queue.pop();

        if (command == 2) {         // lock the door
            lock_status = 0;
        }
        else if (command == 3) {  // unlock the door
            lock_status = 1;
        }
        else if (command == 0) {  // close door
            if (lock_status == 1) {
                open_status = 0;
            }
        }
        else if (command == 1) {  // open the door
            if (lock_status == 1) {
                open_status = 1;
            }
        }
    }

    // Output result
    if (open_status == 0) {
        cout << "The door is closed." << endl;
    }
    else {
        cout << "The door is open." << endl;
    }

    return 0;
}