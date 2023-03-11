/*
Code: BST to Sorted LL
Send Feedback
Given a BST, convert it into a sorted linked list. Return the head of LL.
Input format :
Elements in level order form (separated by space)
(If any node does not have left or right child, take -1 in its place)
Output Format :
Linked list elements (separated by space)
Sample Input :
8 5 10 2 6 -1 -1 -1 -1 -1 7 -1 -1
Sample Output :
2 5 6 7 8 10
*/
// Following is the Binary Tree node structure
/**************
 
 template <typename T>
 class Node{
    public:
    T data;
    Node<T> *next;
    
    Node(T data){
        this -> data = data;
        this -> next = NULL;
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
/**********************************************************

	Following are the Binary Tree Node class structure and the 
	Node class structure

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

	template <typename T>
 	class Node{
    	public:
    	T data;
    	Node<T> *next;
    
    	Node(T data) {
        	this->data = data;
        	this->next = NULL;
    	}
 	};

***********************************************************/
//method 1
pair<Node<int>*, Node<int>*> helper(BinaryTreeNode<int>* root){
    if(root == NULL)
        return {NULL, NULL};
    pair<Node<int>*, Node<int>*> leftAns = helper(root->left);
    pair<Node<int>*, Node<int>*> rightAns = helper(root->right);
    pair<Node<int>*, Node<int>*> ans;
    Node<int>* rootLLNode = new Node<int>(root->data);
    
    //head
    if(leftAns.first != NULL)
        ans.first = leftAns.first;
    else
        ans.first = rootLLNode;
    //middle linking
    if(leftAns.second != NULL)
        leftAns.second->next = rootLLNode;
    rootLLNode->next = rightAns.first;
    
    //tail
    if(rightAns.first != NULL)
        ans.second = rightAns.second;
    else
        ans.second = rootLLNode;
    return ans;
}
Node<int>* constructLinkedList(BinaryTreeNode<int>* root) {
	
    return helper(root).first;
}

//method 2
#include<utility>
pair<Node<int>* , Node<int>*> helper(BinaryTreeNode<int>* root){
    pair<Node<int>* , Node<int>*> ans;
    if(root == NULL)
    {
        ans.first = ans.second = NULL;
        return ans;
    }
    if(root->left == NULL && root->right == NULL){
        Node<int> * temp = new Node<int>(root->data);
        ans.first = ans.second = temp;
        return ans;
    }
    pair<Node<int>* , Node<int>*> left = helper(root->left);
    pair<Node<int>* , Node<int>*> right = helper(root->right);
    Node<int> * temp = new Node<int>(root->data);
    
    if(left.first != NULL)
    {
    	ans.first = left.first;
        left.second->next = temp;
    }
    else{
        ans.first = temp;
    }
    temp->next = right.first;
    ans.second = right.second;
    return ans;
}
Node<int>* constructBST(BinaryTreeNode<int>* root) {
    return helper(root).first;
}

//older but same as method 1
//remember ans will be on stack but memory it contains is always on heap
//and while returning only addresses of its pointers are transferred
#include<utility>
pair<Node<int>*,Node<int>*> Helper(BinaryTreeNode<int>* root){
    
    pair<Node<int>*,Node<int>*> ans;
    ans.first = NULL;
    ans.second = NULL;
    if(root==NULL){
        return ans;
    }
    
    pair<Node<int>*,Node<int>*> leftans = Helper(root->left);
    pair<Node<int>*,Node<int>*> rightans = Helper(root->right);
    
    Node<int>* rootNode = new Node<int>(root->data);
    
    //solving for head of linked list
    Node<int> * head;
    if(leftans.first==NULL)
        head=rootNode;
    else
    {
        head=leftans.first;
        leftans.second->next=rootNode;
    }
    ans.first=head;    
    
    //solving for tail of linked list
    rootNode->next=rightans.first;
    if(rightans.second==NULL)
        ans.second=rootNode;
    else
        ans.second=rightans.second;

    return ans;    
    
}
Node<int>* constructBST(BinaryTreeNode<int>* root) {
    return Helper(root).first;
}