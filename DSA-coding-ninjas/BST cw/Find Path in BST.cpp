/*
Find Path in BST
Send Feedback
Given a BST and an integer k. Find and return the path from the node with data k and root (if a node with data k is present in given BST). Return null otherwise.
Assume that BST contains all unique elements.
Input Format :
Line 1 : Elements in level order form (separated by space)
(If any node does not have left or right child, take -1 in its place)
Line 2 : Integer k
Output Format :
Path from node k to root
Sample Input :
8 5 10 2 6 -1 -1 -1 -1 -1 7 -1 -1
2
Sample Output :
2
5
8
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

vector<int>* getPath(BinaryTreeNode<int> *root , int data) {
	
    if(root == NULL)
        return NULL;
    if(root->data == data){
        return new vector<int>(1, root->data);
    }
    else if(data < root->data){
        vector<int>*tempAns = getPath(root->left, data);
        if(tempAns != NULL)
        	tempAns->push_back(root->data);
        return tempAns;
    }
    else{
        vector<int>*tempAns = getPath(root->right, data);
        if(tempAns != NULL)
        	tempAns->push_back(root->data);
        return tempAns;
    }
}

//descriptive
#include<vector>
vector<int>* findPath(BinaryTreeNode<int> *root , int data){
    
	if(root == NULL)
        return NULL;
    if(root->data == data){
        vector<int> * vec = new vector<int> ();
        vec->push_back(data);
        return vec;
    }
    if(data >= root->data)
    {
        vector<int> * right = findPath(root->right, data);
        if(right != NULL)
        	right->push_back(root->data);
        return right;
    }
    else{
        vector<int> * left = findPath(root->left, data);
        if(left != NULL)
        	left->push_back(root->data);
        return left;
    }
    
}
//descriptive
vector<int>* findPath(BinaryTreeNode<int> *root , int data){
    
	if(root==NULL){
    	return NULL;    
    }
    
    if(root->data==data){
        vector<int> *ans=new vector<int>();
        ans->push_back(root->data);
        return ans;
    }
    
    if(data < root->data){
        vector<int> *leftans = findPath(root->left,data);
        if(leftans!=NULL)
        {
            leftans->push_back(root->data);
            return leftans;
        }
        else
            return NULL;
    }
    else{
        
        vector<int> *rightans = findPath(root->right,data);
        if(rightans!=NULL)
        {
            rightans->push_back(root->data);
            return rightans;
        }
        else
            return NULL;
    }
}