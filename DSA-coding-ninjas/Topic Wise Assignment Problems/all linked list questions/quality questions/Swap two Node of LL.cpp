/*
Swap two Node of LL
Send Feedback
Given a linked list, i & j, swap the nodes that are present at i & j position in the LL. You need to swap the entire nodes, not just the data.
Indexing starts from 0. You don't need to print the elements, just swap and return the head of updated LL.
Assume i & j given will be within limits. And i can be greater than j also.
Input format :

Line 1 : Linked list elements (separated by space and terminated by -1)

Line 2 : i and j (separated by space)

Sample Input 1 :
3 4 5 2 6 1 9 -1
3 4
Sample Output 1 :
3 4 5 6 2 1 9
Sample Input 2 :
3 4 5 2 6 1 9 -1
2 4
Sample Output 2 :
3 4 6 2 5 1 9
*/
//head is head of your linked list, i and j are indexes to be swapped
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
int length(Node * head){
    if(head==NULL)
        return 0;
    int count=1;
    while(head != NULL)
    {
        head = head-> next;
        count++;
    }
    return count;
}
Node *swapNodes(Node *head, int i, int j)
{
    //Write your code here
    int len = length(head);
    if(i < 0 || j < 0 || i >= len || j >= len || i==j)
        return head;
    
    Node *previ = NULL;
    Node *curri = NULL;
    Node *prevj = NULL;
    Node *currj = NULL;
    
    Node * iter = head;
    int count = 0;
    while(iter != NULL){
        if(count == i-1)
            previ = iter;
        if(count == j-1)
            prevj = iter;
        iter = iter->next;
        count++;
    }
    if(i == 0)
        curri = head;
    else
        curri = previ->next;
    if(j == 0)
        currj = head;
    else
        currj = prevj->next;
    
    //replacing prev's
    if(previ == NULL)
        head = currj;//eg, i = 0, j = 4
    else
        previ->next = currj;
    
    if(prevj == NULL)
        head = curri;
    else
        prevj->next = curri;
    
    //replacing next's
    Node *temp = curri->next;
    curri->next = currj->next;
    currj->next = temp;
    
    return head;
}
