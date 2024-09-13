#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

//Following three functions are helper functions for the main validity checking functions

//The matchingParentheses function takes two characters representing an open and closed parenthesis and returns true if they match
bool matchingParentheses(char open, char closed) 
{
    if (open == '{' && closed == '}')
        return true;
    else if (open == '[' && closed == ']')
        return true;
    else if (open == '(' && closed == ')')
        return true;
    else
        return false;
}

//The areParentheses function takes two characters and returns true if both characters are open parentheses
bool areParentheses(char one, char two) {
    bool charOneParentheses = (one == '(') || (one == '[') || (one == '{');
    bool charTwoParentheses = (two == '(') || (two == '[') || (two == '{');

    //Returns true if both are a form of parentheses
    return charOneParentheses && charTwoParentheses;
}

/*The precedence function takes an open parenthesis character and returns its precedence level(3 for '{', 2 for '[', and 1 for '(', since '{' has the highest precedence)
This function should only receive '{', '[', '('—hence, the default case is '(' */
int precedence(char openParen) {
        if (openParen == '{')
            return 3;
        else if (openParen == '[')
            return 2;
        else
            return 1;
    }

//Following three functions are main validity-checking functions

/*The validParentheses function checks whether its parentheses are balanced and properly nested.
It uses a stack to keep track of the open parentheses encountered and matches them with the corresponding closing parentheses.
If a closing parenthesis is encountered without a matching open parenthesis, the function returns false*/
bool validParentheses(string toCheck)
{
    int size = toCheck.size();
    stack<char> stackOfChars;

    for (int i = 0; i < size; i++)
    {
        //will push open parentheses
        if (toCheck[i] == '(' || toCheck[i] == '[' || toCheck[i] == '{')
            stackOfChars.push(toCheck[i]);
        //branches here if closed parenthesis encountered
        else if (toCheck[i] == ')' || toCheck[i] == ']' || toCheck[i] == '}')
        {
            //first arg should be open parentheses
            //second arg should be matching closed parentheses
            //else exits function and returns false
            if (stackOfChars.empty() || !matchingParentheses(stackOfChars.top(), toCheck[i]))
                return false;
            else
            {
                stackOfChars.pop();
            }
        }
    }
    //if no errors encountered, will return true
    return true;
}

/* The noDoubleParentheses function takes a string and checks whether it contains any double parentheses.
It uses a stack to keep track of the previous character encountered and compares it with the current character.
If both are parentheses, the function returns false */
bool noDoubleParentheses(string toCheck)
{
    int size = toCheck.size();
    stack<char> stackOfChars;

    for (int i = 0; i < size; i++)
    {
        //Compares two previous character of string
        //with current character of string
        //if both are parentheses, double parentheses found
        if (!stackOfChars.empty() && areParentheses(stackOfChars.top(), toCheck[i]))
        {
            return false;
        }
        stackOfChars.push(toCheck[i]);
    }
    //if no errors encountered, will return true—no double parentheses
    return true;
}

/*The correctOrder function takes a string and checks whether its parentheses are in the correct order of precedence.
It uses a stack to keep track of the open parentheses encountered and compares the precedence level of the current open parenthesis with the top of the stack*/
bool correctOrder(string toCheck) {
    stack<char> stackOfChars;
    for (char ch : toCheck) {
        if (ch == ')' || ch == ']' || ch == '}') {
            if (!stackOfChars.empty()) {
                stackOfChars.pop();
            }
        }
        else if (ch == '(' || ch == '[' || ch == '{') {
            if (!stackOfChars.empty() && precedence(ch) > precedence(stackOfChars.top())) {
                return false;
            }
            stackOfChars.push(ch);
        }
    }
    return true;
}

void processInputFile(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    if (!inputFile.is_open()) {
        cerr << "Error opening input file: " << inputFileName << endl;
        return;
    }

    string input;
    while (getline(inputFile, input)) { // Read every line from the input file
        // Trim leading spaces
        input.erase(0, input.find_first_not_of(" \n\r\t"));

        bool isValid = validParentheses(input);
        bool noDoubles = noDoubleParentheses(input);
        bool correctOrd = correctOrder(input);

        outputFile << "Input: " << input << endl;
        outputFile << "Valid Parentheses: " << (isValid ? "Yes" : "No") << endl;
        outputFile << "No Double Parentheses: " << (noDoubles ? "Yes" : "No") << endl;
        outputFile << "Correct Order: " << (correctOrd ? "Yes" : "No") << endl;
        outputFile << "----------------------" << endl;
    }

    inputFile.close();
    outputFile.close();
}

int main() {
    // Define input and output file names
    const int numFiles = 10; // Adjust based on the number of input files
    for (int i = 1; i <= numFiles; ++i) {
        string inputFileName = "input" + to_string(i) + ".txt";
        string outputFileName = "output" + to_string(i) + ".txt";

        // Check if the input file exists
        ifstream checkFile(inputFileName);
        if (checkFile.is_open()) {
            checkFile.close(); // Close the file if it exists
            processInputFile(inputFileName, outputFileName); // Process the file
        }
        else {
            cerr;
        }
    }

    return 0;
}