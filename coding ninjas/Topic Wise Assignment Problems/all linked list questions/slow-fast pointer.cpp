node* midpoint_linkedlist(node *head)
{
    // Write your code here
    if(head==NULL || head->next==NULL)//length 0 or 1
        return NULL;
	node *slow=head;
    node *fast=head->next;
    while(fast!=NULL && fast->next!=NULL){
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;
}