/*
687. Longest Univalue Path
Medium

2917

603

Add to List

Share
Given the root of a binary tree, return the length of the longest path, where each node in the path has the same value. This path may or may not pass through the root.

The length of the path between two nodes is represented by the number of edges between them.



Example 1:


Input: root = [5,4,5,1,1,5]
Output: 2
Example 2:


Input: root = [1,4,5,4,4,5]
Output: 2


Constraints:

The number of nodes in the tree is in the range [0, 104].
-1000 <= Node.val <= 1000
The depth of the tree will not exceed 1000.*/
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
// using pair of height and node value
struct Pair
{
    int data;
    int hgt;
    Pair(int _data, int _hgt)
    {
        data = _data;
        hgt = _hgt;
    }
};
class Solution
{
public:
    int ans = 1;
    Pair *helper(TreeNode *root)
    {
        if (root == NULL)
        {
            Pair *node = new Pair(INT_MAX, 0);
            return node;
        }
        Pair *left = helper(root->left);
        Pair *right = helper(root->right);
        Pair *node = new Pair(root->val, 1);
        if (left->data == root->val && right->data == root->val)
        {
            ans = max(ans, left->hgt + right->hgt + 1);

            node->hgt = max(1, max(left->hgt, right->hgt) + 1);
            return node;
        }
        else if (left->data == root->val)
        {
            node->hgt += left->hgt;
            ans = max(ans, max(node->hgt, right->hgt));
            return node;
        }
        else if (right->data == root->val)
        {
            node->hgt += right->hgt;
            ans = max(ans, max(node->hgt, left->hgt));
            return node;
        }
        else
        {

            return node;
        }
        return NULL;
    }
    int longestUnivaluePath(TreeNode *root)
    {
        if (root == NULL)
        {
            return 0;
        }

        helper(root);
        return ans - 1;
    }
};
// my soln. - inefficient though - think it as finding diameter (i.e. calling over nodes repetively just to find height/findSimilar nodes)
class Solution {
public:
    int findSimilar(TreeNode *root, int val){
        if(root == NULL || root->val != val)
            return 0;
        
        int leftcnt = findSimilar(root->left, val);
        int rightcnt = findSimilar(root->right, val);
        
        return max(leftcnt, rightcnt) + 1;
    }
    int longestUnivaluePath(TreeNode* root) {
        if(!root)
            return 0;
        return max({findSimilar(root->left, root->val) + findSimilar(root->right, root->val), longestUnivaluePath(root->left), longestUnivaluePath(root->right)});
    }
};