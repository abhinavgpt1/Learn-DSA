/*
Check if a Binary Tree is BST
Send Feedback
Given a binary tree with N number of nodes, check if that input tree is BST (Binary Search Tree) or not. If yes, return true, return false otherwise.
Duplicate elements should be in right subtree.
Input format :
Line 1 : Nodes in level order form (separated by space). If any node does not have left or right child, take -1 in its place
Output format :
true or false
Constraints :
1 <= N <= 10^5
Sample Input 1 :
3 1 5 -1 2 -1 -1 -1 -1
Sample Output 1 :
true
Sample Input 2 :
5 2 10 0 1 -1 15 -1 -1 -1 -1 -1 -1
Sample Output 2 :
false
*/

//1. basic approach
#include <climits>
int maxvalue(BinaryTreeNode<int> *root)
{
    if (root == NULL)
        return INT_MIN;
    return max(root->data, max(maxvalue(root->left), maxvalue(root->right)));
}
int minvalue(BinaryTreeNode<int> *root)
{
    if (root == NULL)
        return INT_MAX;
    return min(root->data, min(minvalue(root->left), minvalue(root->right)));
}
bool isBST(BinaryTreeNode<int> *root)
{
    // Write your code here
    if (root == NULL)
        return true;
    return root->data > maxvalue(root->left) && root->data <= minvalue(root->right) && isBST(root->left) && isBST(root->right);
}

//2. O(n) approach using tuple/user defined class - pair<pair>
#include <tuple>
#include <climits>
//isBST, min, max
tuple<bool, int, int> isBSTHelper(BinaryTreeNode<int> *root)
{
    tuple<bool, int, int> ans;
    if (root == NULL)
    {
        ans = make_tuple(true, INT_MAX, INT_MIN);
        return ans;
    }
    tuple<bool, int, int> leftAns = isBSTHelper(root->left);
    tuple<bool, int, int> rightAns = isBSTHelper(root->right);

    if (!get<0>(leftAns) || !get<0>(rightAns) || get<2>(leftAns) >= root->data || get<1>(rightAns) < root->data)
        ans = make_tuple(false, 0, 0);
    else
        ans = make_tuple(true, min(root->data, get<1>(leftAns)), max(root->data, get<2>(rightAns)));
    //min, max comparison is important, 
    //passing min = get<1>(leftAns) and max = get<2>(rightAns) is completely WRONG: 
    // ques -> as you may think till here BST is fine and min among all values will be min of left subtree. Similarly max will be max of right subtree => WRONG
    // soln -> left subtree may be NULL therefore, min = root value but you passed INT_MAX (get<1>(NULL)). similar problem with right subtree being NULL
    return ans;
}
bool isBST(BinaryTreeNode<int> *root)
{
    return get<0>(isBSTHelper(root));
}

//3. best solution - O(n)
#include <climits>
bool helper(BinaryTreeNode<int> *root, int minima, int maxima)
{
    if (root == NULL)
        return true;
    if (root->data < minima || root->data >= maxima)
        return false;
    return helper(root->left, minima, root->data) && helper(root->right, root->data, maxima);
}

bool isBST(BinaryTreeNode<int> *root)
{
    /* Don't write main().
	* Don't read input, it is passed as function argument.
	* Return output and don't print it.
	* Taking input and printing output is handled automatically.
	*/
    return helper(root, INT_MIN, INT_MAX);
}

//wrong solution
bool isBST(BinaryTreeNode<int> *root)
{
    if (root == NULL)
        return true;
    if (root->left != NULL)
    {
        if (root->data <= root->left->data)
            return false;
    }
    if (root->right != NULL)
    {
        if (root->data > root->right->data)
            return false;
    }

    bool ans = isBST(root->left);
    if (ans == false)
        return false;

    ans = isBST(root->right);
    if (ans == false)
        return false;

    return true;
}

//user defined class - tuple
#include <utility>
#include <climits>
template <typename T>
class Tuple
{
public:
    bool isBST;
    T max;
    T min;
    Tuple()
    {
        isBST = true;
        min = INT_MAX;
        max = INT_MIN;
    }
};
Tuple<int> Helper(BinaryTreeNode<int> *root)
{
    Tuple<int> ans;
    if (root == NULL)
        return ans;
    if (root->left == NULL && root->right == NULL)//unnecessary
    {
        ans.min = ans.max = root->data;
        return ans;
    }
    Tuple<int> left = Helper(root->left);
    Tuple<int> right = Helper(root->right);

    ans.min = min(left.min, root->data);
    ans.max = max(right.max, root->data);
    /*
            ans.min = left.min;
            ans.max = right.max;
            fails at : 1 5 -1 4 -1 -1 -1
    */
    /*
    //unncessary
    ansFinal.min=min(root->data,min(ansL.min,ansR.min));
    ansFinal.max=max(root->data,max(ansL.max,ansR.max));
    */
    ans.isBST = left.isBST && right.isBST && root->data > left.max && root->data < right.min;
    return ans;
}
bool isBST(BinaryTreeNode<int> *root)
{
    /* Don't write main().
    * Don't read input, it is passed as function argument.
    * Return output and don't print it.
    * Taking input and printing output is handled automatically.
    */
    return Helper(root).isBST;
}

/*//above method but more desciptive
#include<climits>
template <typename T>
class myTuple{
    public:
    T min;
    T max;
    bool result;
};

myTuple<int> BSTHelper(BinaryTreeNode<int> *root){

	if(root==NULL){
        myTuple<int> ans;
        ans.min=INT_MAX;
        ans.max=INT_MIN;
        ans.result=true;
        return ans;
    }

    myTuple<int> ansFinal;
    ansFinal.min=INT_MAX;
    ansFinal.max=INT_MIN;
    ansFinal.result=true;


    myTuple<int> ansL=BSTHelper(root->left);
    myTuple<int> ansR=BSTHelper(root->right);
    if((ansL.result && ansR.result)==false)
    {
        ansFinal.result=false;
        return ansFinal;
    }

    if(root->data <= ansL.max)
    {
        ansFinal.result=false;
        return ansFinal;
    }
    if(root->data > ansR.min)
    {
        ansFinal.result=false;
        return ansFinal;
    }

    ansFinal.min=min(root->data,min(ansL.min,ansR.min));
    ansFinal.max=max(root->data,max(ansL.max,ansR.max));
    ansFinal.result=true;

    return ansFinal;

}
bool isBST(BinaryTreeNode<int> *root){
    return BSTHelper(root).result;
}*/
