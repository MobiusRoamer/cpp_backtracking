

// Version 29/11/2025 (Correct: compared to the previous incorrect version, the key is to only use one functional call dfs
// in the parent call combine() (line 22)
#include <vector>
#include <iostream>
using namespace std;

class Combinations{

public:
    vector<vector<int>> combine(int b, int k) {

        vector<vector<int>> out;
        if (b == 0 || k == 0) return out;

        // we could use an explicit array of elements from 1 to b, but we could also use an index tracker
        vector<int> path;

        dfs(out, path, 0, b, k);

        return out;

    }

private:
    void dfs(vector<vector<int>>& out, vector<int>& path, int currIndex, int b, int k) {

        if (path.size() == k) { out.push_back(path); return; } // found a new path

        for (int i = currIndex; i < b ; i++) {

            // backtracking template: choose -- explore -- unchoose
            // choose
            path.push_back(i);

            // explore
            dfs(out, path, i + 1, b, k);

            // unchoose
            path.pop_back();
        }
    }
};

static void printVector(const vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}







// Version 28/11/2025
// I am very close, why am I printing a repetition of the very last combination in lexicographic order?

#include <vector>
#include <iostream>
using namespace std;

class Combinations{

public:
    vector<vector<int>> combine(int b, int k) {

        vector<vector<int>> out;
        if (b == 0 || k == 0) return out;

        // we could use an explicit array of elements from 1 to b, but we could also use an index tracker
        vector<int> path;
        vector<bool> used(b, false);
        for (int i = 0; i < b; i ++) {
            dfs(out, path, i, b, k);
        }

        // dfs(out, path, 0, b, k); Don't do this! this means we always return to the parent function call starting all over againt at 0
        return out;

    }

private:
    void dfs(vector<vector<int>>& out, vector<int>& path, int currIndex, int b, int k) {

        if (path.size() == k) { out.push_back(path); return; } // found a new path

        for (int i = currIndex; i < b ; i++) {

            // backtracking template: choose -- explore -- unchoose
            // choose
            path.push_back(i);

            // explore
            dfs(out, path, i + 1, b, k);
            // unchoose
            path.pop_back();
        }
    }
};

static void printVector(vector<int> v) {
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
}




