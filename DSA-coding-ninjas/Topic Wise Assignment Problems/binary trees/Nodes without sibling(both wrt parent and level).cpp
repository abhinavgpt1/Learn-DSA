/*
Nodes without sibling
Send Feedback
Given a binary tree, print all nodes that don’t have a sibling.
Edit : Print the elements in different lines. And order of elements doesn't matter.
Input format :
Elements in level order form (separated by space). If any node does not have left or right child, take -1 in its place.
Output format :
Print nodes separated by new line.
Sample Input :
5 6 10 2 3 -1 -1 -1 -1 -1 9 -1 -1
Sample Output :
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

void nodesWithoutSibling(BinaryTreeNode<int> *root) {
    // Write your code here
	if(root==NULL)
        return;
    if(root->left==NULL && root->right!=NULL)
        cout<<root->right->data<<endl;
    if(root->left!=NULL && root->right==NULL)
        cout<<root->left->data<<endl;
    nodesWithoutSibling(root->left);
    nodesWithoutSibling(root->right);
}
//advanced version
//check if nodes have sibling on their level..if not print 'em
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

void nodesWithoutSibling(BinaryTreeNode<int> *root) {
    // Write your code here
    if(root==NULL)
        return;
    queue<BinaryTreeNode<int> *> pending;
    queue<int> ans;
    pending.push(root);
    pending.push(NULL);
    bool isRoot=true;//since we don't want root to be printed
    while(pending.size()!=0){
        
        BinaryTreeNode<int> * front=pending.front();
        pending.pop();
        
        if(front==NULL){
            
            if(isRoot){
                ans.pop();
            }
            isRoot=false;
            if(ans.size()==1)
                cout<<ans.front()<<endl;
            
            while(!ans.empty()){
                    ans.pop();
            }
            
            if(pending.size()!=0)
                pending.push(NULL);
            
            
        }
        else{
            
            ans.push(front->data);
            if(front->left!=NULL)
                pending.push(front->left);
            if(front->right!=NULL)
                pending.push(front->right);
        }
        
    }
}
