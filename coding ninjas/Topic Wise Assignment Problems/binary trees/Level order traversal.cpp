/*
Level order traversal
Send Feedback
Given a binary tree, print the level order traversal. Make sure each level start in new line.
Input format :

Elements in level order form (separated by space). If any node does not have left or right child, take -1 in its place.

Output Format :

Elements are printed level wise, each level in new line (separated by space).

Sample Input :
5 6 10 2 3 -1 -1 -1 -1 -1 9 -1 -1
Sample Output :
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
#include<queue>
void printLevelATNewLine(BinaryTreeNode<int> *root) {
    // Write your code here
    if(root==NULL)
        return;
	queue<BinaryTreeNode<int> *> q1;
    queue<BinaryTreeNode<int> *> q2;
    q1.push(root);
    
    while(q1.size()!=0 || q2.size()!=0){
        if(q2.size()==0){
            while(q1.size()!=0){
				BinaryTreeNode<int> * front=q1.front();
                q1.pop();
                cout<<front->data<<" ";
                if(front->left!=NULL)
                    q2.push(front->left);
                if(front->right!=NULL)
                    q2.push(front->right);
            }
            cout<<endl;
        }
        else if(q1.size()==0){
            while(q2.size()!=0){
				BinaryTreeNode<int> * front=q2.front();
                q2.pop();
                cout<<front->data<<" ";
                if(front->left!=NULL)
                    q1.push(front->left);
                if(front->right!=NULL)
                    q1.push(front->right);
            }
            cout<<endl;
        }
    }
}

//method 2: coding ninjas
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
//1 2 3 4 5 6 7 -1 -1 -1 -1 -1 -1 -1 -1
//1 null 2 3 null 4 5 6 7 null -1 -1 -1 -1 -1 -1 -1 -1
#include<queue>
void printLevelATNewLine(BinaryTreeNode<int> *root) {
    // Write your code here
    if(root==NULL)
        return;
    queue<BinaryTreeNode<int> *> pending;
    pending.push(root);
    pending.push(NULL);
    while(pending.size()!=0){
        
        BinaryTreeNode<int> * front=pending.front();
        pending.pop();
        if(front!=NULL)
        {
            cout<<front->data<<" ";
            if(front->left!=NULL)
                pending.push(front->left);
            if(front->right!=NULL)
                pending.push(front->right);
        }
        else{
            cout<<endl;
            if(pending.size()!=0)
                pending.push(NULL);
        }
    }
}
