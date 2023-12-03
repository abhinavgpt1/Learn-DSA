/*
102. Binary Tree Level Order Traversal
Medium

7230

145

Add to List

Share
Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).



Example 1:


Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]
Example 2:

Input: root = [1]
Output: [[1]]
Example 3:

Input: root = []
Output: []


Constraints:

The number of nodes in the tree is in the range [0, 2000].
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
//good approach - 15, 20% though
vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> ans;
    if (root == nullptr)
    {
        return ans;
    }

    queue<pair<TreeNode *, int>> q;
    q.push({root, 0});
    map<int, vector<int>> mp;

    while (!q.empty())
    {
        auto it = q.front();
        q.pop();
        int level = it.second;
        TreeNode *node = it.first;
        mp[level].push_back(node->val);

        if (node->left)
        {
            q.push({node->left, level + 1});
        }
        if (node->right)
        {
            q.push({node->right, level + 1});
        }
    }

    for (auto p : mp)
    {
        vector<int> col;
        for (auto w : p.second)
        {
            col.push_back(w);
        }
        ans.push_back(col);
    }

    return ans;
}

// my soln. - 5, 62 %
class Solution
{
public:
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        if (root == NULL)
            return {};
        vector<vector<int>> ans;
        queue<TreeNode *> pending;
        pending.push(root);
        pending.push(NULL);
        vector<int> temp;
        while (!pending.empty())
        {
            TreeNode *front = pending.front();
            pending.pop();
            if (front == NULL)
            {
                ans.push_back(temp);
                temp.clear();
                if (!pending.empty())
                    pending.push(NULL);
            }
            else
            {
                temp.push_back(front->val);
                if (front->left != NULL)
                    pending.push(front->left);
                if (front->right != NULL)
                    pending.push(front->right);
            }
        }
        return ans;
    }
};