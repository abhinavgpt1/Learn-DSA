/*
kReverse
Send Feedback
Implement kReverse( int k ) in a linked list i.e. you need to reverse first K elements then reverse next k elements and join the linked list and so on.
Indexing starts from 0. If less than k elements left in the last, you need to reverse them as well. If k is greater than length of LL, reverse the complete LL.
You don't need to print the elements, just return the head of updated LL.
Input format :

Line 1 : Linked list elements (separated by space and terminated by -1)

Line 2 : k

Sample Input 1 :
1 2 3 4 5 6 7 8 9 10 -1
4
Sample Output 1 :
4 3 2 1 8 7 6 5 10 9
Sample Input 2 :
1 2 3 4 5 -1
2
Sample Output 2 :
2 1 4 3 5 
Sample Input 3 :
1 2 3 4 5 6 7 -1
3
Sample Output 3 :
3 2 1 6 5 4 7
*/
//head is the head of the linked list, n is number of elements to be reversed
/****************************************************************
 
    Following is the class structure of the Node class:

        class Node
        {
        public:
            int data;
            Node *next;
            Node(int data)
            {
                this->data = data;
                this->next = NULL;
            }
        };

*****************************************************************/

// recursively
Node* kReverse(Node*head,int n)
{
    //write your code here
    if(head==NULL)
        return NULL;
    
    if(n==0 || n==1)
        return head;
    
    int count=0;
    Node *prev=NULL;
    Node *curr=head;
    Node *next=head;
    while(count!=n){
        if(next==NULL)
            break;
        next=curr->next;
        curr->next=prev;
        
        prev=curr;
        curr=next;
        count++;
    }
    Node *head2 = kReverse(next,n);
    head->next=head2;
    
    return prev;
}

// iteratively
/*
#include<utility>
pair<Node *, Node*> reverse(Node *head, Node *tail){
    pair<Node*, Node*> ans;
    // ans.first = tail; for case when 9->10->NULL => head = 9, tail = NULL...gives us wrong ans (returning head = NULL...thus losing 10,9)
    
    ans.second = head;
    
    Node * prev = NULL;
    Node * curr = head;
    Node * next = head;
    while(curr != NULL){
        next = next->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    ans.first = prev;
    return ans;
}
Node * findKth(Node * head, int k){
    int count = 1;
    while(head != NULL && count<k){
        head = head->next;
        count++;
    }
    return head;
}
Node *kReverse(Node *head, int k)
{
    //Write your code here
    if(k==0 || k==1)
        return head;
    Node * newHead = NULL;
    Node * newTail = NULL;
    Node * iter = head;
    while(iter != NULL){
        Node *kthNode = findKth(iter, k);
        Node *kplus1Node = NULL;
        if(kthNode != NULL)
        {   
            kplus1Node = kthNode->next;
            kthNode->next = NULL;
        }
        pair<Node *, Node *> p = reverse(iter,kthNode);
        if(newHead == NULL){
            newHead = p.first;
            newTail = p.second;
        }
        else{
            newTail->next = p.first;
            newTail = p.second;
        }
        iter = kplus1Node;
    }
    return newHead;
}
*/