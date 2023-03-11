/*
LCA of BST
Send Feedback
Given a binary search tree and two nodes, find LCA(Lowest Common Ancestor) of the given two nodes in the BST. Read about LCA if you are having doubts about the definition.
If out of 2 nodes only one node is present, return that node.
If both are not present, return -1.
Input format :
Line 1 :  Elements in level order form (separated by space)
(If any node does not have left or right child, take -1 in its place)
Line 2 : Two integers, Node 1 and Node 2 (separated by space)
Output Format :
LCA
Constraints :
1 <= N <= 1000
Sample Input 1:
8 5 10 2 6 -1 -1 -1 -1 -1 7 -1 -1
2 10
Sample Output 1:
8
Sample Input 2:
8 5 10 2 6 -1 -1 -1 -1 -1 7 -1 -1
2 6
Sample Output 2:
5
Sample Input 3:
8 5 10 2 6 -1 -1 -1 -1 -1 7 -1 -1
12 78
Sample Output 3:
-1
*/
/**********************************************************

	Following is the Binary Tree Node class structure

	template <typename T>
	class BinaryTreeNode {
    	public: 
    	T data;
    	BinaryTreeNode<T> *left;
    	BinaryTreeNode<T> *right;

    	BinaryTreeNode(T data) {
        	this->data = data;
        	left = NULL;
        	right = NULL;
    	}
	};

***********************************************************/

int getLCA(BinaryTreeNode<int>* root , int val1 , int val2){
    // Write your code here
    if(root == NULL)
        return -1;
    if(root->data == val1 || root->data == val2)
        return root->data;

    if(val1 < root->data && val2 < root->data)
        return getLCA(root->left, val1, val2);
    else if(val1 > root->data && val2 > root->data)
        return getLCA(root->right, val1, val2);
    else{
        int leftAns = getLCA(root->left, val1, val2);
        int rightAns = getLCA(root->right, val1, val2);
        
        if(leftAns == -1 || rightAns == -1)
            return leftAns + rightAns + 1;
        else
            return root->data;
    }
}

//little expanded
int lcaInBST(BinaryTreeNode<int>* root , int val1 , int val2){
    // Write your code here
	if(root==NULL)
        return -1;
    if(root->data==val1 || root->data==val2)
        return root->data;

    
    if(root->data < val1 && root->data < val2)
        return lcaInBST(root->right, val1, val2);
    
    else if(root->data > val1 && root->data > val2)
        return lcaInBST(root->left, val1, val2);
    
    else {
        /*
        if((val1 < root->data && val2 > root->data) || (val2 < root->data && val1 > root->data))
        return root->data;

                this isn't sufficient, since elements might not exist
        //submission test cases at coding ninjas are cheap: doesn't include any tc as stated above
        */
        //similar as previous question (LCA in binary tree)
        int left = lcaInBST(root->left, val1, val2);
		int right = lcaInBST(root->right, val1, val2);
        if(left==-1 && right==-1)
            return -1;
        if(left==-1 || right==-1)
            return left+right+1;
        else
            return root->data;
    }
}

