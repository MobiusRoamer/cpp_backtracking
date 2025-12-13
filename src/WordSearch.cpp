//
// Created by alyss on 8/12/2025.
//

#include <vector>
#include <string>
#include <stack>
#include <iostream>
using namespace std;

// 13/12/2025
// Given an m x n grid of characters board and a string word, return true if word exists in the grid.
//
// The word can be constructed from letters of sequentially adjacent cells,
// where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.
/*********************************************************************************************************************/
// NOTES:
// The control flow (using return type boolean in dfs()) is very similar to ".../src/"SumPath.cpp"
//
// (1) Stepping through a 2D array, we usually invoke an offset approach where we define the xStep and yStep within the class
// The trick is to prevent the dfs from repeating the same steps (traversing the path we have already checked. This can be prevented
//  by adding two parameters (xParent, yParent) when performing the search
//
// (2) Stack overflow problems with the base case stopping condition in dfs().
// Think: Should we stop the process upon the word length reaching
// the target word length, or by instance equality that our cumulative string == word?
//
// (3) Question: Can we modularize dfs()? Break it up into helpers?

class WordSearch {

private:
    int xStep[4] = {-1, 1, 0, 0}, yStep[4] = {0, 0, -1, 1};

public:
    bool wordSearch(vector<vector<char>>& board, const string& word) {
        int rows = (int) board.size();
        int cols = (int) board[0].size();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                string s;
                s.push_back(board[i][j]); // ERROR 1: forgot to add current char
                if (dfs(i, j, 0, -1, -1, board, word, s)) { return true; }
            }
        }
        return false;

    }

private:
    bool dfs(int row, int col, int currIndex, int parentX, int parentY,
             const vector<vector<char>>& board, const string& word, string s) {
        // ERROR 2: should not check for s == word, but to stop the search using the currIndex, otherwise we run into stack overflow
        //          offload the check equality logic to inside the loop (line 59)!
        // if (s == word) return true;
        if (currIndex == word.size()) return true;

        for (int i = 0; i < 4; i++) {
            if (xStep[i] == parentX && yStep[i] == parentY) continue; // don't look back!
                                                                      // Otherwise, we would be walking the path we came from!
            int xCoord = col + xStep[i], yCoord = row + yStep[i];

            if (xCoord >= board[0].size() || xCoord < 0 || yCoord >= board.size() || yCoord < 0) continue; // boundaries of the board

            char addChar = board[yCoord][xCoord];

            // backtracking
            if (word[currIndex] == addChar) {
                s.push_back(addChar);
                if (dfs(yCoord, xCoord, currIndex + 1, -xStep[i], -yStep[i], board, word, s)) {
                    // ERROR 3: forgot to invert the sign for parent coordinate, they should be negated to indicate opposite direction of
                    // where we came from
                    return true;
                }
                s.pop_back();
            }
        }
        return false;
    }

};

int main() {
    WordSearch test;
    vector<vector<char>> board;
    board.push_back({'A','B','C','E'});
    board.push_back({'S','F','C','S'});
    board.push_back({'A','D','E','E'});
    cout << test.wordSearch(board, "ABCCED") << endl;
}