/*
Pair sum in a BST
Send Feedback
Given a binary search tree and an integer S, find pair of nodes in the BST which sum to S. You can use extra space of the order of O(log n).
Note:
1. Assume BST contains all unique elements.
2. In a pair, print the smaller element first.
Input Format :
The first line of input contains data of the nodes of the tree in level order form. The data of the nodes of the tree is separated by space. If any node does not have left or right child, take -1 in its place. Since -1 is used as an indication whether the left or right nodes exist, therefore, it will not be a part of the data of any node.   
The following line of input contains an integer, that denotes the value of S.
Output format:
You have to print each pair in a different line (pair elements separated by space). The order of different pairs, to be printed, does not matter.
Constraints:
Time Limit: 1 second   
Sample Input 1:
8 5 10 2 6 -1 -1 -1 -1 -1 7 -1 -1
12
Sample Output 1:
2 10
5 7
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
#include<stack>
void fillInc(BinaryTreeNode<int> *root, stack<BinaryTreeNode<int>*> &inc){
    if(root == NULL)
        return;
    inc.push(root);
    fillInc(root->left, inc);
}
void fillRevInc(BinaryTreeNode<int> *root, stack<BinaryTreeNode<int>*> &revinc){
    if(root == NULL)
        return;
    revinc.push(root);
    fillRevInc(root->right, revinc);
}
void printNodesSumToS(BinaryTreeNode<int> *root, int s) {

    stack<BinaryTreeNode <int> *> inc, revinc;
    fillInc(root, inc);
    fillRevInc(root, revinc);
    while(!inc.empty() && !revinc.empty()){
        BinaryTreeNode<int> * ith = inc.top();
        BinaryTreeNode<int> * jth = revinc.top();
	
    //if not mentioned fails at -> prints output twice -> the pointers jump cross each other in fillInc, fillRevInc at root
	//10 9 11 8 -1 -1 12 7 -1 -1 13 -1 -1 -1 -1   
	//21
        if(ith == jth || ith->data >= jth->data) //ith==jth is unnecessary to write now
            break;
        if(ith->data + jth->data == s){
            cout<<ith->data<<" "<<jth->data<<endl;
            inc.pop();
        	revinc.pop();
            fillInc(ith->right, inc);
            fillRevInc(jth->left, revinc);
        }
        else if(ith->data + jth->data > s){
            revinc.pop();
            fillRevInc(jth->left, revinc);
        }
        else{
            inc.pop();
            fillInc(ith->right, inc);
        }
    }
}

// wrong solution

// Missing things in this sol.:
// inside while || functions same as && because never will the situation of either stack empty would arise...because before that happens "start" will be equal to "end" -> break;
// keeping a check of pointers being equal and not crossing eath other is imp
#include<stack>
#include<vector>
void fillIn(BinaryTreeNode<int> *root, stack<BinaryTreeNode<int> *> &in){
    if(root == NULL)
        return;
    in.push(root);
    fillIn(root->left, in);
}
void fillRIn(BinaryTreeNode<int> *root, stack<BinaryTreeNode<int> *> &rin){
    if(root == NULL)
        return;
    rin.push(root);
    fillRIn(root->right, rin);
}
void helper(int s, stack<BinaryTreeNode<int> *> &in, stack<BinaryTreeNode<int> *> &rin) {
    while(!in.empty() || !rin.empty()){
        
        // if(in.empty() || rin.empty())//here is the problem
        //     break;
    	BinaryTreeNode<int> * start = in.top();
    	BinaryTreeNode<int> * end = rin.top();
        
        if(start == end)
            break;
        
    	if(start->data + end->data == s){
        	cout<<start->data<<" ";
        	cout<<end->data<<endl;
        	
        	in.pop();
        	rin.pop();
        	fillIn(start->right, in);
        	fillRIn(end->left, rin);
    	}
    	else if(start->data + end->data > s){
    	    
        	rin.pop();
        	fillRIn(end->left, rin);
    	}
    	else{
            
    	    in.pop();
        	fillIn(start->right, in);
    	}    
    }
    
}

void printNodesSumToS(BinaryTreeNode<int> *root, int s) {
    // Write your code here
    stack<BinaryTreeNode<int> *> in;
    fillIn(root, in);
    stack<BinaryTreeNode<int> *> rin;
    fillRIn(root, rin);
    helper(s, in, rin);    
}

//whole wrong
#include<stack>
void printNodesSumToS(BinaryTreeNode<int> *root, int s) {
    if(root == NULL)
        return;
    stack<BinaryTreeNode<int> *> decr, incr;
	// helper(root, s, decr, incr);
    BinaryTreeNode<int> *leftItr = root;
    while(leftItr != NULL){
        decr.push(leftItr);
        leftItr = leftItr->left;
    }
    BinaryTreeNode<int> *rightItr = root;
    while(rightItr != NULL){
        incr.push(rightItr);
        rightItr = rightItr->right;
    }
    leftItr = decr.top();
    rightItr = incr.top();
    while(!decr.empty() && !incr.empty()){
        leftItr = decr.top();
        rightItr = incr.top();
        if(leftItr == rightItr)
            break;
        if(leftItr->data + rightItr->data == s){
            cout<<leftItr->data<<" "<<rightItr->data<<endl;
            decr.pop();
            incr.pop();
            if(leftItr->right != NULL)
                decr.push(leftItr->right);
            // if(leftItr->left != decr.top() && leftItr->left != NULL)
            //     decr.push(leftItr->left);
            if(rightItr->left != NULL)
                incr.push(rightItr->left);
            // if(rightItr->right != incr.top() && rightItr->right != NULL)
            //     incr.push(rightItr->right);
        }
        else if(leftItr->data + rightItr->data > s){
            incr.pop();
            if(rightItr->left != NULL)
                incr.push(rightItr->left);
        }
        else{
            decr.pop();
            if(leftItr->right != NULL)
                incr.push(leftItr->right);
        }
        cout<<decr.size()<<" "<<incr.size()<<endl;
    }

