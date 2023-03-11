/*
Foldable Binary Tree
Given a binary tree, check if the tree can be folded or not. A tree can be folded if left and right subtrees of the tree are structure wise same. An empty tree is considered as foldable.
Consider the below trees:
(a) and (b) can be folded.
(c) and (d) cannot be folded.


(a)
       10
     /    \
    7      15
     \    /
      9  11
(b)
        10
       /  \
      7    15
     /      \
    9       11
(c)
        10
       /  \
      7   15
     /    /
    5   11
(d)
         10
       /   \
      7     15
    /  \    /
   9   10  12

Example 1:

Input:
     10
    /    \
   7     15
 /  \   /  \
N   9  11   N
Output:Yes
Example 2:

Input:
      10
    /    \
   7     15
 /  \   /  \
5   N  11   N
Output: No

Your Task:
The task is to complete the function isFoldable() that takes root of the tree as input and returns true or false depending upon whether the tree is foldable or not.

Expected Time Complexity: O(N).
Expected Auxiliary Space: O(Height of the Tree).

Constraints:
1 <= n <= 103
1 <= data of node <= 104
*/
// { Driver Code Starts
#include <bits/stdc++.h>

using namespace std;

// Tree Node
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Function to Build Tree
Node *buildTree(string str) {
    // Corner Case
    if (str.length() == 0 || str[0] == 'N')
        return NULL;

    // Creating vector of strings from input
    // string after spliting by space
    vector<string> ip;

    istringstream iss(str);
    for (string str; iss >> str;)
        ip.push_back(str);

    // Create the root of the tree
    Node *root = new Node(stoi(ip[0]));

    // Push the root to the queue
    queue<Node *> queue;
    queue.push(root);

    // Starting from the second element
    int i = 1;
    while (!queue.empty() && i < ip.size()) {

        // Get and remove the front of the queue
        Node *currNode = queue.front();
        queue.pop();

        // Get the current Node's value from the string
        string currVal = ip[i];

        // If the left child is not null
        if (currVal != "N") {

            // Create the left child for the current Node
            currNode->left = new Node(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->left);
        }

        // For the right child
        i++;
        if (i >= ip.size())
            break;
        currVal = ip[i];

        // If the right child is not null
        if (currVal != "N") {

            // Create the right child for the current Node
            currNode->right = new Node(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->right);
        }
        i++;
    }

    return root;
}


 // } Driver Code Ends


/* Returns true if the given tree is foldable */

/* A binary tree node has data, pointer to left child
and a pointer to right child */
/*struct node
{
    int data;
    struct node* left;
    struct node* right;

    node(int x){
        data = x;
        left = right = NULL;
    }
};
*/
bool isPalindrome(string str){
    string cpy=str;
    reverse(cpy.begin(),cpy.end());
    return cpy==str;
}
bool IsFoldable(Node* root)
{
    // Your code goes here
    if(root==NULL)
    return true;
    if((root->left==NULL && root->right!=NULL)||(root->right==NULL && root->left!=NULL))
    return false;

    queue<Node *> pending;
    pending.push(root);
    pending.push(NULL);
    string str="";
    while(pending.size()!=0){

        Node *front=pending.front();
        pending.pop();

        if(front==NULL){

            if(!isPalindrome(str))
            return false;
            else
            str="";

            if(pending.size()!=0)
            pending.push(NULL);

        }
        else{


            if(front->left!=NULL)
            {
                pending.push(front->left);
                str+="P";
            }
            else
                str+="N";


            if(front->right!=NULL)
            {
                pending.push(front->right);
                str+="P";
            }
            else
                str+="N";

        }




    }
    return true;



}

// { Driver Code Starts.

int main() {
    int tc;
    scanf("%d ", &tc);
    while (tc--) {
        string treeString;
        getline(cin, treeString);
        Node *root = buildTree(treeString);
        if (IsFoldable(root)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }

    }


    return 0;
}  // } Driver Code Ends

//second solution
// C++ program to check foldable binary tree
#include <bits/stdc++.h>
using namespace std;

/* You would want to remove below
3 lines if your compiler supports
bool, true and false */
#define bool int
#define true 1
#define false 0

