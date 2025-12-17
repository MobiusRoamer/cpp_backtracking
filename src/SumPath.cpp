#include <vector>
using namespace std;

// 02/12/2025
// Originally I let dfs(...) return void, so its purpose is mutating the out variable
// But this turns out to exercise poor control flow -> I managed to explore the paths but my traversal does not
// correctly reocgnise a path and keeps exploring further
// To fix this problem I added the boolean control flow

class SumPath {
private:
    class TreeNode {
        int val;
        // why not vector<TreeNode> *children; ?
        // Because TreeNode owns the field children. Only use a pointer if referring to some item external to the class
        // Notice this means a class can be constructed using items outside its scope!
        vector<TreeNode> children;

        TreeNode(int x) : val(x) {}

        // TreeNode(int x, vector<TreeNode> *c) : val(x), children(c) {} // use this version if we wish to sown and store a pointer
        // then children is allowed to be nullptr
        // Alternatively
        TreeNode(int x, vector<TreeNode>& c) : val(x), children(c) {}
        // This means our TreeNode class does not own this list of children it just points to them
        // (fits our case, the children vector is an external argument, the caller never deletes or move the vector)
    public:
        int getVal() const { return val; }
        vector<TreeNode> getChildren() const { return children; }
    };

public:
    vector<TreeNode> findPath(TreeNode& root, int target) {
        vector<TreeNode> out;
        if (root.getVal() == target) { out.push_back(root); return out; }

        if (dfs(out, root, target)) return out;
        return {};
    }

    /**
     * We need to return bool, which signals, upon returning to parent function call in findPath,
     * that we should terminate the program and return out
     * @param out
     * @param root
     * @param target
     * @return
     */
private:
    bool dfs(vector<TreeNode>& out, TreeNode& root, int target) {
        if (target - root.getVal() == 0) { return true; }

        target -= root.getVal();

        out.push_back(root);
        for (TreeNode& c : root.getChildren()) {
            if (dfs(out, c, target)) return true;
        }
        out.pop_back();
        return false;
    }
};
