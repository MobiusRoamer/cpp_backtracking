// 27/11/2025.
#include <vector>
#include <iostream>
using namespace std;

class Permutations{

public:
    vector<vector<int>> permute(vector<int>& nums) {

        vector<vector<int>> out;
        if (nums.size() == 0) return out;

        vector<bool> used(nums.size());
        // Note if we attempt
        // array<bool, k> used = {false};
        // we get an error because b is not compile time constant. Note here int b is not declared constant.
        // so if we were to use array, need to use const int b in the function signature

        // delegate to the backtracking dfs function
        vector<int> path;
        dfs(out, path, used, nums);
        return out;

    }

private:
    // NOTE on ERROR:
    // consider the incorrect signature:
    // void dfs(vector<vector<int>> out, vector<int> path, vector<bool> used, vector<int> nums) {
    // This means passing parameters BY VALUE
    // so inside dfs(), when we want to out.push_back(path); we will be adding to a LOCAL COPY of out
    // but when dfs returns to the parent call, the original out in permute() is still empty
    // then permite returns an empty vector<vector<int>> and nothing prints
    void dfs(vector<vector<int>>& out, vector<int>& path, vector<bool>& used, vector<int>& nums) {

        if (path.size() == path.size()) { out.push_back(path); return; } // found a new path

        for (int i = 0; i < used.size(); i++) {
            if (used[i]) continue;

            // backtracking template: choose -- explore -- unchoose
            // choose
            path.push_back(nums[i]);
            used[i] = true;
            // explore
            dfs(out, path, used, nums);
            // unchoose
            path.pop_back();
            used[i] = false;
        }
    }

};

static void printVector(vector<int>& v) {
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
}

//int main() {
//    vector<int> test = {1, 3, 5, 7};
//    Permutations p;
//    vector<vector<int>> output = p.permute(test);
//    for (int i = 0; i < output.size(); ++i) {
//        printVector(output[i]);
//    }
//}
