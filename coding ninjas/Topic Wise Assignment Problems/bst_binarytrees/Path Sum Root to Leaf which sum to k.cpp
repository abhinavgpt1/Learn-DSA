/*
Path Sum Root to Leaf which sum to k
Send Feedback
Given a binary tree and a number k, print out all root to leaf paths where the sum of all nodes value is same as the given number k.
Input format :

Line 1 : Elements in level order form (separated by space)

(If any node does not have left or right child, take -1 in its place)

Line 2 : k

Output format : Print each path in new line, elements separated by space

Sample Input 1 :
5 6 7 2 3 -1 1 -1 -1 -1 9 -1 -1 -1 -1
13
Sample Output 1 :
5 6 2
5 7 1
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

//method efficient: 1
void helper(BinaryTreeNode<int> *root, int k, vector<int> arr) {

    if(root == NULL || k <= 0)
        return; 
    if(root->left == NULL && root->right == NULL && k == root->data){
        for(auto x: arr)
            cout<<x<<" ";
        cout<<root->data<<endl;
    }

    arr.push_back(root->data);
    helper(root->left, k-root->data, arr);
    helper(root->right, k-root->data, arr);
}
void rootToLeafPathsSumToK(BinaryTreeNode<int> *root, int k) {
    vector<int> arr;
    helper(root, k, arr);
}

//longer, inefficient code (k<=0 is not checked)
void print(vector<int> output){
    for(int i=0;i<output.size();i++)
        cout<<output[i]<<" ";
    cout<<endl;
}
void helper(BinaryTreeNode<int> *root, int k, vector<int> output) {
    if(root==NULL)
        return;
    
    output.push_back(root->data);
    if(root->left==NULL && root->right==NULL){
        if(k==root->data)
            print(output);
        return;
    }
    helper(root->left,k-root->data,output);
    helper(root->right,k-root->data,output);
    
}
void rootToLeafPathsSumToK(BinaryTreeNode<int> *root, int k) {
    vector<int> output;
	helper(root, k, output);
}


//method tactical: 2
void print(vector<int> output){
    for(int i=0;i<output.size();i++)
        cout<<output[i]<<" ";
    cout<<endl;
}
void helper(BinaryTreeNode<int> *root, int k, vector<int> output) {
    if(root==NULL){
        if(k==0)
            print(output);
        return;
    }
    output.push_back(root->data);
    if(root->left != NULL && root->right != NULL)
    {
        helper(root->left,k-root->data,output);
    	helper(root->right,k-root->data,output);
    }
    else if(root->left == NULL)
        helper(root->right,k-root->data,output);
    else
        helper(root->left,k-root->data,output);
}
void rootToLeafPathsSumToK(BinaryTreeNode<int> *root, int k) {
    if(root==NULL)
        return;
    vector<int> output;
	helper(root, k, output);
}

//wrong ans: therefore use k == root->data condition and not k == 0
//mini version of above method : answer will print twice here
void helper(BinaryTreeNode<int> *root, int k, vector<int> arr) {
    if(k < 0)
        return;
	if(root == NULL){
        if(k == 0)
        {
            for(auto x: arr)
                cout<<x<<" ";
            cout<<endl;
        }
        return;
    }    
    arr.push_back(root->data);
    helper(root->left, k-root->data, arr);
    helper(root->right, k-root->data, arr);
}


//GENERAL: i.e. not specifically from root

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
void print(vector<int> output){
    for(int i=0;i<output.size();i++)
        cout<<output[i]<<" ";
    cout<<endl;
}
void helper(BinaryTreeNode<int> *root, int k, vector<int> &output) {
    if(root==NULL){
        if(k==0)
            print(output);
        return;
    }
    output.push_back(root->data);
    if(root->left != NULL && root->right != NULL)
    {
        helper(root->left,k-root->data,output);
    	helper(root->right,k-root->data,output);
    }
    else if(root->left == NULL)
        helper(root->right,k-root->data,output);
    else
        helper(root->left,k-root->data,output);
            
    output.pop_back();
    if(root->left != NULL && root->right != NULL)
    {
        helper(root->left,k,output);
    	helper(root->right,k,output);
    }
    else if(root->left == NULL)
        helper(root->right,k,output);
    else
        helper(root->left,k,output);
    
    // helper(root->left,k,output);
    // helper(root->right,k,output);
}
void rootToLeafPathsSumToK(BinaryTreeNode<int> *root, int k) {
    // Write your code here
    vector<int> output;
	helper(root, k, output);
}
