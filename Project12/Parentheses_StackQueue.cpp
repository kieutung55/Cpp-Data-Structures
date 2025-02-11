#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// The inputProcessor function reads example strings and stores each non-empty line in a queue, which is returned at the end of the function
queue<string> inputProcessor() {
    queue<string> queueToReturn;

    // Adding example strings to test the functionality
    queueToReturn.push("{ [ ( ) ] }");
    queueToReturn.push("{ [ ( ] }");
    queueToReturn.push("{ ( ) [ ] }");
    queueToReturn.push("{ ( [ ] ) }");
    queueToReturn.push("{ ( ) ( }");

    return queueToReturn;
}

// Following three functions are helper functions for the main validity checking functions

// The matchingParentheses function takes two characters representing an open and closed parenthesis and returns true if they match
bool matchingParentheses(char open, char closed) {
    return (open == '{' && closed == '}') ||
        (open == '[' && closed == ']') ||
        (open == '(' && closed == ')');
}

// The areParentheses function takes two characters and returns true if both characters are open parentheses
bool areParentheses(char one, char two) {
    return ((one == '(') || (one == '[') || (one == '{')) &&
        ((two == '(') || (two == '[') || (two == '{'));
}

// The precedence function takes an open parenthesis character and returns its precedence level
int precedence(char openParen) {
    if (openParen == '{') return 3;
    else if (openParen == '[') return 2;
    else return 1;
}

// Following three functions are main validity-checking functions

// The validParentheses function checks whether its parentheses are balanced and properly nested
bool validParentheses(string toCheck) {
    int size = toCheck.size();
    stack<char> stackOfChars;

    for (int i = 0; i < size; i++) {
        if (toCheck[i] == '(' || toCheck[i] == '[' || toCheck[i] == '{') {
            stackOfChars.push(toCheck[i]);
        }
        else if (toCheck[i] == ')' || toCheck[i] == ']' || toCheck[i] == '}') {
            if (stackOfChars.empty() || !matchingParentheses(stackOfChars.top(), toCheck[i]))
                return false;
            else {
                stackOfChars.pop();
            }
        }
    }
    return stackOfChars.empty(); // Return true if no unmatched parentheses remain
}

// The noDoubleParentheses function checks whether it contains any double parentheses
bool noDoubleParentheses(string toCheck) {
    int size = toCheck.size();
    stack<char> stackOfChars;

    for (int i = 0; i < size; i++) {
        if (!stackOfChars.empty() && areParentheses(stackOfChars.top(), toCheck[i])) {
            return false;
        }
        stackOfChars.push(toCheck[i]);
    }
    return true;
}

// The correctOrder function checks whether its parentheses are in the correct order of precedence
bool correctOrder(string toCheck) {
    int size = toCheck.size();
    stack<char> stackOfChars;

    for (int i = 0; i < size; i++) {
        if (!stackOfChars.empty() && (toCheck[i] == ')' || toCheck[i] == ']' || toCheck[i] == '}')) {
            stackOfChars.pop();
        }

        if (toCheck[i] == '(' || toCheck[i] == '[' || toCheck[i] == '{') {
            if (!stackOfChars.empty() && precedence(toCheck[i]) > precedence(stackOfChars.top())) {
                return false;
            }
            stackOfChars.push(toCheck[i]);
        }
    }

    return true;
}

// Main function for testing
int main() {
    queue<string> queueOfInput = inputProcessor();
    queue<string> queueOfValid;
    queue<string> queueOfInvalid;

    // Separation into a list of valid and invalid strings
    while (!queueOfInput.empty()) {
        string current = queueOfInput.front();
        queueOfInput.pop();

        if (validParentheses(current) && noDoubleParentheses(current) && correctOrder(current)) {
            queueOfValid.push(current);
        }
        else {
            queueOfInvalid.push(current);
        }
    }

    // Print list of valid strings
    if (!queueOfValid.empty()) {
        cout << "Valid:" << endl;
        while (!queueOfValid.empty()) {
            cout << queueOfValid.front() << endl;
            queueOfValid.pop();
        }
    }

    // Print list of invalid strings
    if (!queueOfInvalid.empty()) {
        cout << "Invalid:" << endl;
        while (!queueOfInvalid.empty()) {
            cout << queueOfInvalid.front() << endl;
            queueOfInvalid.pop();
        }
    }

    return 0;
}