/**
 * Given an array arr containing N integers and a positive integer K, 
 * find the length of the longest sub array with sum of the elements divisible by the given value K.
 * 
 */
class Solution{
public:	
	int longSubarrWthSumDivByK(int arr[], int n, int k) {
	    // similar to finding longest subarray with sum S
	    // here we should store the remainder of K and which occur as early as possible
	    unordered_map<int, int> remainderAtIndex;
	    int sum = 0;
	    int ans = 0;
	    remainderAtIndex[0] = 0;
	    for(int i=0; i<n; i++){
	        sum += arr[i];
	        if(sum % k == 0)
	            ans = i + 1;
	        else {
	            int cpy = sum;
                while(cpy < 0){
                    // to make -ve sum positive and to store positive remainder
                    cpy += k;
                }
                // math's % != computer's % over negative numbers
                // -1%9 = 8 in maths and -1 in comp
                    
	            if(remainderAtIndex.count(cpy%k))
	                ans = max(ans, i - remainderAtIndex[cpy%k]);
	            else 
	                remainderAtIndex[cpy%k] = i;
	        }
	    }
	    return ans;
	}
};