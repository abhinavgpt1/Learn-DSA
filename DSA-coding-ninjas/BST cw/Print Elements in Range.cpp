/*
Code: Print Elements in Range
Send Feedback
Given a Binary Search Tree and two integers k1 and k2, find and print the elements which are in range k1 and k2 (both inclusive).
Print the elements in increasing order.
Input format :
Line 1 : Elements in level order form (separated by space)
(If any node does not have left or right child, take -1 in its place)
Line 2 : Two Integers k1 and k2
Output Format :
Required elements (separated by space)
Sample Input :
8 5 10 2 6 -1 -1 -1 -1 -1 7 -1 -1
6 10
Sample Output :
6 7 8 10
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
// to print in increasing order
void elementsInRangeK1K2(BinaryTreeNode<int>* root, int k1, int k2) {
    if(root == NULL)
        return;
    if(root->data >= k1 && root->data <= k2){
        elementsInRangeK1K2(root->left,k1,k2);
        cout<<root->data<<" ";
        elementsInRangeK1K2(root->right,k1,k2);
    }
    else if(k2 < root->data)
        elementsInRangeK1K2(root->left,k1,k2);
    else//== k1 > root->data
        elementsInRangeK1K2(root->right,k1,k2);
}
//little lengthy:as above though
void elementsInRangeK1K2(BinaryTreeNode<int>* root, int k1, int k2) {
    if(root == NULL)
        return;
    
    if(root->data > k2)
    {
        elementsInRangeK1K2(root->left, k1, k2);
        if(root->data <=k2 && root->data >= k1)//impractical: just check the parent if/else-if condition
        cout<<root->data<<" ";
    }
    else if(root->data < k1){
        if(root->data <=k2 && root->data >= k1)//impractical: just check the parent if/else-if condition
        cout<<root->data<<" ";
        elementsInRangeK1K2(root->right, k1, k2);
    }
    else{
        elementsInRangeK1K2(root->left, k1, k2);
        if(root->data <=k2 && root->data >= k1)
        cout<<root->data<<" ";
        elementsInRangeK1K2(root->right, k1, k2);
    }
}
//not efficient: branches not pruned
void elementsInRangeK1K2(BinaryTreeNode<int>* root, int k1, int k2) {
    if(root==NULL)
        return;
    
    elementsInRangeK1K2(root->left,k1,k2);
   	if(root->data >= k1 && root->data <= k2)
       	cout<<root->data<<" ";    
	elementsInRangeK1K2(root->right,k1,k2); 

}
