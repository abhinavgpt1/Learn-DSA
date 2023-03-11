/*
is tree Balanced
Send Feedback
Given a binary tree, check if its balanced i.e. depth of left and right subtrees of every node differ by at max 1. Return true if given binary tree is balanced, false otherwise.
Input format :

Elements in level order form (separated by space). If any node does not have left or right child, take -1 in its place.

Sample Input 1 :
5 6 10 2 3 -1 -1 -1 -1 -1 9 -1 -1
Sample Output 1 :
false
Sample Input 2 :
1 2 3 -1 -1 -1 -1
Sample Output 2 :
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
int height(BinaryTreeNode<int> *root){
    if(root==NULL)
        return 0;
    return (1+max(height(root->left),height(root->right)));
}
bool isBalanced(BinaryTreeNode<int> *root) {
    // Write your code here
	if(root==NULL)
        return true;
    
    int h1=height(root->left);
    int h2=height(root->right);
    if(abs(h1-h2)>1)
        return false;
    
    bool ans=isBalanced(root->left);
    if(ans==false)
        return false;
    ans=isBalanced(root->right);
    if(ans==false)
        return false;
    
    return true;
}
//optimized code
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
#include<utility>
pair<int, bool> helper(BinaryTreeNode<int> *root){
    if(root==NULL){
        pair<int,bool> ans;
        ans.first=0;
        ans.second=true;
        return ans;
    }
    
    pair<int,bool> left = helper(root->left);
    pair<int,bool> right = helper(root->right);
    
    pair<int,bool> ans;
    int lh=left.first;
    int rh=right.first;
    if(abs(lh-rh)>1)
    {
        ans.second=false;
        ans.first=1+max(lh,rh);
    }
    else{
        if(left.second==false || right.second==false)
            ans.second=false;
        else
            ans.second=true;
        ans.first=1+max(lh,rh);
    }
    return ans;
}
bool isBalanced(BinaryTreeNode<int> *root) {
    // Write your code here
    return helper(root).second;
}
