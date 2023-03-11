Height is defined as the total number of nodes along the longest path from the root to any of the leaf node.
So, its safe to assume this
                        10      h=3
                      /      \
                    20      30  h=2
                   /    \
                 40    50       h=1
although, technically(and in textbooks)
                        10      h=0/1
                      /      \
                    20      30  h=1/2
                   /    \
                 40    50       h=2/3
BUT THEN LEVEL AND HEIGHT WIL SOUND SAME
/*
Code : Height of Binary Tree
Send Feedback
Given a binary tree, find and return the height of given tree.
Input format :
Nodes in the level order form (separated by space). If any node does not have left or right child, take -1 in its place
Output format :
Height
Constraints :
1 <= N <= 10^5
Sample Input :
10
 9 
4 
-1 
-1 
 5 
 8 
-1 
6 
-1 
-1 
3 
-1 
-1
-1
Sample Output :
5
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

int height(BinaryTreeNode<int> *root) {
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Return output and don't print it.
     * Taking input and printing output is handled automatically.
     */
	if(root==NULL)
        return 0;
    int h1=height(root->left);
    int h2=height(root->right);
    return max(h1,h2)+1;
}
