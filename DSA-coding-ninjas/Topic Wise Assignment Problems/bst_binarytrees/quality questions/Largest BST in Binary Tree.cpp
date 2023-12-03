/*
Largest BST in Binary Tree
Send Feedback
Given a Binary tree, find the largest BST subtree. That is, you need to find the BST with maximum height in the given binary tree.
Return the height of largest BST.
Input format :

Line 1 : Elements in level order form (separated by space)

(If any node does not have left or right child, take -1 in its place)

Sample Input 1:
5 10 6 2 3 -1 -1 -1 -1 -1 9 -1 -1
Sample Output 1:
2
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

// method 1
#include<climits>
//min, max, isBST, height
class myTuple{
  public:
    int min = INT_MAX, max = INT_MIN, hgt = 0;
    bool isBST = false;
};
myTuple helper(BinaryTreeNode<int> *root){
    myTuple ans;
    if(root == NULL){
        ans.isBST = true;
        return ans;
    }
    myTuple leftans = helper(root->left);
    myTuple rightans = helper(root->right);
    if(leftans.isBST && rightans.isBST && root->data > leftans.max && root->data <= rightans.min){
        ans.isBST = true;
        ans.hgt = max(leftans.hgt, rightans.hgt) + 1;
        ans.min = min(root->data, leftans.min);
        ans.max = max(root->data, rightans.max);
    }
    else{
        ans.hgt = max(leftans.hgt, rightans.hgt);
        ans.min = min(root->data, min(leftans.min, rightans.min));
        ans.max = max(root->data, max(leftans.max, rightans.max));
        ans.isBST = false;
    }
    return ans;
}
int largestBSTSubtree(BinaryTreeNode<int> *root) {
    // Write your code here
    return helper(root).hgt;
}

//method 2: not good complexity
#include<climits>
bool isBST(BinaryTreeNode<int> *root, int maxima, int minima) {
    
    if(root==NULL)
        return true;
    if(root->data > maxima || root->data < minima)
        return false;
    return isBST(root->left,root->data, minima) && isBST(root->right,maxima,root->data);    
}
int height(BinaryTreeNode<int> *root) {
    if(root==NULL)
        return 0;
    return 1 + max(height(root->left), height(root->right));
}
int largestBSTSubtree(BinaryTreeNode<int> *root) {
    // Write your code here
    bool ans = isBST(root,INT_MAX,INT_MIN);
    if(ans)
        return height(root);
    return max(largestBSTSubtree(root->left),largestBSTSubtree(root->right));    
}

// Wrong method: see ninjas solution: takes a class-> min, max, isBST, height of max BST
// in that min, max are not updated in case root is not part of isBST

// WRONG method : not even proper from isBST 's question point of view
class Tuple{
  public:
    bool isBST;
    int height;
    Tuple(){
        isBST = true;
        height = 0;
    }
};
Tuple helper(BinaryTreeNode<int> *root){
   
    if(root == NULL){
       Tuple ans;
       return ans;
    }
    if(root->left == NULL && root->right == NULL)
    {
        Tuple ans;
        ans.height = 1;
        return ans;
    }
    Tuple left = helper(root->left);
    Tuple right = helper(root->right);
    
    if(root->left != NULL && root->right != NULL){
        Tuple ans;
        ans.isBST = left.isBST && right.isBST && root->data > root->left->data && root->data <= root->right->data;
        if(ans.isBST){
            ans.height = max(left.height, right.height)+1;
        }
        else
            ans.height = max(left.height, right.height);
        return ans;
    }
    else if(root->left != NULL){        
        if(root->left->data < root->data){
            left.height +=1;
            return left;
        }
        else{
            left.isBST = false;
            return left;            
        }
    }
    else{
        if(root->right->data >= root->data){
            right.height +=1;
            return right;
        }
        else{
            right.isBST = false;
            return right;            
        }
    }
}
int largestBSTSubtree(BinaryTreeNode<int> *root) {
    // Write your code here
    return helper(root).height;
}