/**********************************************************

	Following is the Binary Tree Node class structure

	template <typename T>
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

***********************************************************/

BinaryTreeNode<int>* constructTree(int *input, int n) {
	// Write your code here
    int mid = (n-1)/2;
    if(input == NULL || n <= 0)
        return NULL;
    BinaryTreeNode<int>* root = new BinaryTreeNode<int>(input[mid]);
    root->left = constructTree(input, mid);
    root->right = constructTree(input + mid + 1, n - mid - 1);
    return root;
}
// convenient
BinaryTreeNode<int>* Helper(int input[],int si, int endi){
    if(si>endi)
        return NULL;
    int mid=(endi+si)/2;
	BinaryTreeNode<int>* root = new BinaryTreeNode<int>(input[mid]);
    root->left=Helper(input,si,mid-1);
    root->right=Helper(input,mid+1,endi);
    return root;
}
BinaryTreeNode<int>* constructTree(int *input, int n) {
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Return output and don't print it.
     * Taking input and printing output is handled automatically.
     */
	return Helper(input,0,n-1);
}
