#include <iostream>
#include <map>
#include <algorithm>
#include <sstream> // Include this for istringstream

using namespace std;

//------------- Print result -------------------//
void printInfo(map<string, int> orderedMap) {
    bool is_valid = false;

    for (const auto& pair : orderedMap) {
        if (pair.second > 1) {
            is_valid = true;
        }
    }

    if (is_valid) {
        cout << "True" << endl;
        for (const auto& pair : orderedMap) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }
    else {
        cout << "False" << endl;
    }
}

void processEmail(const string& email) {
    map<string, int> orderedMap;  // Create orderedMap
    string word;
    int email_num = 0;
    istringstream emailStream(email); // Create an istringstream from the email

    while (emailStream >> word) {
        // Clean up the word
        word.erase(remove(word.begin(), word.end(), ','), word.end());
        word.erase(remove(word.begin(), word.end(), '!'), word.end());
        word.erase(remove(word.begin(), word.end(), '"'), word.end());
        word.erase(remove(word.begin(), word.end(), '.'), word.end());
        word.erase(remove(word.begin(), word.end(), '?'), word.end());
        word.erase(remove(word.begin(), word.end(), '~'), word.end());

        // Transform word to lowercase characters
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (word == "dear") {
            if (email_num > 0) {
                printInfo(orderedMap);
                orderedMap.clear();
            }
            email_num++;
            continue;
        }

        // Count the words
        if (orderedMap.count(word) > 0) {
            orderedMap[word]++;
        }
        else {
            orderedMap[word] = 1;
        }
    }

    // Print the last email's word count
    if (email_num > 0) {
        printInfo(orderedMap);
    }
}

int main() {
    // Example email texts
    string email1 = "Dear John,\nI hope you are doing well! I wanted to check in on you. I hope to hear from you soon.";
    string email2 = "Dear Alice,\nThank you for your email! I appreciate your help.";
    string email3 = "Dear Bob,\nLet's meet for a coffee. Coffee is great!";
    string email4 = "Dear Charlie,\nHow are you? Are you interested in the project?";
    string email5 = "Dear David,\nI hope you enjoy the weekend! Enjoy!";

    // Process each email example
    processEmail(email1);
    processEmail(email2);
    processEmail(email3);
    processEmail(email4);
    processEmail(email5);

    return 0;
}