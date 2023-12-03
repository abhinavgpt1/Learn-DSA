/*
Min and Max of Binary Tree
Send Feedback
Given a binary tree, find and return the min and max data value of given binary tree.
Return the output as an object of PairAns class, which is already created.
Input format :
Elements in level order form (separated by space)
(If any node does not have left or right child, take -1 in its place)
Output Format :
Max and min (separated by space)
Sample Input :
8 3 10 1 6 -1 14 -1 -1 4 7 13 -1 -1 -1 -1 -1 -1 -1
Sample Output :
14 1
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
 
 // PairAns class -
 class PairAns {
    public :
        int min;
        int max;
 };
 
***************/
#include<climits>
PairAns minMax(BinaryTreeNode<int> *root) {
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Return output and don't print it.
     * Taking input and printing output is handled automatically.
     */
	if(root==NULL){
        PairAns ans;
        //to be noticed
        ans.min=INT_MAX;
        ans.max=INT_MIN;
        return ans;
    }
    
    PairAns left=minMax(root->left);
    PairAns right=minMax(root->right);
    PairAns ans;
    ans.min=min(root->data,min(left.min,right.min));
    ans.max=max(root->data,max(left.max,right.max));
    return ans;
    
    
}

//second solution
#include<climits>
void helper(BinaryTreeNode<int> *root, int &min_glob, int &max_glob){
    if(root == NULL)
        return;
    if(root->data > max_glob)
        max_glob = root->data;
    if(root->data < min_glob)
        min_glob = root->data;
    helper(root->left, min_glob, max_glob);
    helper(root->right, min_glob, max_glob);
    
}
pair<int, int> getMinAndMax(BinaryTreeNode<int> *root) {
	// Write your code here
    int min_glob = INT_MAX, max_glob = INT_MIN;
    helper(root, min_glob, max_glob);
    return {min_glob, max_glob};
}