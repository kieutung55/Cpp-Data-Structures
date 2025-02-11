#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

/* Recursive function to search target string in given character matrix.
board: given character matrix
r, c: start element of matrix for search (r: row, c:column)
target: string to be searched by
index: this function finds substring ('index'th character to latest character) of target

For example:
find(board, 0, 0, "apple", 0) will return boolean value if there exists "apple" starting with (0, 0) element
find(board, 2, 5, "apple", 2) will return boolean value if there exists "ple" starting with (2, 5) element
*/
bool find(vector<vector<char>> board, int r, int c, string target, int index) {
    if (index == target.length()) {
        return true;
    }

    if (r < 0 || c < 0 || r >= board.size() || c >= board[0].size() || target[index] != board[r][c]) {
        return false;
    }

    // Avoid going back to the previous position
    char temp = board[r][c];
    board[r][c] = ' ';

    // Call recursive function
    bool found = false;
    // There are 4 directions to be searched from current position (r, c)
    // (r-1, c): North, (r, c+1): East, (r+1, c): South, (r, c-1): West
    found = find(board, r - 1, c, target, index + 1);                   // North direction
    if (!found) {                // if not found in North direction
        found = find(board, r, c + 1, target, index + 1);               // East Direction
        if (!found) {           // if not found in East direction
            found = find(board, r + 1, c, target, index + 1);           // South Direction
            if (!found) {       // if not found in South direction
                found = find(board, r, c - 1, target, index + 1);       // West Direction
            }
        }
    }

    board[r][c] = temp; // recover original board

    return found;
}

int main() {
    // Define test cases
    vector<vector<vector<char>>> boards = {
        {{'a', 'b', 'c', 'd', 'e'},
         {'f', 'g', 'h', 'i', 'j'},
         {'k', 'l', 'm', 'n', 'o'},
         {'p', 'q', 'r', 's', 't'},
         {'u', 'v', 'w', 'x', 'y'}},

        {{'a', 'p', 'p', 'l', 'e'},
         {'f', 'g', 'h', 'i', 'j'},
         {'k', 'l', 'm', 'n', 'o'},
         {'p', 'q', 'r', 's', 't'},
         {'u', 'v', 'w', 'x', 'y'}},

        {{'z', 'a', 'b', 'c', 'd'},
         {'e', 'f', 'g', 'h', 'i'},
         {'j', 'k', 'l', 'm', 'n'},
         {'o', 'p', 'q', 'r', 's'},
         {'t', 'u', 'v', 'w', 'x'}},

        {{'t', 'e', 's', 't'},
         {'a', 'b', 'c', 'd'},
         {'e', 'f', 'g', 'h'},
         {'i', 'j', 'k', 'l'}},

        {{'c', 'o', 'd', 'e'},
         {'f', 'g', 'h', 'i'},
         {'j', 'k', 'l', 'm'},
         {'n', 'o', 'p', 'q'}}
    };

    vector<string> targets = {
        "apple",   // Should return true (found at (0, 0))
        "apple",   // Should return true (found at (0, 0))
        "zab",     // Should return false (not found)
        "test",    // Should return true (found at (0, 0))
        "code"     // Should return true (found at (0, 0))
    };

    // Test each case
    for (size_t i = 0; i < boards.size(); i++) {
        bool found = false; // result indicating target exists or not
        vector<vector<char>> board = boards[i];
        string target = targets[i];

        // Iterate for each character in the board
        for (int r = 0; r < board.size(); r++) {
            for (int c = 0; c < board[0].size(); c++) {
                found = find(board, r, c, target, 0);
                if (found) break; // if target string has been found, return the result.
            }
            if (found) break; // if target string has been found, return the result.
        }

        // Output the result for the current test case
        cout << "Searching for \"" << target << "\" in the board: "
            << (found ? "true" : "false") << endl;
    }

    return 0;
}