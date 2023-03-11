/*
Level wise linkedlist
Send Feedback
Given a binary tree, write code to create a separate linked list for each level. You need to return the array which contains head of each level linked list.
Input format :

Elements in level order form (separated by space). If any node does not have left or right child, take -1 in its place.

Output format : Each level linked list is printed in new line (elements separated by space).

Sample Input :
5 6 10 2 3 -1 -1 -1 -1 -1 9 -1 -1
Sample Output :
5 
6 10 
2 3 
9
*/
// Following is the Node and Binary Tree node structure

/**************
class node{
public:
    T data;
    node<T> * next;
    node(T data){
        this->data=data;
        this->next=NULL;
    }
};

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

vector<node<int>*> createLLForEachLevel(BinaryTreeNode<int> *root) {
    // Write your code here
	if(root==NULL){
        vector<node<int>*> ans;
        ans.push_back(NULL);
        return ans;
    }
    
    queue<BinaryTreeNode<int> *> pending;
    pending.push(root);
    pending.push(NULL);
    
    node<int> *head=NULL;
    node<int> *tail=NULL;
    vector<node<int>*> ans;
    
    while(pending.size()!=0){
        
        BinaryTreeNode<int> * front= pending.front();
        pending.pop();
        
        if(front==NULL){
            
            ans.push_back(head);
            head=NULL;
            tail=NULL;
            if(pending.size()!=0)
                pending.push(NULL);
            
        }
        else{
            
            node<int>* temp = new node<int>(front->data);
            if(head==NULL){
                head=tail=temp;
            }
            else{
				tail->next=temp;
                tail=tail->next;//important
            }
            if(front->left!=NULL)
                pending.push(front->left);
            if(front->right!=NULL)
                pending.push(front->right);
            
            
        }
        
        
    }
    
    return ans;
    
    
}
