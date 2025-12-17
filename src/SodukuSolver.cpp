//
// Created by alyss on 8/12/2025.
//

#include <vector>
#include <string>
#include <iostream>
#include <set>
using namespace std;

// 16/12/2025 - 17/12/2025
// LeetCode 37. Soduku Solver
// Write a program to solve a Sudoku puzzle by filling the empty cells.
// A sudoku solution must satisfy all of the following rules:
// Each of the digits 1-9 must occur exactly once in each row.
// Each of the digits 1-9 must occur exactly once in each column.
// Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
// The '.' character indicates empty cells.
// NOTES: see version 1 notes
class SodukuSolver {

//Version 2: 17/12/2025
public:
    void solveSoduku(vector<vector<char>>& board) {
        int r = -1, c = -1;
        if (!findEmpty(board, r, c)) { return; }
            // no empty blocks left, done; In the mean time, mutate r and c to locate the next '.' block

        for (char d = '1'; d <= '9'; d++) {
            if (!isValid(board, r, c, d)) continue;

            board[r][c] = d;
            solveSoduku(board);
            board[r][c] = '.';
        }

    }

private:
    bool isValid(vector<vector<char>>& board, int r, int c, char d) {

        for (int col = 0; col < 9; col++) {
            if (board[r][col] == d) return false;
        }
        for (int row = 0; row < 9; row++) {
            if (board[row][c] == d) return false;
        }
        int blockCol = (int) c / 3;
        int blockRow = (int) r / 3;
        for (int bC = blockCol * 3; bC < blockCol * 3 + 3; bC++) {
            for (int bR = blockRow * 3; bR < blockRow * 3 + 3; bR++) {
                if (board[bR][bC] == d) return false;
            }
        }
        return true;
    }

    bool findEmpty(vector<vector<char>>& board, int r, int c) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    r = i;
                    c = j;
                    return true;
                }
            }
        }
        return false;
    }

/**********************************************************************************************************************/
// Version 1: 16/12/2025
// ERROR 1: declaring global seen sets colSeen, rowSeen, blockSeen. This is because constraints are per row.
//     so rowSeen should be 9 sets, the same for cols and blocks
// ERROR 2: Bad logic flow, we should first limit our attempts to blocks with '.'
//     then for each of these '.' blocks, try 0-9 (outer loop) and query whether filling in a number is valid (satisfies
//     soduku rules.
//
// public:
//     void solveSoduku(vector<vector<char>>& board) {
//
//         set<char> rowSeen, colSeen, blockSeen;
//         for (int i = 0; i < 9; i++) { // fix a row
//             dfsRow(i, rowSeen, colSeen, blockSeen, board);
//         }
//     }
//
//     void dfsRow(int rowNum, set<char>& rowSeen,
//                 set<char>& colSeen, set<char>& blockSeen, vector<vector<char>>& board) {
//         // TERMINATE and POP
//         if (rowNum == 9) { return; } // have filled in all blanks (no more attempts)
//
//         // EXHAUST ALL TENTATIVE SOLUTIONS
//         for (int i = 1; i < 10; i++) { // try every option 0 - 9, choose and put if satisfies soduku rule
//             int num = static_cast<int>(i);
//             if (!fill(i, rowSeen, colSeen, blockSeen))  continue;
//
//             // choose
//             board[rowNum][i] = i;
//             rowSeen.insert(i);
//             colSeen.insert(i);
//             blockSeen.insert(i);
//             // explore
//             dfsRow(rowNum, rowSeen, colSeen, blockSeen, board);
//             // unchoose
//             board[rowNum][i] = '.';
//             rowSeen.erase(i);
//             colSeen.erase(i);
//             blockSeen.erase(i);
//         }
//     }
//
//     void findRowSeen(set<char>& rowSeen, int rowNum, vector<vector<char>>& board) {
//         for (int i = 0; i < 9; i++) {
//             if (board[rowNum][i] != '.') {
//                 rowSeen.insert(board[rowNum][i]);
//             }
//         }
//     }
//
//     void findColSeen(set<char>& colSeen, int colNum, vector<vector<char>>& board) {
//         for (int i = 0; i < 9; i++) {
//             if (board[i][colNum] != '.') {
//                 colSeen.insert(board[i][colNum]);
//             }
//         }
//     }
//
//     void findBlockSeen(set<char>& blockSeen, int rowNum, int colNum, vector<vector<char>>& board) {
//         int blockRow = (int) rowNum / 3;
//         int blockCol = (int) colNum / 3;
//         for (int i = blockRow * 3; i < blockRow * 3 + 3; i++) {
//             for (int j = blockCol * 3; j < blockCol * 3 + 3; j++) {
//                 if (board[i][j] != '.') {
//                     blockSeen.insert(board[i][j]);
//                 }
//             }
//         }
//     }
//
//     bool fill(char num, set<char>& seen1, set<char>& seen2, set<char>& seen3) {
//         return !seen1.count(num) && !seen2.count(num) && !seen3.count(num);
//     }

};
//
// int main() {
//     PalindromePartition test;
//     vector<vector<string>> res = test.partition("aab");
//     for (vector<string> s : res) {
//         for (int i = 0; i < s.size(); i++) {
//             cout << s[i];
//             if (i < s.size() - 1) { cout << ", "; }
//         }
//         cout << "; ";
//     }
//     cout << endl;
// }