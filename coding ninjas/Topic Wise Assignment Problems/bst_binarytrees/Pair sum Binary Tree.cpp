/*
Pair sum BInary Tree
Send Feedback
Given a binary tree and an integer S, print all the pair of nodes whose sum equals S.
Assume binary tree contains all unique elements.
Note : In a pair, print the smaller element first. Order of different pair doesn't matter.
Input format :
Line 1 : Elements in level order form (separated by space)
(If any node does not have left or right child, take -1 in its place)
Line 2 : Integer S
Output Format :
Each pair in different line (pair elements separated by space)
Constraints :
1 <= N <= 1000
Sample Input 1:
5 10 6 2 3 -1 -1 -1 -1 -1 9 -1 -1
15
Sample Output 1:
5 10
6 9
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
//fastest and easy
#include<algorithm>
#include<vector>
void makeVec(BinaryTreeNode<int> *root, vector<int> & output){
    if(root == NULL)
        return;
    output.push_back(root->data);
    makeVec(root->left, output);
    makeVec(root->right, output);
}
void nodesSumToS(BinaryTreeNode<int> *root, int sum) {
    // Write your code here
    vector<int> vec;
    makeVec(root,vec);
    sort(vec.begin(), vec.end());
    int i = 0 ,j = vec.size() - 1;
    while(i<j){
        if(vec[i] + vec[j] == sum)
        {
            cout<<vec[i]<<" "<<vec[j]<<endl;
            i++;
            j--;
        }
        else if(vec[i] + vec[j] > sum)
            j--;
        else
            i++;
    }
}
//generic way(brute force): avoid
#include<climits>
bool find(int x, BinaryTreeNode<int> * root){
    if(root==NULL)
        return false;
    if(root->data==x)
    {
        root->data=INT_MIN;
        return true;
    }
    
        bool ans = find(x,root->left) || find(x,root->right);
    
        return ans;
}
void nodesSumToS(BinaryTreeNode<int> *node, BinaryTreeNode<int> *root, int sum) {
    // Write your code here
    if(node==NULL)
        return;
    if(node->data!=INT_MIN){
    	bool ans = find(sum-node->data, root);
    	if(ans){
    	    int a=node->data;
    	    int b=sum-node->data;
    	    int min=a<b?a:b;
    	    int max=a>b?a:b;
    		cout<<min<<" "<<max<<endl;
    	}    
    }
	
    nodesSumToS(node->left,root,sum);
    nodesSumToS(node->right,root,sum);
    
}
void nodesSumToS(BinaryTreeNode<int> *root, int sum) {
    // Write your code here
    
	nodesSumToS(root,root,sum);
}


//method 2
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
#include<algorithm>
vector<int> makeVec(BinaryTreeNode<int> *root){
    vector<int> ans;
    if(root==NULL)
        return ans;
    vector<int> left = makeVec(root->left);
    vector<int> right = makeVec(root->right);
    for(int i=0;i<left.size();i++)
        ans.push_back(left[i]);
    ans.push_back(root->data);
    for(int i=0;i<right.size();i++)
        ans.push_back(right[i]);
    return ans;
}
void nodesSumToS(BinaryTreeNode<int> *root, int sum) {
    // Write your code here
    vector<int> arr = makeVec(root);
    
    sort(arr.begin(),arr.end());
    int i=0,j = arr.size()-1;
    while(i<j){
        
        if(sum==arr[i]+arr[j]){
            cout<<arr[i]<<" "<<arr[j]<<endl;
            i++;j--;
        }
        else if(sum>arr[i]+arr[j]){
            i++;
        }
        else{
            j--;
        }       
        
    }
    
}
