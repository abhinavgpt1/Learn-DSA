/*
Merge K sorted arrays
Send Feedback
Given k different arrays, which are sorted individually (in ascending order). You need to merge all the given arrays such that output array should be sorted (in ascending order).
Hint : Use Heaps.
Input Format :
Line 1 : Integer K
Line 2 : Arrays 1 size (n1)
Line 3 : Array 1 elements (separated by space)
Line 4 : Array 2 size (n2)
and so on for next arrays
Sample Input 1 :
4
3
1 5 9
2
45 90
5
2 6 78 100 234
1
0
Sample Output 1 :
0 1 2 5 6 9 45 78 90 100 234
*/
#include<queue>
class Tuple{
    public:
    int value;
    int index;
    int arrNo;
    bool operator() (Tuple a, Tuple b){//help create min Heap
        return a.value > b.value;
    }
};
vector<int> mergeKSortedArrays(vector<vector<int>*> input){
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Return the output.
     * Taking input and printing output is handled automatically.
     */
    int k = input.size();
    int totalElements = 0;
    for(int i = 0; i < k; i++){
        totalElements += input[i]->size();
    }
	vector<int> ans;
    priority_queue<Tuple, vector<Tuple>, Tuple> pq;
    for(int i = 0; i < k; i++){
        Tuple temp;
        temp.value = (*input[i])[0];
        temp.index = 0;
        temp.arrNo = i;
        
        pq.push(temp);
    }
    int currElementCount = totalElements;
    while(currElementCount--){
        Tuple temp = pq.top();
        pq.pop();
        // if(temp.value == 0)
        //     cout<<endl<<temp.arrNo<<endl;
        ans.push_back(temp.value);
        if(temp.index < input[temp.arrNo]->size() - 1){
            temp.index++;
            temp.value = (*input[temp.arrNo])[temp.index];
            pq.push(temp);
        }
        
    }
    
    return ans;
}
/*
//easier solution but high memory consumption
#include<queue>
vector<int> mergeKSortedArrays(vector<vector<int>*> input){
    priority_queue<int, vector<int>, greater<int>>  pq;
    for(int i=0;i<input.size();i++){
        int size = input[i]->size();
        for(int j=0;j<size;j++)
            pq.push((*input[i])[j]);
    }
    
    vector<int> ans;
    while(!pq.empty()){
        ans.push_back(pq.top());
        pq.pop();
    }
    return ans;
}
*/

//retried
class Tuple{
	public: 
    int val, listNo, index;
    Tuple(int v, int l, int i){
        val = v; listNo = l; index = i;
    }
};
class Comp{
    public:
	bool operator()(Tuple a, Tuple b){
	    if(a.val > b.val)
	    	return true;
	    else if(a.val == b.val)
	        return a.listNo < b.listNo;
	    else
	    	return false;
	        
	}
};
#include<queue>
vector<int> mergeKSortedArrays(vector<vector<int>*> input) {
    // Write your code here
    int n = input.size();
    vector<int> ans;
    priority_queue<Tuple, vector<Tuple>, Comp> pq;
    for(int i=0; i<n; i++)
        pq.push(Tuple((*input[i])[0], i, 0));
    while(!pq.empty()){
        Tuple topTuple = pq.top();
        pq.pop();
        if(topTuple.index < input[topTuple.listNo]->size() - 1)
            pq.push(Tuple((*input[topTuple.listNo])[topTuple.index + 1], topTuple.listNo, topTuple.index + 1));
        ans.push_back(topTuple.val);
    }
    return ans;
}