/*
Replace with Sum of greater nodes in BST
Send Feedback
Given a binary search tree, replace each nodes' data with the sum of all nodes' which are greater or equal than it. You need to include the current node's data also.
That is, if in given BST there is a node with data 5, you need to replace it with sum of its data (i.e. 5) and all nodes whose data is greater than or equal to 5.
You don't need to return or print, just change the data of each node.
Input format :

Line 1 : Elements in level order form (separated by space)

(If any node does not have left or right child, take -1 in its place)

Output format : Elements are printed in level order wise, every level in new line

Sample Input 1 :
8 5 10 2 6 -1 -1 -1 -1 -1 7 -1 -1
Sample Output 1 :
18 
36 10 
38 31 
25 
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
int helper(BinaryTreeNode<int> *root, int extraAddition){
    if(root == NULL)
        return 0;
    int rightAns = helper(root->right, extraAddition);
    int leftAns = helper(root->left, extraAddition + rightAns + root->data);
    int ans = root->data + leftAns + rightAns;
    root->data += rightAns + extraAddition;
    return ans;
    
}
void replaceWithLargerNodesSum(BinaryTreeNode<int> *root) {
    // Write your code here
    helper(root, 0);
}

//older code
int helper(BinaryTreeNode<int> *root, int addOn) {
    if(root == NULL)
        return 0;
    
    int rightData = helper(root->right, addOn);
    int leftData = helper(root->left, root->data + rightData + addOn);
    
    int r = root->data + leftData + rightData;
    root->data += rightData + addOn;
    return r;
}

void replaceWithLargerNodesSum(BinaryTreeNode<int> *root) {
    // Write your code here
	helper(root, 0);
}

//same as above: sum and replace done in O(n) in comparison to below method's code
int Helper(BinaryTreeNode<int> *root, int addOn) {
    if(root==NULL)
        return 0;
    //saving root value
    int rootData = root->data;
    
    int rightSum = Helper(root->right, addOn);
    root->data += rightSum + addOn;
    int leftSum = Helper(root->left, root->data);

    //returns "sum of tree"
    return rootData + leftSum + rightSum;
}
void replaceWithLargerNodesSum(BinaryTreeNode<int> *root) {
    // Write your code here
    Helper(root,0);//gives sum of entire tree
}

//T(n) != O(n)
int sum(BinaryTreeNode<int> *root){
    if(root==NULL)
        return 0;
    return sum(root->left) + sum(root->right) + root->data;
}
void Helper(BinaryTreeNode<int> *root, int addOn) {
    if(root==NULL)
        return;
    int right = sum(root->right);
    root->data +=right + addOn;
    Helper(root->right, addOn);
    Helper(root->left, root->data);
}
void replaceWithLargerNodesSum(BinaryTreeNode<int> *root) {
    // Write your code here
    Helper(root,0);
}
