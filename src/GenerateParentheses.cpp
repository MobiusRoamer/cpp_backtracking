//
// Created by alyss on 8/12/2025.
//

#include <vector>
#include <string>
#include <stack>
#include <iostream>
using namespace std;

// 12/12/2025
// Leetcode 22
// Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
// Example:
//  Input: n = 3
//  Output: ["((()))","(()())","(())()","()(())","()()()"]
//  Observation simplifies the problem!
/*********************************************************************************************************************/
// NOTES:
// Notice the starting bracket has to be '(', and the ending bracket has to be ')'
// it seems like we can then seek all permutations of an equal number of left and right brackets
// in between the start and the end,
// but this is incorrect because we cannot have "())(()"
//
// A trick with parentheses is to use two stacks:
//      one containing left brackets and the other one containing right brackets, called left and right stacks
// Backtracking is a binary tree where at each node we decide whether to pop the left or right stack and add the popped
// element to the string
// The key decision at every level is whether to add one more left or right
// to avoid getting ()) we can only add a right when left brackets in the path (see line 42)

class GenerateParentheses {
public:
    vector<string> generateParentheses(int n) {
        if (n == 0) return {};

        vector<string> out;
        string path;
        stack<string> s1, s2;
        for (int i = 0; i < n; i++) { s1.emplace("("); s2.emplace(")"); }
        dfs(out, path, s1, s2, n);
        return out;
    }

private:
    void dfs(vector<string>& out, string& path, stack<string>& left, stack<string>& right, int n) {

        if (path.size() == 2 * n) { out.push_back(path); return; }

        if (right.size() > left.size() ) {
            path += right.top();
            right.pop();
            dfs(out, path, left, right, n);
            path.pop_back();
            right.emplace(")");
        }
        if (!left.empty()) { // nonempty stack, if we remove this emptiness check we may run into stack overflow
            path += left.top();
            left.pop();
            dfs(out, path, left, right, n) ;
            path.pop_back();
            left.emplace("(");
        }
    }
};
//
// int main() {
//     GenerateParentheses test;
//     vector<string> res = test.generateParentheses(1);
//     for (string& s : res) {
//         cout << s << " ";
//     }
//     cout << endl;
// }