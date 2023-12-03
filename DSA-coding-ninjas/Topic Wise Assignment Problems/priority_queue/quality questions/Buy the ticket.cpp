/*
Buy the ticket
Send Feedback
You want to buy a ticket for a well-known concert which is happening in your city. But the number of tickets available is limited. Hence the sponsors of the concert decided to sell tickets to customers based on some priority.
A queue is maintained for buying the tickets and every person has attached with a priority (an integer, 1 being the lowest priority). The tickets are sold in the following manner -
1. The first person (pi) in the queue asked to comes out.
2. If there is another person present in the queue who has higher priority than pi, then ask pi to move at end of the queue without giving him the ticket.
3. Otherwise, give him the ticket (and don't make him stand in queue again).
Giving a ticket to a person takes exactly 1 minutes and it takes no time for removing and adding a person to the queue. And you can assume that no new person joins the queue.
Given a list of priorities of N persons standing in the queue and the index of your priority (indexing starts from 0). Find and return the time it will take until you get the ticket.
Input Format :
Line 1 : Integer N (Total number of people standing in queue)
Line 2 : Priorities of every person (n space separated integers)
Line 3 : Integer k (index of your priority)
Output Format :
Time required
Sample Input 1 :
3
3 9 4
2
Sample Output 1 :
2
Sample Output 1 Explanation :
Person with priority 3 comes out. But there is a person with higher priority than him. So he goes and then stands in the queue at the end. Queue's status : {9, 4, 3}. Time : 0 secs.
Next, the person with priority 9 comes out. And there is no person with higher priority than him. So he'll get the ticket. Queue's status : {4, 3}. Time : 1 secs.
Next, the person with priority 4 comes out (which is you). And there is no person with higher priority than you. So you'll get the ticket. Time : 2 secs.
Sample Input 2 :
5
2 3 2 2 4
3
Sample Output 2 :
4
*/
#include<queue>
int buyTicket(int *arr, int n, int k) {
    queue<int> que;
    priority_queue<int> maxHp;
    int time = 0;
    for(int i=0; i<n; i++){
        que.push(i);
        maxHp.push(arr[i]);
    }
    while(1){
        int indexFront = que.front();
        if(arr[indexFront] == maxHp.top()){
            que.pop();
            maxHp.pop();
            time++;
            if(indexFront == k)
                return time;
        }
        else{
            que.pop();
            que.push(indexFront);
        }
    }
    return -1;
}

//won't work if indices of same prioirty needs to be considered
// except this fact both below solutions are good

#include<queue>
int buyTicket (int *arr, int n, int k){
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Return output and don't print it.
     * Taking input and printing output is handled automatically.
     */
    int time = 0;
    priority_queue<int> pq;
    queue<int> que;
    for(int i = 0; i < n; i++){
        pq.push(arr[i]);
        que.push(arr[i]);
    }
    int K = arr[k];
    while(1){
        int front = que.front();
        que.pop();
        if(front == pq.top()){
            pq.pop();
            time++;
            if(front == K)
                break;
        }
        else{
            que.push(front);
        }
    }
    return time;
}

#include<deque>
#include<queue>
int buyTicket (int *arr, int n, int k){
    
    priority_queue<int> pq;
    deque<int> dq;
    for(int i=0;i<n;i++){
		pq.push(arr[i]);
        dq.push_back(arr[i]);
    }
    int time = 0;
    int our_priority = arr[k];
    while(!pq.empty()){
        
        if(pq.top() == dq.front()){
            
            time++;
            
            if(pq.top() == our_priority)
                return time;
            pq.pop();
            dq.pop_front();
        }
        else{
            int temp = dq.front();
            dq.pop_front();
            dq.push_back(temp);
        }
        
    }
    return time;
}