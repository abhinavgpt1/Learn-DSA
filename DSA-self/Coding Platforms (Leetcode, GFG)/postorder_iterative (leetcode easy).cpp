/*
145. Binary Tree Postorder Traversal
Easy

3750

135

Add to List

Share
Given the root of a binary tree, return the postorder traversal of its nodes' values.



Example 1:


Input: root = [1,null,2,3]
Output: [3,2,1]
Example 2:

Input: root = []
Output: []
Example 3:

Input: root = [1]
Output: [1]


Constraints:

The number of the nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100


Follow up: Recursive solution is trivial, could you do it iteratively?

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
// 100% - postorder is just preorder with left and right swapped - left right root == reverse(root right left)
class Solution
{
public:
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> an;
        if (root == NULL)
            return an;
        stack<TreeNode *> st;
        st.push(root);
        while (!st.empty())
        {
            TreeNode *cur = st.top();
            st.pop();

            if (cur == NULL)
            {
                break;
            }
            an.push_back(cur->val);
            if (cur->left)
            {
                st.push(cur->left);
            }
            if (cur->right)
            {
                st.push(cur->right);
            }
        }
        reverse(an.begin(), an.end());
        return an;
    }
};
// my solution - 44, 96%
class Solution
{
public:
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> ans;
        if (!root)
            return ans;
        stack<pair<TreeNode *, bool>> stk;
        stk.push({root, false});
        while (!stk.empty())
        {
            pair<TreeNode *, bool> topNode = stk.top();
            stk.pop();
            if (topNode.second == false)
            {
                topNode.second = true;
                stk.push(topNode);
                if (topNode.first->right)
                    stk.push({topNode.first->right, false});
                if (topNode.first->left)
                    stk.push({topNode.first->left, false});
            }
            else
            {
                ans.push_back(topNode.first->val);
            }
        }
        return ans;
    }
};

// as above but has mistakes and improvement - 1. no check of if root == NULL, 2. isStkChanged is not necessary-> just checking considered = true is sufficient
vector<int> postOrder(Node *node)
{
    // code here
    stack<pair<Node *, bool>> stk;
    vector<int> ans;
    stk.push({node, false});
    while (!stk.empty())
    {
        pair<Node *, bool> temp = stk.top();
        stk.pop();
        Node *top = temp.first;
        bool considered = temp.second;
        int isStkChanged = stk.size();

        if (considered == false)
            stk.push({top, true});

        if (top->right != NULL && !considered)
            stk.push({top->right, false});
        if (top->left != NULL && !considered)
            stk.push({top->left, false});

        if (stk.size() == isStkChanged)
        {
            ans.push_back(top->data);
        }
    }
    return ans;
}
// recursion soln. is 100 % on runtime
// devastating soln. - tree is no more connected - but memory efficient soln.
class Solution {
public:
     vector<int> result;
    vector<int> postorderTraversal(TreeNode* root) {
        if(root == NULL)
            return result;
        stack<TreeNode*> s;
        s.push(root);
        while(!s.empty())
        {
            TreeNode* curr = s.top();
            if(curr->left)
            {
                s.push(curr->left);
                curr->left = NULL;
            }
            else if(curr->right)
            {
                s.push(curr->right);
                curr->right = NULL;
            }
            else
            {
                result.push_back(s.top()->val);
                s.pop();
            }
        }
        return result;
        
    }
};