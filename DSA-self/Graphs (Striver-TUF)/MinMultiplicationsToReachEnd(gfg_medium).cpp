/*
 * Minimum Multiplications to reach End
 * ------------------------------------
 * Given start, end and an array arr of n numbers. 
 * At each step, start is multiplied with any number in the array and then mod operation with 100000 is done to get the new start.
 * 
 * Your task is to find the minimum steps in which end can be achieved starting from start. 
 * If it is not possible to reach end, then return -1.
*/

// Time complexity is mod*size(arr), but it is highly unprobable as all values will not be visited

class Solution{
    public:
    int minimumMultiplications(vector<int>& arr, int start, int end) {
        // Max. size of queue = end
        // Approach is to find minimum no. of steps to reach a value
        const int mod = 1e5;
        vector<int> stepsToReachValue(mod + 1, INT_MAX); // end can be reached after exceeding mod and multiplications thereafter
        
        set<pair<int, int>> pending; //steps, value
        stepsToReachValue[start] = 0;
        pending.insert({stepsToReachValue[start], start});
        while(!pending.empty()){ //O(mod)
            auto it = pending.begin();
            pending.erase(it); //O(log(mod))
            
            int steps = it->first;
            int value = it->second;
            
            if(value == end){
                return steps;
            }
            
            for(int i: arr){ //O(n=1e4)
                //value*i<=1e9 < INT_MAX otherwise we would require long int
                int newValue = (value*i)%mod;
                // if(newValue > end) // WRONG to include this check: newValue may be greater than end but less than mod
                //     continue;
                int newSteps = steps+1;
                if(stepsToReachValue[newValue] > newSteps){
                    if(stepsToReachValue[newValue] != INT_MAX){
                        pending.erase({stepsToReachValue[newValue], newValue});
                    }
                    stepsToReachValue[newValue] = newSteps;
                    pending.insert({newSteps, newValue});
                }
                
            }
        }
        
        return -1;
    }
};