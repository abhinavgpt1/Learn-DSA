/**
 * Fractional Knapsack
 * -------------------
 * Given weights and values of n items, we need to put these items in a knapsack of capacity w to get the maximum total value in the knapsack.
 * Return a double value representing the maximum value in knapsack.
 * Note: Unlike 0/1 knapsack, you are allowed to break the item here. 
 * The details of structure/class is defined in the comments above the given function.
 * 
 * Expected Time Complexity : O(n log n)
 * Expected Auxilliary Space: O(1)
 * 
 * Constraints:
 * 1 <= n <= 10^5
 * 1 <= w <= 10^9
 * 1 <= valuei, weighti <= 10^4
*/

// link: https://www.geeksforgeeks.org/problems/fractional-knapsack-1587115620/1
// article: https://www.geeksforgeeks.org/fractional-knapsack-problem/

// Solution: Greedy: O(nlogn), O(n) [needed during the merge sort]
bool valPerWeight(Item a, Item b){
    return 1.0*a.value/a.weight > 1.0*b.value/b.weight;
}

class Solution {
  public:
    double fractionalKnapsack(int w, Item arr[], int n) {
        sort(arr, arr+n, valPerWeight);
        double ans = 0;
        int i = 0;
        while(i < n && w != 0){
            if(arr[i].weight <= w){
                ans += arr[i].value;
                w -= arr[i].weight;    
            }
            else{
                ans += 1.0*arr[i].value * w / arr[i].weight;
                w = 0;
            }
            
            i++;
        }
        return ans;
    }
};