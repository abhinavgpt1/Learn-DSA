/*
Remove loop in Linked List 
You are given a linked list of N nodes. The task is to remove the loop from the linked list, if present. 

Note: C is the position of the node to which the last node is connected. If it is 0 then no loop.

Example 1:

Input:
N = 3
value[] = {1,3,4}
C = 2
Output: 1
Explanation: In the first test case
N = 3.The linked list with nodes
N = 3 is given. Here, x = 2 which
means last node is connected with xth
node of linked list. Therefore, there
exists a loop. 

Example 2:
Input:
N = 4
value[] = {1,8,3,4}
C = 0
Output: 1
Explanation: N = 4 and x = 0, which
means lastNode->next = NULL, thus
the Linked list does not contains
any loop.
Your Task:
Your task is to complete the function removeLoop(). The only argument of the function is head pointer of the linked list. Simply remove the loop in the list (if present) without disconnecting any nodes from the list. The driver code will print 1 if your code is correct.

Expected time complexity : O(n)

Expected auxiliary space : O(1)

Constraints:
1 <= N <= 104
*/
// { Driver Code Starts
// driver code

#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
    
    Node(int val)
    {
        data = val;
        next = NULL;
    }
};

void loopHere(Node* head, Node* tail, int position)
{
    if(position==0) return;
    
    Node* walk = head;
    for(int i=1; i<position; i++)
        walk = walk->next;
    tail->next = walk;
}

bool isLoop(Node* head)
{
    if(!head) return false;
    
    Node* fast = head->next;
    Node* slow = head;
    
    while( fast != slow)
    {
        if( !fast || !fast->next ) return false;
        fast=fast->next->next;
        slow=slow->next;
    }
    
    return true;
}

int length(Node* head)
{
    int ret = 0;
    while(head)
    {
        ret++;
        head = head->next;
    }
    return ret;
}

void removeLoop(Node* head);

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n, num;
        cin>>n;
        
        Node *head, *tail;
        cin>> num;
        head = tail = new Node(num);
        
        for(int i=0 ; i<n-1 ; i++)
        {
            cin>> num;
            tail->next = new Node(num);
            tail = tail->next;
        }
        
        int pos;
        cin>> pos;
        loopHere(head,tail,pos);
        
        removeLoop(head);
        
        if( isLoop(head) || length(head)!=n )
            cout<<"0\n";
        else
            cout<<"1\n";
    }
	return 0;
}
// } Driver Code Ends


/*
structure of linked list node:

struct Node
{
    int data;
    Node* next;
    
    Node(int val)
    {
        data = val;
        next = NULL;
    }
};

*/
#include<climits>
#include<vector>
void removeLoop(Node* head)
{
    // code here
    // just remove the loop without losing any nodes
    if(head==NULL || head->next==NULL)
    return;
    vector<int> save;
    
    Node * iter = head;
    while(iter->next!=NULL){
        
        save.push_back(iter->data);
        iter->data=INT_MIN;
        
        if(iter->next->data==INT_MIN){
            iter->next=NULL;
            break;
        }
        iter = iter->next;
        
    }
    
    iter=head;
    for(int x:save){
        iter->data=x;
        // cout<<"iter->data:"<<iter->data<<endl;
        iter=iter->next;
    }
}

//see gfg article IMAGE FOR METHOD 2