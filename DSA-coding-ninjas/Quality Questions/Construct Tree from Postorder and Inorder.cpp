/*
Construct Tree from Postorder and Inorder
Send Feedback
Given Postorder and Inorder traversal of a binary tree, create the binary tree associated with the traversals.You just need to construct the tree and return the root.
Note: Assume binary tree contains only unique elements.
Input format :

Line 1 : n (Total number of nodes in binary tree)

Line 2 : Post order traversal

Line 3 : Inorder Traversal

Output Format :

Elements are printed level wise, each level in new line (separated by space).

Sample Input :
8
8 4 5 2 6 7 3 1
4 8 2 5 1 6 3 7
Sample Output :
1 
2 3 
4 5 6 7 
8
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
BinaryTreeNode<int>* BinaryTreeHelper(int *post, int *in, int postS,int postE,int inS,int inE){
    if(inS>inE)
        return NULL;
    int rootData = post[postE];
    int rootIndexPost=postE;
    int rootIndexIn=-1;
    for (int i = inS; i <= inE; i++) {
		if (in[i] == rootData) {
			rootIndexIn = i;
			break;
		}
	}
    BinaryTreeNode<int>*  root = new BinaryTreeNode<int>(rootData);
    int lInS = inS;
    int lInE = rootIndexIn-1;
	int lPostS = postS;
	int lPostE = lInE - lInS + lPostS;
    
	int rPostS = lPostE + 1;
	int rPostE = rootIndexPost-1;
	int rInS = rootIndexIn + 1;
	int rInE = inE;
    
    root->left=BinaryTreeHelper(post,in,lPostS,lPostE,lInS,lInE);
    root->right=BinaryTreeHelper(post,in,rPostS,rPostE,rInS,rInE);
    return root;
}

BinaryTreeNode<int>* getTreeFromPostorderAndInorder(int *postorder, int postLength, int *inorder, int inLength) {
    // Write your code here
	return BinaryTreeHelper(postorder,inorder,0,postLength-1,0,inLength-1);
}
