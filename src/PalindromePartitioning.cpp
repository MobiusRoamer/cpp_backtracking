#include <vector>
#include <string>
#include <iostream>
#include <deque>
using namespace std;

// Version 1: 15/12/2025
// LeetCode 131. Palindrome Partitioning
// Given a string s, partition s such that every substring of the partition is a palindrome.
// Return all possible palindrome partitioning of s.
//
/*********************************************************************************************************************/
// NOTES:
// (1) The key is we want partitions not substrings. So a valid partition is in which all substrings are palindromes
// (2) Template for checking palindrome (two pointer approach, see helper isPalindrome())
//

class PalindromePartition {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> out;
        vector<string> pal;
        if (s.length() == 0) { return {}; }
        dfs(out, pal, 0, s);
        return out;
    }

private:
    /**
     * A difficulty here is we need to check whether the substring starting from the previous partition (cut) to the
     * current index is a palindrome, so we need to keep track of the previous cut index and the current index
     *
     * It turns out we do not need to explicitly feed prevCut index as an argument into the function.
     * Think in terms of dynamic-programming:
     * We want to know whether starting from index i in string s, we can form a palindrome by cutting at every next index
     * in between i + 1 and the end of the string s.
     * If we found a partition where i ... j forms a palindrome, automatically update the new dfs recursion startIndex
     * to j.
    */
    void dfs(vector<vector<string>>& out, vector<string>& pal, int startIndex, string s) {
        // The base case is where we have iterated to the end of the string
        if (startIndex == s.length()) {
            out.push_back(pal);
            return;
        }

        for (int endIndex = startIndex; endIndex < s.length(); endIndex++) {
            // check palindrome of the substring between current index and the previous cut
            if (!(isPalindrome(startIndex, endIndex, s))) continue;

            // build a tentative solution: cut the string at startIndex and endIndex
            pal.push_back(s.substr(startIndex, endIndex - startIndex + 1));
            dfs(out, pal, endIndex + 1, s);
            pal.pop_back();
        }
    }

    bool isPalindrome(int start, int end, string s) {

        int i = start, j = end;
        while (i < j) {
            if (s[i] != s[j]) return false;
            i++; j--;
        }
        return true;
    }

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
