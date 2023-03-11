/*
111. Minimum Depth of Binary Tree
Easy

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

Note: A leaf is a node with no children.

 

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: 2

Example 2:

Input: root = [2,null,3,null,4,null,5,null,6]
Output: 5

 

Constraints:

    The number of nodes in the tree is in the range [0, 105].
    -1000 <= Node.val <= 1000


*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
//100% - DFS
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }
        if (root->left == NULL) {
            return 1 + minDepth(root->right);
        }
        if (root->right == NULL) {
            return 1 + minDepth(root->left);
        }
        return 1 + min(minDepth(root->left), minDepth(root->right));
    }
};
//100% - BFS
class Solution {
public:
    int minDepth(TreeNode* root) {
        int minimumDepth = 1;
        if(!root) return 0;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            for(int i=0,n=q.size();i<n;i++){
                TreeNode* p = q.front();
                q.pop();
                if(p->left==NULL && p->right==NULL) return minimumDepth;
                if(p->left) q.push(p->left);
                if(p->right) q.push(p->right);
            }
            minimumDepth++;
        }
        return minimumDepth;
    }
};
//my soln.
class Solution {
public:
    int solve(TreeNode* root){
        if(root == NULL)
            return INT_MAX;
        if(root->left == NULL && root->right == NULL)
            return 1;
        return min(solve(root->left), solve(root->right)) + 1;
    }
    int minDepth(TreeNode* root) {
        if(root == NULL)
            return 0;
        return solve(root);
    }
};