/* A binary tree node has data,
pointer to left child and a
pointer to right child */
class node {
public:
	int data;
	node* left;
	node* right;
};

/* converts a tree to its mrror image */
void mirror(node* node);

/* returns true if structure of
two trees a and b is same only
structure is considered for comparison, not data! */
bool isStructSame(node* a, node* b);

/* Returns true if the given tree is foldable */
bool isFoldable(node* root)
{
	bool res;

	/* base case */
	if (root == NULL)
		return true;

	/* convert left subtree to its mirror */
	mirror(root->left);

	/* Compare the structures of the
	right subtree and mirrored
	left subtree */
	res = isStructSame(root->left, root->right);

	/* Get the originial tree back */
	mirror(root->left);

	return res;
}

bool isStructSame(node* a, node* b)
{
	if (a == NULL && b == NULL) {
		return true;
	}
	if (a != NULL && b != NULL && isStructSame(a->left, b->left) && isStructSame(a->right, b->right)) {
		return true;
	}

	return false;
}

/* UTILITY FUNCTIONS */
/* Change a tree so that the roles of the left and
	right pointers are swapped at every node.
	See https:// www.geeksforgeeks.org/?p=662 for details */
void mirror(node* Node)
{
	if (Node == NULL)
		return;
	else {
		node* temp;

		/* do the subtrees */
		mirror(Node->left);
		mirror(Node->right);

		/* swap the pointers in this node */
		temp = Node->left;
		Node->left = Node->right;
		Node->right = temp;
	}
}

/* Helper function that allocates a new node with the
given data and NULL left and right pointers. */
node* newNode(int data)
{
	node* Node = new node();
	Node->data = data;
	Node->left = NULL;
	Node->right = NULL;

	return (Node);
}

/* Driver program to test mirror() */
int main(void)
{
	/* The constructed binary tree is
			1
		/ \
		2 3
		\ /
		4 5
	*/
	node* root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->right->left = newNode(4);
	root->left->right = newNode(5);

	if (isFoldable(root) == 1) {
		cout << "tree is foldable";
	}
	else {
		cout << "\ntree is not foldable";
	}
	return 0;
}

// This code is contributed by rathbhupendra


//method 3
#include <bits/stdc++.h>
using namespace std;

/* You would want to remove below 3 lines if your compiler
supports bool, true and false */
#define bool int
#define true 1
#define false 0

/* A binary tree node has data, pointer to left child
and a pointer to right child */
class node {
public:
	int data;
	node* left;
	node* right;
};

/* A utility function that checks
if trees with roots as n1 and n2
are mirror of each other */
bool IsFoldableUtil(node* n1, node* n2);

/* Returns true if the given tree can be folded */
bool IsFoldable(node* root)
{
	if (root == NULL) {
		return true;
	}

	return IsFoldableUtil(root->left, root->right);
}

/* A utility function that checks
if trees with roots as n1 and n2
are mirror of each other */
bool IsFoldableUtil(node* n1, node* n2)
{
	/* If both left and right subtrees are NULL,
	then return true */
	if (n1 == NULL && n2 == NULL) {
		return true;
	}

	/* If one of the trees is NULL and other is not,
	then return false */
	if (n1 == NULL || n2 == NULL) {
		return false;
	}

	/* Otherwise check if left and right subtrees are mirrors of
	their counterparts */
	return IsFoldableUtil(n1->left, n2->right) && IsFoldableUtil(n1->right, n2->left);
}

/*UTILITY FUNCTIONS */
/* Helper function that allocates a new node with the
given data and NULL left and right pointers. */
node* newNode(int data)
{
	node* Node = new node();
	Node->data = data;
	Node->left = NULL;
	Node->right = NULL;

	return (Node);
}

/* Driver code */
int main(void)
{
	/* The constructed binary tree is
		1
		/ \
		2 3
		\ /
		4 5
	*/
	node* root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->right = newNode(4);
	root->right->left = newNode(5);

	if (IsFoldable(root) == true) {
		cout << "tree is foldable";
	}
	else {
		cout << "tree is not foldable";
	}

	return 0;
}

// This is code is contributed by rathbhupendra
