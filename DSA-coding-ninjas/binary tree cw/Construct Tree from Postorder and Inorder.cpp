/*
Construct Tree from Postorder and Inorder
Send Feedback
For a given postorder and inorder traversal of a Binary Tree of type integer stored in an array/list, create the binary tree using the given two arrays/lists. You just need to construct the tree and return the root.
Note:
Assume that the Binary Tree contains only unique elements. 
Input Format:
The first line of input contains an integer N denoting the size of the list/array. It can also be said that N is the total number of nodes the binary tree would have.

The second line of input contains N integers, all separated by a single space. It represents the Postorder-traversal of the binary tree.

The third line of input contains N integers, all separated by a single space. It represents the inorder-traversal of the binary tree.
Output Format:
The given input tree will be printed in a level order fashion where each level will be printed on a new line. 
Elements on every level will be printed in a linear fashion. A single space will separate them.
Constraints:
1 <= N <= 10^4
Where N is the total number of nodes in the binary tree.

Time Limit: 1 sec
Sample Input 1:
7
4 5 2 6 7 3 1 
4 2 5 1 6 3 7 
Sample Output 1:
1 
2 3 
4 5 6 7 
Sample Input 2:
6
2 9 3 6 10 5 
2 6 3 9 5 10 
Sample Output 2:
5 
6 10 
2 3 
9 
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
/************** Not doing this way : 
    (int *post, int *in, int postS,int postE,int inS,int inE) but as
    (int *post, int *in, int postS,int postLength,int inS,int inLength)
 WILL cause problem
 

...........................NOT ANYMORE, see solution below.......................


because keeping track of each index is cumbersome -> a single problem will make ans. wrong
eg. reducing array size of inorderarray for generating left, right subtrees isn't possible, hence you require whole array, with suitable indices
reduction in pre,postarrays will be fine since root occurs in extreme...but not in case of inorder
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

//tougher approach : you have to just think more accuractely

BinaryTreeNode<int>* buildTree(int *postorder, int postLength, int *inorder, int inLength) {
    // Write your code here
    if(postLength != inLength || postLength <= 0 || postorder == NULL || inorder == NULL)
        return NULL;
    int root, postLS, postLE, postRS, postRE, postRoot, inLS, inLE, inRS, inRE, inRoot;
    postRoot = postLength - 1;
    root = postorder[postRoot];
    for(int i=0; i<inLength; i++){
        if(inorder[i] == root){
            inRoot = i;
            break;
        }
    }
    inLS = 0;
    inLE = inRoot - 1;
    inRS = inRoot + 1;
    inRE = inLength - 1;
    postLS = 0;
    postRE = postRoot - 1;
    
    int leftLength = inLE - inLS + 1;
    int rightLength = inRE - inRS + 1;
    
    postLE = postLS + leftLength - 1;
    postRS = postRE - rightLength + 1;
    
    BinaryTreeNode<int>* leftTree = buildTree(postorder, leftLength, inorder, leftLength);
    BinaryTreeNode<int>* rightTree = buildTree(postorder + postRS, rightLength, inorder + inRS, rightLength);
    
    BinaryTreeNode<int>* rootNode = new BinaryTreeNode<int>(root);
    rootNode->left = leftTree;
    rootNode->right = rightTree;
    return rootNode;
}