/*
counting no. of nodes
==
Code : Max data node
Send Feedback
Given a generic tree, find and return the node with maximum data. You need to return the complete node which is having maximum data.
Return null if tree is empty.
Input format :
Elements in level order form separated by space (as per done in class). Order is - 
Root_data, n (No_Of_Child_Of_Root), n children, and so on for every element 
Output Format :
Node with largest data
Sample Input :
10 3 20 30 40 2 40 50 0 0 0 0 
Sample Output :
50
*/
//method 1: easiest method : recursion
// Following is the given Tree node structure.
/**************
 template <typename T>
 class TreeNode {
    public:
        T data;
        vector<TreeNode<T>*> children;
 
        TreeNode(T data) {
            this->data = data;
        }
 
        ~TreeNode() {
            for (int i = 0; i < children.size(); i++) {
                delete children[i];
            }
        }
 };
***************/

TreeNode<int>* maxDataNode(TreeNode<int>* root) {
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Return output and don't print it.
     * Taking input and printing output is handled automatically.
     */
    if(root==NULL)
        return NULL;
	TreeNode<int> *max=root;
    int max_data=root->data;
    for(int i=0;i<root->children.size();i++){
        TreeNode<int>*temp=maxDataNode(root->children[i]);
        if(temp->data>max_data){
            max=temp;
            max_data=temp->data;
        }
    }
    return max;
}

//method 2:level wise traversal

// Following is the given Tree node structure.
/**************
 template <typename T>
 class TreeNode {
    public:
        T data;
        vector<TreeNode<T>*> children;
 
        TreeNode(T data) {
            this->data = data;
        }
 
        ~TreeNode() {
            for (int i = 0; i < children.size(); i++) {
                delete children[i];
            }
        }
 };
***************/

TreeNode<int>* maxDataNode(TreeNode<int>* root) {
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Return output and don't print it.
     * Taking input and printing output is handled automatically.
     */
    if(root==NULL)
        return NULL;
    int max_data=root->data;
    TreeNode<int> *max_node=root;
    queue<TreeNode<int>*> pending;
    pending.push(root);
    
    
    while(pending.size()!=0)
    {
        TreeNode<int>*front=pending.front();
        pending.pop();
        
        for(int i=0;i<front->children.size();i++){
            int temp=front->children[i]->data;
            if(temp>max_data){
                max_data=temp;
                max_node=front->children[i];
            }
            pending.push(front->children[i]);
        }
    }
    return max_node;
}

