/*
Delete every N nodes
Send Feedback
Given a linked list and two integers M and N. Traverse the linked list such that you retain M nodes then delete next N nodes, continue the same until end of the linked list. That is, in the given linked list you need to delete N nodes after every M nodes.
Input format :

Line 1 : Linked list elements (separated by space and terminated by -1)

Line 2 : M

Line 3 : N

Sample Input 1 :
1 2 3 4 5 6 7 8 -1
2
2
Sample Output 1 :
1 2 5 6
Sample Input 2 :
1 2 3 4 5 6 7 8 -1
2
3
Sample Output 2 :
1 2 6 7
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
//solution 1 : easier

Node * deleteN(Node * head, int n){
    if(head == NULL)
        return head;
    Node * iter = head;
    int count = 1;
    while(count != n && iter != NULL){
        iter=iter->next;
        count++;
    }
    if(iter == NULL)
        return iter;
    return iter->next;
}
Node *skipMdeleteN(Node *head, int M, int N)
{
    // Write your code here
    if(head == NULL || N == 0)
        return head;
    if(M == 0)
        return NULL;
    
    
    Node * iter = head;
    int count = 1;
    while(iter!=NULL){
        if(count % M == 0)
        {
            iter->next = deleteN(iter->next, N); 
        }
        iter = iter->next;
        count++;
    }
    return head;
}









//solution 2
node *deleteN(node *head,int n){
    int c=0;
    node *temp=head;

    while(c!=n){
        if(head==NULL)
            return NULL;
		head=head->next;
        c++;
        temp->next=NULL;
        delete temp;
        temp=head;
    }

    return head;
}
node* skipMdeleteN(node  *head, int M, int N) {
    // Write your code here
    if(head==NULL)
        return head;
    if(M<=0||N<=0)//would be clearly mentioned in actual problems
        return NULL;
    node *iter=head;
    int length=0;
    while(iter!=NULL){
        length++;
        iter=iter->next;
    }
    if(M>length || N>length)
        return head;
    //till here m, n are legit
    // node*temp=deleteN(head->next->next->next,N);
    // cout<<temp->data<<endl;
	int c1=1;
    iter=head;

    while(iter->next!=NULL){
        if(c1==M){
            node*temp=deleteN(iter->next,N);
            iter->next=temp;
			c1=0;
            if(temp==NULL)
                break;
        }
        c1++;
        iter=iter->next;
    }

    return head;
}