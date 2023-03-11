/*
Stock Span
Send Feedback
The span si of a stock’s price on a certain day i is the minimum number of consecutive days (up to the current day) the price of the stock has been less than its price on that ith day. If for a particular day, if no stock price is greater then just count the number of days till 0th day including current day.
For eg. if given price array is {3, 6, 8, 1, 2}, span for 4th day (which has price 2) is 2 because minimum count of consecutive days (including 4th day itself) from current day which has price less than 4th day is 2 (i.e. day 3 & 4). Similarly, span for 2nd day is 3 because no stock price in left is greater than 2nd day's price. So count is 3 till 0th day.
Given an input array with all stock prices, you need to return the array with corresponding spans of each day.
Note : Try doing it in O(n).
Input format :
Line 1 : Integer n, Arrays Size
Line 2 : Price for n days (separated by space). It can contain duplicate values`
Constraints:
Time Limit: 1 second
Size of input array lies in the range: [1, 1000000]
Output format :
Return an array that contain span for each day
Sample Input 1 :
8
60 70 80 100 90 75 80 120
Sample Output 1 :
1 2 3 4 1 1 2 8
Sample Input 2 :
 4
 1 1 1 1
Sample Output 2 :
1 1 1 1
*/

//method 1: O(n^2)
#include<stack>
int* stockSpan(int *price, int size) {
	// Write your code here
	stack<int> s;
    int *ans=new int[size];
    for(int i=0;i<size;i++){
        if(i==0)
            ans[i]=1;
        else{
                int min=1;
            	for(int j=i-1;j>=0;j--){
                	if(price[j]<price[i])
                		min++;
                    else
                    	break;	
            	}
                
                ans[i]=min;    
        }
    }
    return ans;
}
//method 2: O(n)
#include<stack>
int* stockSpan(int *price, int size) {
    // Write your code here
    int *ans=new int[size];
    stack<int> sindices;
    sindices.push(0);
    ans[0]=1;
    for(int i=1;i<size;i++){
        while(!sindices.empty() && price[sindices.top()] < price[i]){
            sindices.pop();
        }
        
        if(sindices.empty())
        {
            ans[i]=i+1;
            sindices.push(i);
        }
        else{
            
            ans[i]=i-sindices.top();
            sindices.push(i);            
        }
    }
    return ans;
}
//method2 alternate
int* stockSpan(int *price, int size)  {
	// Write your code here
    int* ans = new int[size]();
    stack<int> stk;
    ans[0] = 1;
    stk.push(0);
    for(int i=1; i<size; i++){
        ans[i] = 1;
        if(price[i] > price[i-1]){
            int topIndex = stk.top();
            
            while(price[topIndex] < price[i]){
                stk.pop();
                ans[i]+=ans[topIndex];
                if(stk.empty())
                    break;
                topIndex = stk.top();
            }
        }
        stk.push(i);
    }
    return ans;
}