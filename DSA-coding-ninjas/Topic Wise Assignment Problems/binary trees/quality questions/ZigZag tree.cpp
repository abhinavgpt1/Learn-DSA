/*
ZigZag tree
Send Feedback
Given a binary tree, print the zig zag order i.e print level 1 from left to right, level 2 from right to left and so on. This means odd levels should get printed from left to right and even level right to left.
Input format :

Elements in level order form (separated by space)

(If any node does not have left or right child, take -1 in its place)

Output Format :

Elements are printed level wise, each level in new line (separated by space).

Sample Input :
5 6 10 2 3 -1 -1 -1 -1 -1 9 -1 -1
Sample Output :
5
10 6
2 3
9
*/

// can be solved by
// A) two stacks
// B) toggle switch + vector
// C) one queue one stack
// D) two queues one stack
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
// A)
void zigZagOrder(BinaryTreeNode<int> *root)
{
    // Write your code here
    if (root == NULL)
        return;
    stack<BinaryTreeNode<int> *> LtoR;
    stack<BinaryTreeNode<int> *> RtoL;

    LtoR.push(root);

    while (!LtoR.empty() || !RtoL.empty())
    {

        while (!LtoR.empty())
        {

            BinaryTreeNode<int> *temp = LtoR.top();
            LtoR.pop();
            cout << temp->data << " ";

            if (temp->left != NULL)
                RtoL.push(temp->left);
            if (temp->right != NULL)
                RtoL.push(temp->right);
        }
        cout << endl;

        while (!RtoL.empty())
        {

            BinaryTreeNode<int> *temp = RtoL.top();
            RtoL.pop();
            cout << temp->data << " ";

            if (temp->right != NULL)
                LtoR.push(temp->right);
            if (temp->left != NULL)
                LtoR.push(temp->left);
        }
        cout << endl;
    }
}

//B)
#include <algorithm>
void print(vector<int> arr, bool toggle)
{
    if (toggle)
        reverse(arr.begin(), arr.end());
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}
void zigZagOrder(BinaryTreeNode<int> *root)
{
    // Write your code here
    if (root == NULL)
        return;
    queue<BinaryTreeNode<int> *> pending;
    pending.push(root);
    pending.push(NULL);
    bool toggle = false;
    vector<int> arr;
    while (!pending.empty())
    {
        BinaryTreeNode<int> *front = pending.front();
        pending.pop();
        if (front != NULL)
        {
            arr.push_back(front->data);
            if (front->left != NULL)
                pending.push(front->left);
            if (front->right != NULL)
                pending.push(front->right);
        }
        else
        {
            print(arr, toggle);
            arr.clear();
            if (!pending.empty())
                pending.push(NULL);
            toggle = !toggle;
        }
    }
}
// C) gfg
#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;
};

/* Utility function to create a new tree node */
Node *newNode(int val)
{
    Node *new_node = new Node;
    new_node->data = val;
    new_node->left = new_node->right = NULL;
    return new_node;
}

/* Function to print a tree in spiral form 
using one stack */
void printSpiralUsingOneStack(Node *root)
{
    if (root == NULL)
        return;

    stack<int> s;
    queue<Node *> q;

    bool reverse = true;
    q.push(root);
    while (!q.empty())
    {

        int size = q.size();
        while (size)
        {
            Node *p = q.front();
            q.pop();

            // if reverse is true, push node's
            // data onto the stack, else print it
            if (reverse)
                s.push(p->data);
            else
                cout << p->data << " ";

            if (p->left)
                q.push(p->left);
            if (p->right)
                q.push(p->right);
            size--;
        }

        // print nodes from the stack if
        // reverse is true
        if (reverse)
        {
            while (!s.empty())
            {
                cout << s.top() << " ";
                s.pop();
            }
        }

        // the next row has to be printed as
        // it is, hence change the value of
        // reverse
        reverse = !reverse;
    }
}

//D) not so good efficiency
void zigZagOrder(BinaryTreeNode<int> *root)
{
    // Write your code here
    if (root == NULL)
        return;
    queue<BinaryTreeNode<int> *> pending;
    queue<int> ans;
    bool isLevelEven = false;
    pending.push(root);
    pending.push(NULL);
    while (pending.size() != 0)
    {

        BinaryTreeNode<int> *front = pending.front();
        pending.pop();
        if (front == NULL)
        {

            if (isLevelEven)
            // reverse(ans.begin(),ans.end());//wrong since stacks, queues have no begin()
            //reversing the queue
            {
                stack<int> s;
                while (!ans.empty())
                {
                    s.push(ans.front());
                    ans.pop();
                }
                while (!s.empty())
                {
                    ans.push(s.top());
                    s.pop();
                }
            }

            //printing the queue
            while (!ans.empty())
            {
                cout << ans.front() << " ";
                ans.pop();
            }
            cout << endl;
            //toggling order of printing
            isLevelEven = (isLevelEven == false);

            if (pending.size() != 0)
                pending.push(NULL);
        }
        else
        {
            ans.push(front->data);
            if (front->left != NULL)
                pending.push(front->left);
            if (front->right != NULL)
                pending.push(front->right);
        }
    }
}
