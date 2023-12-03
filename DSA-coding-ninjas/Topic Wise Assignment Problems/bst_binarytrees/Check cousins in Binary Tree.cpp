/*
Check cousins in Binary Tree
Send Feedback
Given the binary Tree and two nodes say ‘p’ and ‘q’. Determine whether the two nodes are cousins of each other or not. Two nodes are said to be cousins of each other if they are at same level of the Binary Tree and have different parents.
Do it in O(n).
Input format :
Line 1 : Nodes in level order form (separated by space). If any node does not have left or right child, take -1 in its place
Line 2 : integer value of p 
Line 3 : Integer value of q
Output format :
true or false
Constraints :
1 <= N <= 10^5
Sample Input :
5 6 10 2 3 4 -1 -1 -1 -1 9 -1 -1 -1 -1
2
4
Sample Output :
true
*/
// Following is the Binary Tree node structure
/**************
class BinaryTreeNode {
    public : 
    T data;
    BinaryTreeNode<T> *left;
    BinaryTreeNode<T> *right;

    BinaryTreeNode(T data) {
        this -> data = data;
        left = NULL;
        right = NULL;
    }
};
***************/
//more performance
//at leetcode
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
    int getLevel(TreeNode * root, int x, int y){
        if(root == NULL)
            return -1;
        if(root->left != NULL 
           && 
           root->right != NULL
          && (
              (root->left->val == x && root->right->val == y)
              ||
              (root->left->val == y && root->right->val == x)
            ))
           return -1;
        if(root -> val == x)
            return 0;
        int leftAns = getLevel(root->left, x, y);
        if(leftAns != -1)
            return leftAns + 1;
        leftAns = getLevel(root->right, x, y);
        return ((leftAns != -1) ? leftAns + 1 : -1);
    }
    bool isCousins(TreeNode* root, int x, int y) {
        int xAns = getLevel(root, x, y);
        int yAns = getLevel(root, y, x);
        if(xAns == -1 || yAns == -1 || xAns != yAns)
            return false;
        return true;
    }
};

//at coding ninjas
pair<bool, int> findLevel(BinaryTreeNode<int> *root, int p){
    if(root == NULL)
        return {false, 0};
    if(root->data == p)
        return {true, 1};
    pair<bool, int> leftAns = findLevel(root->left, p);
    
    if(leftAns.first)//this way we prune the tree other we could do leftAns, rightAns consecutively
        return {leftAns.first, leftAns.second + 1};
    pair<bool, int> rightAns = findLevel(root->right, p);
    if(rightAns.first)
        return {rightAns.first, rightAns.second + 1};
    return rightAns; 
}
bool checkCommonParent(BinaryTreeNode<int> *root, int p, int q){
    if(root == NULL)
        return false;
    if(root->left!=NULL && root->right!=NULL && ((root->left->data == p && root->right->data == q) || (root->left->data == q && root->right->data == p)))
        return true;
    return checkCommonParent(root->left, p, q) || checkCommonParent(root->right, p, q);
}
bool isCousin(BinaryTreeNode<int> *root, int p, int q) {
    // O(3n) - finding level can be made efficient by finding level for both p, q at once : tuple<bool, int,  bool, int> -> O(2n)

	pair<bool, int> pAns = findLevel(root, p);
    pair<bool, int> qAns = findLevel(root, q);
    if(!pAns.first && !qAns.first || pAns.second != qAns.second)//not found, not same level
        return false;
    return !checkCommonParent(root, p, q);
}


//unneccesary code
int findLevel(BinaryTreeNode<int> *root, int n){
    if(root==NULL)
        return -1;
    if(root->data == n)
        return 0;
    int left = findLevel(root->left,n);
    if(left!=-1)
        return left + 1;
    int right = findLevel(root->right,n);
    if(right!=-1)
        return right + 1;
    else
        return -1;
}
bool isSibling(BinaryTreeNode<int> *root, int p, int q){
    if(root==NULL)
        return false;
    if(root->left!=NULL && root->right!=NULL)
    {
        if((root->left->data==p && root->right->data==q) || (root->left->data==q && root->right->data==p))
            return true;
        else
            return isSibling(root->left,p,q) || isSibling(root->right,p,q);
    }
    if(root->left!=NULL)
        return isSibling(root->left,p,q);
    else
        return isSibling(root->right,p,q);
        
}
bool isCousin(BinaryTreeNode<int> *root, int p, int q) {
    // Write your code here
	int lp = findLevel(root,p);
    int lq = findLevel(root,q);
    if(lp==-1 || lq==-1 || lp != lq)//means they were'nt found
        return false;
    //edge case : they must not be siblings
    return !isSibling(root,p,q);
}
