//
// Created by alyss on 8/12/2025.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_set>
using namespace std;
// 08/12/2025
// Realized sorting can enable a more efficient skip duplicate mechanism。 Specifically, we can sort the array so that
// the duplicates cluster and are easier to skip

/**
 * Given a collection of numbers, nums, that might contain duplicates,
 * return all possible unique permutations in any order.
 */
class PermutationsII {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        if (nums.empty()) return {};

        vector<bool> used(nums.size(), false);
        vector<vector<int>> out;
        vector<int> path;

        // sort the nums array
        sort(nums.begin(), nums.end());

        dfs(0, path, out, nums, used);
        return out;
    }


    /**
 * We want some efficient skipping mechanism: when a number has already been seen, skip it and permute with the rest
 * currIdx refers to the position in the current 'path' permutation
 * It also is the depth of our backtracking tree. Each recursion level is one level in the tree.
 * Each level picks one number to append to the permutation. Depth is how many numbers we have already chosen
 *
 */
private:
    void dfs(int currIdx, vector<int>& path, vector<vector<int>>& out, vector<int>& nums, vector<bool>& used) {

        if (path.size() == nums.size()) { out.push_back(path); return; }

        // at every position of 'path', try every possible index i from nums
        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) continue;
            if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) { continue; }

            used[i] = true;
            path.push_back(nums[i]);

            dfs(currIdx + 1, path, out, nums, used);

            used[i] = false;
            path.pop_back();
        }
    }
public:
    static void printV(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            cout << nums[i] << " ";
        }
        cout << endl;
    }

};
int main() {
    PermutationsII p;
    vector<int> nums = {1, 1, 2};
    vector<vector<int>> out = p.permuteUnique(nums);
    for (vector<int> v : out) {
        PermutationsII::printV(v);
    }
}

