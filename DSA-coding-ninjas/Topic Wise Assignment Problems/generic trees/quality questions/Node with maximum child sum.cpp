/*
Node with maximum child sum
Send Feedback
Given a tree, find and return the node for which sum of data of all children and the node itself is maximum. In the sum, data of node itself and data of immediate children is to be taken.
Input format :
Line 1 : Elements in level order form separated by space (as per done in class). Order is - 
Root_data, n (No_Of_Child_Of_Root), n children, and so on for every element 
Output format :
Node with maximum sum.
Sample Input 1 :
5 3 1 2 3 1 15 2 4 5 1 6 0 0 0 0
Sample Output 1 :
1
*/
//method 1: classes/ pair in utility
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
#include<utility>
#include<climits>
pair<TreeNode<int>*, int> helper(TreeNode<int> *root){
	if(root == NULL){
        return {NULL, 0};
    }
    int sum = root->data;
    for(int i=0; i < root->children.size(); i++){
        sum+=root->children[i]->data;
    }
    pair<TreeNode<int>*, int> ans;
    ans.first = root;
    ans.second = sum;
    for(int i=0; i < root->children.size(); i++){
        pair<TreeNode<int>*, int> smallAns = helper(root->children[i]);
        if(smallAns.second > ans.second){
            ans = smallAns;
        }
    }
    return ans;
}
TreeNode<int>* maxSumNode(TreeNode<int>* root) {
    // Write your code here
    return helper(root).first;
}