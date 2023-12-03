/*
98. Validate Binary Search Tree
Medium
Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
 

Example 1:


Input: root = [2,1,3]
Output: true
Example 2:


Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-231 <= Node.val <= 231 - 1
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

//100%
class Solution
{
public:
    bool isValidBST(TreeNode *root)
    {
        return inOrder(root, nullptr, nullptr);
    }

private:
    bool inOrder(TreeNode *root, TreeNode *min, TreeNode *max)
    {
        if (!root)
            return true;
        if (min != nullptr && root->val <= min->val)
            return false;
        if (max != nullptr && root->val >= max->val)
            return false;

        return inOrder(root->left, min, root) && inOrder(root->right, root, max);
    }
}
//my soln.
class Solution
{
public:
    bool solve(TreeNode *root, int min, int max, bool &isNInf, bool &isInf)
    {
        if (root == NULL)
            return true;
        if (root->val < min || root->val > max)
            return false;

        int data = root->val;
        if ((data == INT_MIN && isNInf) || (data == INT_MAX && isInf))
            return false;
        if (data == INT_MIN)
            isNInf = true;
        if (data == INT_MAX)
            isInf = true;
        return solve(root->left, min, (data == INT_MIN ? INT_MIN : data - 1), isNInf, isInf) && solve(root->right, (data == INT_MAX ? INT_MAX : data + 1), max, isNInf, isInf);
    }
    bool isValidBST(TreeNode *root)
    {
        bool isNInf = false, isInf = false;
        return solve(root, INT_MIN, INT_MAX, isNInf, isInf);
    }
};
//my sol. - with UDDT
class Solution;
class Tuple{
    // int min, max;
    TreeNode * min, *max;
    bool isBST;
    friend Solution;
    public:
      Tuple(TreeNode * min, TreeNode * max, bool isBST):min(min), max(max), isBST(isBST){}
};
class Solution {
public:
    Tuple helper(TreeNode* root){
        if(root == NULL)
            return Tuple(NULL, NULL, true);
        
        Tuple leftAns = helper(root->left);
        Tuple rightAns = helper(root->right);
        
        if(!leftAns.isBST || !rightAns.isBST || (leftAns.max != NULL && (leftAns.max->val >= root->val)) || (rightAns.min != NULL && (rightAns.min->val <= root->val)))
            return Tuple(NULL, NULL, false);
        
        return Tuple((leftAns.min == NULL ? root : leftAns.min), (rightAns.max == NULL? root : rightAns.max), true);
    }
    bool isValidBST(TreeNode* root) {
        return helper(root).isBST;
    }
};