/*
662. Maximum Width of Binary Tree
Medium

Given the root of a binary tree, return the maximum width of the given tree.

The maximum width of a tree is the maximum width among all levels.

The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes are also counted into the length calculation.

It is guaranteed that the answer will in the range of 32-bit signed integer.

 

Example 1:


Input: root = [1,3,2,5,3,null,9]
Output: 4
Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
Example 2:


Input: root = [1,3,null,5,3]
Output: 2
Explanation: The maximum width existing in the third level with the length 2 (5,3).
Example 3:


Input: root = [1,3,2,5]
Output: 2
Explanation: The maximum width existing in the second level with the length 2 (3,2).
 

Constraints:

The number of nodes in the tree is in the range [1, 3000].
-100 <= Node.val <= 100
*/
// someone else's code
class Solution {
public:
    int max(int x,int y){
        return (x>y?x:y);
    }
    int widthOfBinaryTree(TreeNode* root) {
        if(!root) return 0;
        queue<pair<TreeNode*,unsigned long long int>>q;
        q.push({root,0});
        int width=0;
        while(!q.empty()){
            unsigned long long int l=q.front().second;
            unsigned long long int r=0;
            int n=q.size();
            for(auto i=0;i<n;i++){
                pair<TreeNode*,unsigned long long int >ptr=q.front();
                q.pop();
                r=ptr.second;
                if(ptr.first->left){
                    q.push({ptr.first->left,2*r+1});
                }
                if(ptr.first->right){
                    q.push({ptr.first->right,2*r+2});
                }
            }
            width=max(width,(r-l+1));
        }
        return width;
    }
};

// my soln.
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

class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if(!root)
            return 0;
        queue< pair<TreeNode*, long long int> > pending;
        pending.push({root, 1});
        pending.push({NULL, 0});
        
        long long int minId = INT_MAX, maxId = 0;
        long long int ans = 0;
        
        while(!pending.empty()){
            pair<TreeNode*, long long int> frontPair = pending.front();
            pending.pop();
            if(frontPair.first == NULL){
                
                if(!pending.empty())
                    pending.push({NULL, 0});
                
                ans = max(ans, maxId - minId + 1);
                minId = INT_MAX; maxId = 0;
            }
            else{
                minId = min(minId, frontPair.second);
                maxId = max(maxId, frontPair.second);
                
                //everytime the leftmost node at any level will have value 1
                //minId will be assigned once for a level, for rest times it'll be same
                //2*INT_MAX can appear, so using long long int is necessary
                if(frontPair.first->left)
                    pending.push({frontPair.first->left, 2*frontPair.second - minId});
                    
                if(frontPair.first->right)
                    pending.push({frontPair.first->right, 2*frontPair.second + 1  - minId});
            }
        }
        return ans;
    }
};