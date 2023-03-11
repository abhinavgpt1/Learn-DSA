/*
Code: Construct Tree from Preorder and Inorder
Send Feedback
Given Preorder and Inorder traversal of a binary tree, create the binary tree associated with the traversals.You just need to construct the tree and return the root.
Note: Assume binary tree contains only unique elements.
Input format :

Line 1 : n (Total number of nodes in binary tree)

Line 2 : Pre order traversal

Line 3 : Inorder Traversal

Output Format :

Elements are printed level wise, each level in new line (separated by space).

Sample Input :
12
1 2 3 4 15 5 6 7 8 10 9 12
4 15 3 2 5 1 6 10 8 7 9 12
Sample Output :
1 
2 6 
3 5 7 
4 8 9 
15 10 12
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
BinaryTreeNode<int>* buildTreeHelper(int* in, int* pre, int inS, int inE, int preS, int preE) {
    if (inS > inE) {
        return NULL;
    }

    int rootData = pre[preS];
    int rootIndex = -1;
    for (int i = inS; i <= inE; i++) {
        if (in[i] == rootData) {
            rootIndex = i;
            break;
        }
    }

    int lInS = inS;
    int lInE = rootIndex - 1;
    int lPreS = preS + 1;
    int lPreE = lInE - lInS + lPreS;
    int rPreS = lPreE + 1;
    int rPreE = preE;
    int rInS = rootIndex + 1;
    int rInE = inE;
    BinaryTreeNode<int>*  root = new BinaryTreeNode<int>(rootData);
    root->left = buildTreeHelper(in, pre, lInS, lInE, lPreS, lPreE);
    root->right = buildTreeHelper(in, pre, rInS, rInE, rPreS, rPreE);
    return root;
}

BinaryTreeNode<int>* buildTree(int *preorder, int preLenght, int *inorder, int inLength) {
    // Write your code here
    return buildTreeHelper(inorder, preorder, 0, inLength - 1, 0, inLength - 1);
}

//tougher approach : you have to just think more accuractely
BinaryTreeNode<int>* buildTree(int *preorder, int preLength, int *inorder, int inLength) {
    // Write your code here
    if(preLength != inLength || preLength <=0 || preorder == NULL || inorder == NULL)
        return NULL;
    int root, preLS, preLE, preRS, preRE, preRoot, inRoot, inLS, inLE, inRS, inRE;
    preRoot = 0;
    root = preorder[preRoot];
    preLS = preRoot + 1;
    preRE = preLength - 1;
    for(int i=0; i<inLength; i++){
        if(inorder[i] == root){
            inRoot = i;
            break;
        }
    }
    inLE = inRoot-1;
    inRS = inRoot+1;
    inLS = 0;
    inRE = inLength - 1;
    int leftLength = inLE - inLS + 1;
    int rightLength = inRE - inRS + 1;
    preLE = preLS + leftLength - 1;
    preRS = preRE - rightLength + 1;
    
    BinaryTreeNode<int>* leftTree = buildTree(preorder + preLS, leftLength, inorder, leftLength);
    BinaryTreeNode<int>* rightTree = buildTree(preorder + preRS, rightLength, inorder + inRS, rightLength);
    
    BinaryTreeNode<int>* rootNode = new BinaryTreeNode<int>(root);
    rootNode->left = leftTree;
    rootNode->right = rightTree;
    return rootNode;
};