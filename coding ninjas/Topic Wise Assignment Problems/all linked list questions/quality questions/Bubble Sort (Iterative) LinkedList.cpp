/*
Bubble Sort (Iterative) LinkedList
Send Feedback
Sort a given linked list using Bubble Sort (iteratively). While sorting, you need to swap the entire nodes, not just the data.
You don't need to print the elements, just sort the elements and return the head of updated LL.
Input format : Linked list elements (separated by space and terminated by -1)`

Sample Input 1 :
1 4 5 2 -1
Sample Output 1 :
1 2 4 5
*/
//head is the head of the linked list
// Following is the node structure
/**************
class node{
public:
    int data;
    node * next;
    node(int data){
        this->data=data;
        this->next=NULL;
    }
};
***************/
int length(node *head){
    int count=0;
    while(head!=NULL){
        head=head->next;
        count++;
    }
    return count;
}
node * swap(node *head, int i, int j){
    if(i<0 || j<0 || i==j)
        return head;
    int l = length(head);
    if(i>l-1 || j>l-1)
        return head;
    
    int count=0;
    node * previ=NULL;
    node * curri=head;
    
    while(count!=i){
        previ=curri;
    	curri=curri->next;    
        count++;
    }
    
    count=0;
    node * prevj=NULL;
    node * currj=head;
    
    while(count!=j){
        prevj=currj;
    	currj=currj->next;    
        count++;
    }
    
    if(previ==NULL)
        head=currj;
    else
        previ->next=currj;
    
    if(prevj==NULL)
        head=curri;
    else
        prevj->next=curri;
    
    node *temp=curri->next;
    curri->next=currj->next;
    currj->next=temp;
    
    return head;    
}
node* bubble_sort_LinkedList_itr(node* head)
{
    //write your code here
    if(head==NULL || head->next==NULL)
        return head;
    
    int l=length(head);
    
    for(int i=0;i<l;i++){
        node * prev=NULL;
        node * curr=head;
        node * next=head->next;
        while(curr->next!=NULL){
            if(curr->data <= curr->next->data){
                prev=curr;
                curr=curr->next;
            }
            else{
                if(prev==NULL){
                    head=curr->next;
                    next=curr->next;
                    curr->next=next->next;
                    next->next=curr;
                    
                    prev=next;
                }
                else{
                   prev->next=curr->next;
                    next=curr->next;
                    curr->next=next->next;
                    next->next=curr;
                    
                    prev=next;
                }
            }
        }
    }
    return head;
}
//method 2
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
int length(Node *head){
    if(head == NULL)
        return 0;
    int count=0;
    while(head != NULL){
        head=head->next;
        count++;
    }
    return count;
}
Node *bubbleSort(Node *head)
{
    // Write your code here
    if(head == NULL || head->next == NULL)
        return head;
    
    int len = length(head);
    for(int i = 1; i <= len; i++){
        Node *prev = NULL;
        Node *curr = head;
          while(curr->next != NULL) {
            if(curr->data > curr->next->data)
            {
                if(prev == NULL){
                    head = curr->next;
                    curr->next = head->next;
                    head->next = curr;
                    prev = head;
                }
                else{
                    prev->next = curr->next;
                    curr->next = prev->next->next;
                    prev->next->next = curr;
                    prev = prev->next;
                }
                //naive way
                // int temp = curr->data;
                // curr->data = curr->next->data;
                // curr->next->data = temp;
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
    }
    return head;
    
}