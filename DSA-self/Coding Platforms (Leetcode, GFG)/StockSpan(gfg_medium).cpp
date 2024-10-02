/**
 * Stock span problem
 * ------------------
 * The stock span problem is a financial problem where we have a series of n daily price quotes for a stock 
 * and we need to calculate the span of stocks price for all n days.
 * The span Si of the stocks price on a given day i is defined as the maximum number of consecutive days just before the given day, for which the price of the stock on the given day is less than or equal to its price on the current day.
 * For example, if an array of 7 days prices is given as {100, 80, 60, 70, 60, 75, 85}, then the span values for corresponding 7 days are {1, 1, 1, 2, 1, 4, 6}.
 * 
 * Expected Time Complexity: O(N).
 * Expected Auxiliary Space: O(N).
 * 
 * Constraints:
 * 1 ≤ N ≤ 10^5
 * 1 ≤ C[i] ≤ 10^5
 */
// link: https://www.geeksforgeeks.org/problems/stock-span-problem-1587115621/1
// link: https://leetcode.com/problems/online-stock-span/description/
// article: https://www.geeksforgeeks.org/the-stock-span-problem/

// O(n), O(n)
class Solution{
    public:
    vector <int> calculateSpan(int price[], int n)
    {
       // [WRONG]aim is to store local maxima as we traverse on price[]
       // editorial: Know the closest day preceding i s.t. price is greater than price[i]
       stack<int> cgs; //closest greater stock
       vector<int> ans;
       
       cgs.push(0);
       ans.push_back(1);
       
       for(int i=1; i<n; i++){
            while(!cgs.empty() && price[cgs.top()] <= price[i])
                cgs.pop();
            
            ans.push_back(cgs.empty() ? i+1 : i - cgs.top());
            cgs.push(i);
       }
       return ans;
    }
};

// O(n), O(n)
class Solution {
public:
    vector <int> calculateSpan(int price[], int n) {
        stack<int> stk;
        vector<int> ans(n, 1);
        
        for(int i=0; i<n; i++){
            if(stk.empty() || price[stk.top()] > price[i]) {
                stk.push(i);
                // ans[i] = 1; implicit from intialization
            } else {
                int span = 1;
                while(!stk.empty() && price[stk.top()] <= price[i]){
                    span += ans[stk.top()];// coun the ans of elements you are popping out
                    stk.pop();
                }
                ans[i] = span;
                stk.push(i);
            }
        }
        return ans;
    }
};

// O(n) but verbose
class Solution
{
    public:
    vector <int> calculateSpan(int price[], int n)
    {
       // [WRONG]aim is to store local maxima as we traverse on price[]
       stack<int> lm;
       vector<int> ans;
       for(int i=0; i<n; i++){
           if(lm.empty()) {
               ans.push_back(i+1);
               lm.push(i);
           } else {
               if(price[lm.top()] > price[i]) {
                   ans.push_back(1);
               } else {
                   while(!lm.empty()){
                       if(price[lm.top()] <= price[i])
                       lm.pop();
                       else
                       break;
                   }
                   if(lm.empty())
                   ans.push_back(i+1);
                   else
                   ans.push_back(i - lm.top());
               }
               lm.push(i);
           }
       }
       return ans;
    }
};

//previously implemented in CodingNinjas/TopicWiseAssignmentProblems/stock - O(n^2) and O(n) approach as soln.1 above