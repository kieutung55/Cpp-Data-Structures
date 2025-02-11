#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

struct Person {
    string name;
    int black_req;
    int red_req;
    struct Person* next;
};

struct Card {
    string color;
    int card_num;
    struct Card* next;
};

class MyQueue {
private:
    Person* head;
    size_t size;

public:
    MyQueue() {
        head = nullptr;
        size = 0;
    }

    void push(string name, int black_req, int red_req);
    Person* pop();
    size_t getSize();
};

class MyStack {
private:
    Card* head;

public:
    MyStack() {
        head = nullptr;
    }

    void push(string color, int card_num);
    Card* pop();
};

// ===================== Implementation of MyQueue ====================
void MyQueue::push(string name, int black_req, int red_req) {
    Person* temp = new Person();
    temp->name = name;
    temp->black_req = black_req;
    temp->red_req = red_req;
    temp->next = nullptr;

    if (this->head == nullptr) {
        this->head = temp;
    }
    else {
        Person* cu = this->head;
        while (cu->next != nullptr) {
            cu = cu->next;
        }
        cu->next = temp;
    }
    this->size++;
}

Person* MyQueue::pop() {
    if (this->head == nullptr) {
        return nullptr;
    }
    else {
        Person* temp = this->head;
        this->head = this->head->next;
        this->size--;
        return temp;
    }
}

size_t MyQueue::getSize() {
    return this->size;
}

// ===================== Implementation of MyStack ====================
void MyStack::push(string color, int card_num) {
    Card* temp = new Card();
    temp->color = color;
    temp->card_num = card_num;
    temp->next = nullptr;

    if (this->head == nullptr) {
        this->head = temp;
    }
    else {
        temp->next = this->head;
        this->head = temp;
    }
}

Card* MyStack::pop() {
    if (this->head == nullptr) {
        return nullptr;
    }
    else {
        Card* temp = this->head;
        this->head = this->head->next;
        return temp;
    }
}

// ===================== Auxiliary functions ====================
string trim(string str) {
    return str.erase(str.find_last_not_of(" \n\r\t") + 1);
}

vector<string> split(string str, char del) {
    vector<string> tokens;
    stringstream token_stream(str);
    string token;
    while (getline(token_stream, token, del)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    // Create the queue and stack
    MyQueue person_queue;
    MyStack card_stack;

    // Test data
    // Adding people to the queue
    person_queue.push("Alice", 5, 5);  // Total = 10
    person_queue.push("Bob", 3, 7);    // Total = 10
    person_queue.push("Charlie", 6, 4); // Total = 10
    person_queue.push("David", 2, 8);   // Total = 10
    person_queue.push("Eve", 1, 9);     // Total = 10

    // Adding cards to the stack
    card_stack.push("B", 3);
    card_stack.push("R", 2);
    card_stack.push("B", 3);
    card_stack.push("R", 1);
    card_stack.push("B", 4);

    // Processing the queue and stack
    size_t queue_len = person_queue.getSize();
    bool is_burn = false;
    int repeat_num = 0;
    string prev_color = "";
    int prev_card_num = -10;

    while (true) {
        Card* current = card_stack.pop();
        if (current == nullptr) {
            break;
        }

        string color = current->color;
        int card_num = current->card_num;

        if (color == prev_color && card_num == prev_card_num) {
            repeat_num++;
            if (repeat_num >= queue_len) {
                is_burn = true;
                repeat_num = 0;
            }
        }
        else {
            prev_color = color;
            prev_card_num = card_num;
        }

        Person* person = person_queue.pop();
        if (person == nullptr) {
            break;
        }

        string name = person->name;
        int black_req = person->black_req;
        int red_req = person->red_req;

        if (color == "B") {
            int black_remain = black_req - card_num;
            if (black_remain < 0) {
                black_req = 0;
                card_num = abs(black_remain);
                if (!is_burn) {
                    card_stack.push(color, card_num);
                }
            }
            else {
                black_req = black_remain;
            }
            person_queue.push(name, black_req, red_req);
        }
        else if (color == "R") {
            int red_remain = red_req - card_num;
            if (red_remain < 0) {
                red_req = 0;
                card_num = abs(red_remain);
                if (!is_burn) {
                    card_stack.push(color, card_num);
                }
            }
            else {
                red_req = red_remain;
            }
            person_queue.push(name, black_req, red_req);
        }
    }

    // Output results
    while (true) {
        Person* person = person_queue.pop();
        if (person == nullptr) {
            break;
        }
        string name = person->name;
        int black_req = person->black_req;
        int red_req = person->red_req;
        if (black_req != 0 || red_req != 0) {
            cout << name << " - Black: " << black_req << ", Red: " << red_req << endl;
        }
    }

    return 0;
}
