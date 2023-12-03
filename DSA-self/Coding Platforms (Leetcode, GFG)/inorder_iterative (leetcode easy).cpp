/*
94. Binary Tree Inorder Traversal
Easy

Given the root of a binary tree, return the inorder traversal of its nodes' values.

 

Example 1:

Input: root = [1,null,2,3]
Output: [1,3,2]

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
vector<int> inorderTraversal(TreeNode *root)
{

    vector<int> res;

    stack<TreeNode *> s;

    while (root || !s.empty())
    {

        if (root)
        {

            s.push(root);
            root = root->left;
        }
        else
        {

            root = s.top();
            s.pop();
            res.push_back(root->val);
            root = root->right;
        }
    }

    return res;
}
//latest soln. - same as 4th
class Solution {
public:
    void fillLeft(stack<TreeNode*> &stk, TreeNode* root){
        if(!root)
            return;
        stk.push(root);
        fillLeft(stk, root->left);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> stk;
        fillLeft(stk, root);
        vector<int> ans;
        while(!stk.empty()){
            TreeNode* top = stk.top();
            stk.pop();
            ans.push_back(top->val);
            if(top->right)
                fillLeft(stk, top->right);
        }
        return ans;
    }
};

//my soln. - old (better)
vector<int> inOrder(Node *root)
{
    //code here
    stack<pair<Node *, bool>> stk;
    vector<int> ans;
    stk.push({root, false});
    while (!stk.empty())
    {
        pair<Node *, bool> temp = stk.top();
        stk.pop();
        Node *top = temp.first;
        bool considered = temp.second;
        if (top->left != NULL && !considered)
        {
            stk.push({top, true});
            stk.push({top->left, false});
        }
        else
        {
            ans.push_back(top->data);
            if (top->right != NULL)
                stk.push({top->right, false});
        }
    }
    return ans;
}

//my soln. - new
class Solution
{
public:
    vector<int> inorderTraversal(TreeNode *root)
    {

        if (root == NULL)
            return {};

        vector<int> ans;
        stack<TreeNode *> pending;

        TreeNode *top = root;
        while (top != NULL)
        {
            pending.push(top);
            top = top->left;
        }

        while (!pending.empty())
        {
            top = pending.top();
            pending.pop();
            ans.push_back(top->val);
            if (top->right != NULL)
            {
                top = top->right;
                while (top != NULL)
                {
                    pending.push(top);
                    top = top->left;
                }
            }
        }
        return ans;
    }
};