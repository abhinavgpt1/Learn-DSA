/*
Print nodes at distance k from node
Send Feedback
You are given a Binary Tree of type integer, a target node, and an integer value K.
Print the data of all nodes that have a distance K from the target node. The order in which they would be printed will not matter.
Example:
For a given input tree(refer to the image below):
1. Target Node: 5
2. K = 2
alt txt

Starting from the target node 5, the nodes at distance K are 7 4 and 1.
Input Format:
The first line of input will contain the node data, all separated by a single space. Since -1 is used as an indication whether the left or right node data exist for root, it will not be a part of the node data.

The second line of input contains two integers separated by a single space, representing the value of the target node and K, respectively.
Output Format:
All the node data at distance K from the target node will be printed on a new line.

The order in which the data is printed doesn't matter.
Constraints:
1 <= N <= 10^5
Where N is the total number of nodes in the binary tree.

Time Limit: 1 sec
Sample Input 1:
5 6 10 2 3 -1 -1 -1 -1 -1 9 -1 -1
3 1
Sample Output 1:
9
6
Sample Input 2:
1 2 3 4 5 6 7 -1 -1 -1 -1 -1 -1 -1 -1
3 3
Sample Output 2:
4
5
*/
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

/*//my method: idea same
#include<climits>
class Tuple{
  public:
    bool found = false;
    int dist = INT_MIN;
};
void printAtDistKDown(BinaryTreeNode<int> *root, int k){
    if(root == NULL || k < 0)
        return;
    if(k == 0)
    {
        cout<<root->data<<endl;
        return;
    }
    printAtDistKDown(root->left, k-1);
    printAtDistKDown(root->right, k-1);
}
Tuple helper(BinaryTreeNode<int> *root, int node, int k){
    Tuple ans;
    if(root == NULL){
        return ans;
    }
    if(root->data == node){
        printAtDistKDown(root, k);
        Tuple ans;
        ans.found = true;
        ans.dist = 1;
        return ans;
        
    }
    Tuple left = helper(root->left, node, k);
    if(left.found == true){
        if(k == left.dist)
            cout<<root->data<<endl;
        else
            printAtDistKDown(root->right, k - left.dist -1);
        left.dist+=1;
        return left;
    }
    Tuple right = helper(root->right, node, k);
    if(right.found == true){
        if(k == right.dist)
            cout<<root->data<<endl;
        else
            printAtDistKDown(root->left, k - right.dist -1);
        right.dist+=1;
        return right;
    }
    return ans;
}
void nodesAtDistanceK(BinaryTreeNode<int> *root, int node, int k) {
    // Write your code herez
    helper(root, node, k);
}
*/

//official method: logic same
void searchDepth(BinaryTreeNode<int> *root, int level, int depth) {
    if(root == NULL || level > depth)
        return;
    if(level == depth)
        cout<<root->data<<endl;
    else{
        searchDepth(root->left, level + 1, depth);
        searchDepth(root->right, level + 1, depth);
    }
}
int helper(BinaryTreeNode<int> *root, int node, int k) {
    if(root == NULL){
        return -1;
    }
    if(root->data == node){
        //call for down nodes
        searchDepth(root, 0, k);
        return 1;
    }
    int leftCue = helper(root->left, node, k);
    int rightCue = helper(root->right, node, k);
    if(leftCue != -1){
        if(leftCue == k){
            cout<<root->data<<endl;
            return -1;//no upward node is possible now
        }
        else{
            searchDepth(root->right, leftCue + 1, k);
            return leftCue + 1;

        }   
    }
    if(rightCue != -1){
        if(rightCue == k){
            cout<<root->data<<endl;
            return -1;//no upward node is possible now
        }
        else{
            searchDepth(root->left, rightCue + 1, k);
            return rightCue + 1;

        }   
    }
    return -1;
}
void nodesAtDistanceK(BinaryTreeNode<int> *root, int node, int k) {
    helper(root, node, k);
}

//inefficient as in, include a lot of k<0 cases in printAtDistKDown
void printAtDistKDown(BinaryTreeNode<int> *root, int k){
    if(root == NULL || k < 0)
        return;
    if(k == 0)
    {
        cout<<root->data<<endl;
        return;
    }
    printAtDistKDown(root->left, k-1);
    printAtDistKDown(root->right, k-1);
}
int helper(BinaryTreeNode<int> *root, int node, int k) {
    if(root == NULL)
        return -1;
    if(root->data == node){
        printAtDistKDown(root, k);
        return 0;
    }
    int left = helper(root->left, node, k);
    if(left != -1){
        if(left + 1 == k)
            cout<<root->data<<endl;
        else{
            printAtDistKDown(root->right, k - left - 2);
        }
        return left + 1;
    }
    int right = helper(root->right, node, k);
    if(right != -1){
        if(right + 1 == k)
            cout<<root->data<<endl;
        else{
            printAtDistKDown(root->left, k - right - 2);
        }
        return right + 1;
    }
    return -1;
}

void nodesAtDistanceK(BinaryTreeNode<int> *root, int node, int k) {
    // Write your code herez
    helper(root, node, k);
}