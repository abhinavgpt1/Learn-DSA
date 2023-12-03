/*
701. Insert into a Binary Search Tree
Medium
You are given the root node of a binary search tree (BST) and a value to insert into the tree. Return the root node of the BST after the insertion. It is guaranteed that the new value does not exist in the original BST.

Notice that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return any of them.

 

Example 1:


Input: root = [4,2,7,1,3], val = 5
Output: [4,2,7,1,3,5]
Explanation: Another accepted tree is:

Example 2:

Input: root = [40,20,60,10,30,50,70], val = 25
Output: [40,20,60,10,30,50,70,null,null,25]
Example 3:

Input: root = [4,2,7,1,3,null,null,null,null,null,null], val = 5
Output: [4,2,7,1,3,5]
 

Constraints:

The number of nodes in the tree will be in the range [0, 104].
-108 <= Node.val <= 108
All the values Node.val are unique.
-108 <= val <= 108
It's guaranteed that val does not exist in the original BST.
*/

//iterative
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        // support variables
        TreeNode *current = root, *newNode = new TreeNode(val);
        // edge case - empty tree
        if (!root) return newNode;
        // iterative search
        while (true) {
            if (current->val > val) {
                if (current->left) {
                    current = current->left;
                    continue;
                }
                current->left = newNode;
                break;
            } else {
                if (current->right) {
                    current = current->right;
                    continue;
                }
                current->right = newNode;
                break;
            }
        }
        return root;
    }
};

//recursion
class Solution {
    public:
        TreeNode* dfs(TreeNode *root, int val) {
            if (!root) return new TreeNode(val);
            if (root->val > val) {
                root->left = dfs(root->left, val);
                return root;
            }
            if (root->val < val) {
                root->right = dfs(root->right, val);
                return root;
            };
            return NULL;
        }
        TreeNode* insertIntoBST(TreeNode *root, int val) {
            return dfs(root, val);
        }
    };
    A bit more hacky with the comma operator:
    
    class Solution {
    public:
        TreeNode* dfs(TreeNode *root, int val) {
            if (!root) return new TreeNode(val);
            if (root->val > val) return (root->left = dfs(root->left, val), root);
            if (root->val < val) return (root->right = dfs(root->right, val), root);
            return NULL;
        }
        TreeNode* insertIntoBST(TreeNode *root, int val) {
            return dfs(root, val);
        }
    };