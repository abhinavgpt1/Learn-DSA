/*
Even after Odd LinkedList
Send Feedback
Arrange elements in a given Linked List such that, all even numbers are placed after odd numbers. Respective order of elements should remain same.
Note: Input and Output has already managed for you. You don't need to print the elements, instead return the head of updated LL.
Input format:
Linked list elements (separated by space and terminated by -1)
Output format:
Print the elements of updated Linked list. 
Sample Input 1 :
1 4 5 2 -1
Sample Output 1 :
1 5 4 2 
Sample Input 2 :
1 11 3 6 8 0 9 -1
Sample Output 2 :
1 11 3 9 6 8 0
*/
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

node* arrange_LinkedList(node* head)
{
    //write your code here
    if(head==NULL || head->next==NULL)
        return head;
    
    node *oddHead=NULL;
    node *oddTail=NULL;
    
    node *evenHead=NULL;
    node *evenTail=NULL;
    
    while(head!=NULL){
        if(head->data % 2==0)
        {
            if(evenHead==NULL)
            {
                evenHead=head;
                evenTail=head;
            }
            else{
                
                evenTail->next=head;
                evenTail=evenTail->next;
            }
        }
        else{
            if(oddHead==NULL)
            {
                oddHead=head;
                oddTail=head;
            }
            else{
                oddTail->next=head;
                oddTail=oddTail->next;
                // oddTail->next=NULL; do it at last
            }

        }
        
        head=head->next;
    }
    
    if(oddHead!=NULL)
    	oddTail->next=NULL;
    if(evenHead!=NULL)
    	evenTail->next=NULL;
    
    if(oddHead!=NULL)
    {
        head=oddHead;
        oddTail->next=evenHead;
        
    }
    else{
        head=evenHead;
    }
    return head;
}
