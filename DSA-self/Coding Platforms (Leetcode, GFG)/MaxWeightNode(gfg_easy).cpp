/**
 * Maximum Weight Node
 * -------------------
 * Given a maze with N cells. 
 * Each cell may have multiple entry points but not more than one exit (i.e entry/exit points are unidirectional doors like valves).
 * You are given an array Edge[] of N integers, where Edge[i] contains the cell index that can be reached from cell i in one step. 
 * Edge[i] is -1 if the ith cell doesn't have an exit. 
 * The task is to find the cell with maximum weight (The weight of a cell is the sum of cell indexes of all cells pointing to that cell). 
 * If there are multiple cells with the maximum weight return the cell with highest index.
 * Note: The cells are indexed with an integer value from 0 to N-1. 
 * If there is no cell pointing to the ith cell then the weight of the i'th cell is zero.
 * 
 */

class Solution
{
  public:
  int maxWeightCell(int N, vector<int> Edge)
  {
      // be aware of not using set, map when complexity is reqd. as O(N)
      // even unordered_map failed here, so use const array
      const int MAX_SIZE = 1e5 + 1;
      int arr[MAX_SIZE];
      memset(arr, 0, sizeof(arr));
      int maxV = 0, ans = -1;
      for(int i=0; i<N; i++){
          if(Edge[i] != -1){
              arr[Edge[i]] += i;
              if(arr[Edge[i]] > maxV){
                  maxV = arr[Edge[i]];
                  ans = Edge[i];
              } else if(arr[Edge[i]] == maxV) {
                  ans = max(ans, Edge[i]);
              }
          }
      }
      return ans == -1 ? 0 : ans;
  }
};