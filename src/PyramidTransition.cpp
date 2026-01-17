#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/**
* LeetCode 756
* You are stacking blocks to form a pyramid. Each block has a color,
* which is represented by a single letter.
* Each row of blocks contains one less block than the row beneath it and is centered on top.
*
* To make the pyramid aesthetically pleasing,
* there are only specific triangular patterns that are allowed.
* A triangular pattern consists of a single block stacked on top of two blocks.
*
* The patterns are given as a list of three-letter strings allowed,
* where the first two characters of a pattern represent the left and right bottom blocks respectively,
* and the third character is the top block.
*
* For example, "ABC" represents a triangular pattern with a 'C' block stacked
* on top of an 'A' (left) and 'B' (right) block.
* Note that this is different from "BAC" where 'B' is on the left bottom and 'A' is on the right bottom.
*/
class PyramidTransition {
public:
// 17/01/2026 Version 2: same as version 1 but use 
//     unordered_map<string, bool> memo: can current layer reach the top?
private: 
    unordered_map<string, bool> memo;

public: 
    bool pyramidTransition(string bottom, vector<string>& allowed) {

        // Preprocess the allowed patterns
        // Notice a set (unordered) does not work as a dictionary: 
        // For sets, it takes extremely long to search in all elements, check the first two letters in the base, then take the third
        // For maps, there can be AAB, AAC sharing the same prefix AA, so storing key value pair of (AA, B) ignores the option (AA, C)
        // But we can store allowed patterns as an array for a common prefix
        // -> unordered_map
        unordered_map<string, string> dict;
        for (string& s : allowed) {
            string k = s.substr(0, 2);
            char top = s[2];
            dict[k].push_back(top);
        }

        vector<string> path; // the solution so far
        path.push_back(bottom); // the first layer of the solution is the given bottom
        // the lowest layer will be the top layer
        return backtrack(path, dict);
    }


    bool backtrack(vector<string>& path, unordered_map<string, string>& dict) {
        string curr = path.back();
        // termination criterion: have built a full valid solution, the top layer is 1
        if (curr.size() == 1) return true;

        // Find whether we can build to the top from current layer
        auto it = memo.find(curr);
        if (it != memo.end()) { // exists, and have checked before, immediately return the answer
            return it->second;
        }
        
         // build the next layer
        string next;
        // reserve the desired length of next layer
        next.reserve(curr.size() - 1); 
        
        bool ans = buildNext(0, curr, next, path, dict);
        memo[curr] = ans;
        return ans;
    }

    /**
    * @param i index of the current element constructed in the next layer
    * @param curr current layer
    * @param next next layer to be constructed
    * @param path all constructed layers so far
    * @param dict dictionary
    */
    bool buildNext(int i, const string& curr, string& next, 
                   vector<string>& path, unordered_map<string, string>& dict) {
        if (i == (int)curr.size() - 1) {
            // backtrack on the layer level
            path.push_back(next);
            // proceed to the next layer, we backtrack on the entire layer being built
            bool canBuild = backtrack(path, dict);
            path.pop_back();
            return canBuild;
        }

        // Check existence of dictionary item before accessing
        auto it = dict.find(curr.substr(i, 2));
        if (it == dict.end()) return false; // does not exist, failed
        // extract all options of a prefix
        const string& options = it->second;
        if (options.empty()) return false; // if empty, failed 
        
        for (char c : options) {
            next.push_back(c);
            // backtrack on the current character
            if (buildNext(i + 1, curr, next, path, dict)) return true;

            next.pop_back();
        }
        return false;
    }  

    
      
// 16/01/2026 Version 1: kills the test cases but exceeds time limit because there is no memoization involved
    // bool pyramidTransition(string bottom, vector<string>& allowed) {

    //     // Preprocess the allowed patterns
    //     // Notice a set (unordered) does not work as a dictionary: 
    //     // For sets, it takes extremely long to search in all elements, check the first two letters in the base, then take the third
    //     // For maps, there can be AAB, AAC sharing the same prefix AA, so storing key value pair of (AA, B) ignores the option (AA, C)
    //     // But we can store allowed patterns as an array for a common prefix
    //     // -> unordered_map
    //     unordered_map<string, string> dict;
    //     for (string& s : allowed) {
    //         string k = s.substr(0, 2);
    //         char top = s[2];
    //         dict[k].push_back(top);
    //     }

    //     vector<string> path; // the solution so far
    //     path.push_back(bottom); // the first layer of the solution is the given bottom
    //     // the lowest layer will be the top layer
    //     return backtrack(path, dict);
    // }

    // bool backtrack(vector<string>& path, unordered_map<string, string>& dict) {
    //     string curr = path.back();
    //     // termination criterion: have built a full valid solution, the top layer is 1
    //     if (curr.size() == 1) return true;

    //     // build the next layer
    //     string next;
    //     // reserve the desired length of next layer
    //     next.reserve(curr.size() - 1); 

    //     // have tried every pattern but still currentLayer size is not 1
    //     if (dict.size() == 0) return false;
        
    //     return buildNext(0, curr, next, path, dict);
    // }

    // /**
    // * @param i index of the current element constructed in the next layer
    // * @param curr current layer
    // * @param next next layer to be constructed
    // */
    // bool buildNext(int i, const string& curr, string& next, 
    //                vector<string>& path, unordered_map<string, string>& dict) {
    //     if (i == (int)curr.size() - 1) {
    //         // backtrack on the layer level
    //         path.push_back(next);
    //         // proceed to the next layer, we backtrack on the entire layer being built
    //         bool canBuild = backtrack(path, dict);
    //         path.pop_back();
    //         return canBuild;
    //     }

    //     // Check existence before accessing dict[curr.substr(i, 2)]
    //     auto it = dict.find(curr.substr(i, 2));
    //     if (it == dict.end()) return false; // does not exist, failed
    //     // extract all options of a prefix
    //     const string& options = it->second;
    //     if (options.empty()) return false; // if empty, failed 
        
    //     for (char c : options) {
    //         next.push_back(c);
    //         // backtrack on the current character
    //         if (buildNext(i + 1, curr, next, path, dict)) return true;

    //         next.pop_back();
    //     }

    //     return false;
    // }    
};