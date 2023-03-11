/*
Just Next larger than n in tree
Send Feedback
Given a generic tree and an integer n. Find and return the node with next larger element in the Tree i.e. find a node with value just greater than n.
Return NULL if no node is present with the value greater than n.
Input Format :
Line 1 : Integer n
Line 2 : Elements in level order form separated by space (as per done in class). Order is -
Root_data, n (No_Of_Child_Of_Root), n children, and so on for every element
Output Format :
Node with value just greater than n.
Sample Input 1 :
18
10 3 20 30 40 2 40 50 0 0 0 0
Sample Output 1 :
20
Sample Input 2 :
21
10 3 20 30 40 2 40 50 0 0 0 0
Sample Output 2:
30
*/
// Following is the given Tree node structure
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
//easiest solution
#include<climits>
TreeNode<int>* Helper(TreeNode<int>*root,int n, int currnMax){
    TreeNode<int> * ans = NULL;
    if(root->data > n && root->data < currnMax)
    {
        ans = root;
        currnMax = root->data;
    }
    for(int i = 0; i < root->children.size(); i++){
        TreeNode<int> * temp = Helper(root->children[i],n,currnMax);
        if(temp !=NULL && temp->data < currnMax){
            ans = temp;
            currnMax = temp->data;
        }
    }    
    return ans;
}
TreeNode<int>* nextLargerElement(TreeNode<int> *root, int n) {
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Return output and don't print it.
     * Taking input and printing output is handled automatically.
     */
    return Helper(root,n,INT_MAX);

}
//easier

TreeNode<int> * nextLargerElement(TreeNode<int> *root, int n) {

    if(root==NULL)
        return NULL;

    TreeNode<int> * great_node=NULL;

    if(root->data > n)
        great_node=root;


    for(int i=0;i<root->children.size();i++){
        TreeNode<int> *temp = nextLargerElement(root->children[i], n);
        if(great_node == NULL)
            great_node=temp;

        else if(temp!=NULL){
            if(temp->data < great_node->data)
                great_node=temp;
        }
    }

    return great_node;

}
//complicated

#include<utility>
#include<climits>
pair<TreeNode<int> *,int>* nextLargerElement(TreeNode<int> *root, int n, int waste) {

    if(root==NULL)
        {
            pair<TreeNode<int> *,int> *ans = new pair<TreeNode<int> *,int>();
            ans->first=NULL;
            ans->second=0;
            return ans;
        }
    int diff=root->data-n;
    if(diff<=0)
        diff=INT_MAX;

    pair<TreeNode<int> *,int> *great = new pair<TreeNode<int> *,int>();
    great->first=root;
    great->second=diff;

    for(int i=0;i<root->children.size();i++){
        pair<TreeNode<int> *,int> *temp = nextLargerElement(root->children[i], n, waste);
        if(temp->second<great->second)
        {
            great=temp;
        }
        else
            delete temp;
    }
    return great;

}

TreeNode<int>* nextLargerElement(TreeNode<int> *root, int n) {
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Return output and don't print it.
     * Taking input and printing output is handled automatically.
     */
    return nextLargerElement(root, n,0)->first;

}