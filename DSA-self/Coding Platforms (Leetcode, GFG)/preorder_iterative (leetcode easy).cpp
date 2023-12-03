/*
144. Binary Tree Preorder Traversal
Easy

Given the root of a binary tree, return the preorder traversal of its nodes' values.

 

Example 1:

Input: root = [1,null,2,3]
Output: [1,2,3]

Example 2:

Input: root = []
Output: []

Example 3:

Input: root = [1]
Output: [1]

 

Constraints:

    The number of nodes in the tree is in the range [0, 100].
    -100 <= Node.val <= 100

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
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> stk;
        vector<int> result;
        
        if(root == NULL) return result;
        
        TreeNode* curr = NULL;
        stk.push(root);
        
        while(!stk.empty()){
            curr = stk.top();
            stk.pop();
            
            result.push_back(curr->val);
            
            
            if(curr->right) stk.push(curr->right);
            if(curr->left) stk.push(curr->left);
        }
        
        return result;
    }
};

//my soln.
class Solution {
public:
    
    vector<int> preorderTraversal(TreeNode* root) {
        if(root == NULL)
            return {};
        vector<int> ans;    
        stack<TreeNode*> pending;
        pending.push(root);
        while(!pending.empty()){
            TreeNode* top = pending.top();
            pending.pop();
            
            while(top != NULL){
                ans.push_back(top->val);
                
                if(top->right != NULL)
                    pending.push(top->right);
            
                top = top->left;
            }
        }
        return ans;
    }
};

//using stack - 100% (method 1) - concise
vector<int> preOrder(Node* root)
    {
        //code here
        stack<Node*> stk;
        vector<int> ans;
        stk.push(root);
        while(!stk.empty()){
            Node * top = stk.top();
            stk.pop();
            if(top->right != NULL)
            stk.push(top->right);
            if(top->left != NULL)
            stk.push(top->left);
            ans.push_back(top->data);
        }
        return ans;
    }