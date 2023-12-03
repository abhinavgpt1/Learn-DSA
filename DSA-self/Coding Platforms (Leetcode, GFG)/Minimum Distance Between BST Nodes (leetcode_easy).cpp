/*
783. Minimum Distance Between BST Nodes
Easy

1493

304

Add to List

Share
Given the root of a Binary Search Tree (BST), return the minimum difference between the values of any two different nodes in the tree.

 

Example 1:


Input: root = [4,2,6,1,3]
Output: 1
Example 2:


Input: root = [1,0,48,null,null,12,49]
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [2, 100].
0 <= Node.val <= 105
 

Note: This question is the same as 530: https://leetcode.com/problems/minimum-absolute-difference-in-bst/
*/
//100%
class Solution {
public:
    int diff = INT_MAX;
    TreeNode *prev = NULL;
    void dfs(TreeNode *root) {
        // moving to the left as much as we can
        if (root->left) dfs(root->left);
        // if we find at least a node before, we update diff
        if (prev) diff = min(diff, abs(prev->val - root->val));
        prev = root;
        // moving to the right as much as we can
        if (root->right) dfs(root->right);
    }
    int minDiffInBST(TreeNode* root) {
        dfs(root);
        return diff;
    }
};
// my soln - 54, 90%
class Solution {
public:
    int ans = INT_MAX;
    pair<int, int> helper(TreeNode* root){
        if(root == NULL)
            return {INT_MAX,INT_MIN};
        pair<int, int> leftAns = helper(root->left);
        pair<int, int> rightAns = helper(root->right);
        if(leftAns.second != INT_MIN)
            ans = min(ans, root->val - leftAns.second);
        if(rightAns.first != INT_MAX)
            ans = min(ans, rightAns.first - root->val);
        return {min(root->val, leftAns.first), max(root->val, rightAns.second)};
    }
    int minDiffInBST(TreeNode* root) {
        helper(root);
        return ans;
    }
};

// my soln - 24, 24 %
class Solution {
public:
    vector<int> getVector(TreeNode* root){
        if(root == NULL)
            return {};
        vector<int> left = getVector(root->left);
        vector<int> right = getVector(root->right);
        left.push_back(root->val);
        for(auto x: right)
            left.push_back(x);
        return left;
    }
    int minDiffInBST(TreeNode* root) {
        vector<int> arr = getVector(root);
        int ans = INT_MAX;
        for(int i=1; i<arr.size(); i++){
            ans = min(arr[i]-arr[i-1], ans);
        }
        return ans;
    }
};