/*
Running median
Send Feedback
You are given a stream of N integers. For every i-th integer added to the running list of integers, print the resulting median.
Print only the integer part of the median.
Input Format :
The first line of input contains an integer N, denoting the number of integers in the stream.

The second line of input contains 'N' integers separated by a single space.
Output Format :
Print the running median for every integer added to the running list on a new line.
Input Constraints
1 <= N <= 10^5
1 <= Ai <= 10^5

Time Limit: 1sec
Sample Input 1 :
6
6 2 1 3 7 5
Sample Output 1 :
6
4
2
2
3
4
Explanation of Sample Output 1 :
S = {6}, median = 6
S = {6, 2} -> {2, 6}, median = 4
S = {6, 2, 1} -> {1, 2, 6}, median = 2
S = {6, 2, 1, 3} -> {1, 2, 3, 6}, median = 2
S = {6, 2, 1, 3, 7} -> {1, 2, 3, 6, 7}, median = 3
S = {6, 2, 1, 3, 7, 5} -> {1, 2, 3, 5, 6, 7}, median = 4
Sample Input 2 :
5
5 4 3 2 1
Sample Output 2 :
5
4
4
3
3
*/
#include<cmath>
#include<queue>
void findMedian(int *arr, int n)
{
    // Write your code here
    if(n == 0)
        return;
 	priority_queue<int> maxHp;
    priority_queue<int, vector<int>, greater<int>> minHp;
    for(int i=0; i<n; i++){
        if(maxHp.empty() || arr[i] < maxHp.top()){
            maxHp.push(arr[i]);
        }
        else if(minHp.empty() || arr[i] > minHp.top()){
            minHp.push(arr[i]);
        }
        else
            minHp.push(arr[i]);
        //rebalance
        if(abs(int(maxHp.size()) - int(minHp.size())) == 2){
            if(maxHp.size() > minHp.size()){
                minHp.push(maxHp.top());
                maxHp.pop();
            }
            else{
                maxHp.push(minHp.top());
                minHp.pop();
            }
        }
        //ans
        if(i % 2 == 1){
            cout<<(minHp.top() + maxHp.top())/2<<" ";
        }
        else
            cout<<(minHp.size() > maxHp.size() ? minHp.top() : maxHp.top())<<" ";
        
    }
}
//previously
#include<queue>
#include<cmath>
void findMedian(int arr[], int n){
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Print output as specified in the question.
     */
	priority_queue<int> maxH;
    priority_queue<int, vector<int>, greater<int>> minH;
    
    maxH.push(arr[0]);
    cout<<arr[0]<<endl;
    for(int i=1;i<n;i++){
        
        if(maxH.top() > arr[i])
            maxH.push(arr[i]);        
        else
		    minH.push(arr[i]);
        
        //adjust
        // minH.size() gives unsigned value. So, 1(unsigned) - 2(unsigned) = -1(unsigned) == some positive value
        if(abs(minH.size() - maxH.size()) > 1)
        {
            if(minH.size() > maxH.size())
            {
                maxH.push(minH.top());
                minH.pop();
			}
            else{
                minH.push(maxH.top());
                maxH.pop();
            }
            // cout<<"adjusted";
            
            
        }
        
        
        if(i % 2 == 1)//(minH.size() + maxH.size()) % 2 == 0
            cout<<(minH.top() + maxH.top()) / 2 << endl; 
        else//no. of elements are odd
            cout<< ( maxH.size() > minH.size() ? maxH.top() : minH.top()) << endl;
        
    }
}
