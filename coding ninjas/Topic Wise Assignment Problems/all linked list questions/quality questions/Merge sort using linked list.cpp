/*
Merge sort using linked list
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
node * merge(node *head1,node *head2){
    node *head=NULL;
    node *tail=NULL;
    while(head1!=NULL && head2!=NULL){
        if(head==NULL){
            if(head1->data <= head2->data){
                head=tail=head1;
                head1=head1->next;
            }
            else
            {
                head=tail=head2;
                head2=head2->next;
            }
        }
        else if(head1->data <= head2->data){
            tail->next=head1;
            tail=head1;
            head1=head1->next;
        }
        else{
            tail->next=head2;
            tail=head2;
            head2=head2->next;
        }
    }
    
    if(head1!=NULL)
        tail->next=head1;
    if(head2!=NULL)
        tail->next=head2;
    
    return head;
}
node* mergeSort(node *head) {
    //write your code here
    if(head==NULL)//length 0
        return NULL;
    if(head->next==NULL)
        return head;
    node * slow=head;
	node * fast=head->next;
    while(fast!=NULL && fast->next!=NULL){
        slow=slow->next;
        fast=fast->next->next;
    }
        
    node *head2=slow->next;
    slow->next=NULL;
    
    head=mergeSort(head);
    head2=mergeSort(head2);
    return merge(head,head2);
}
