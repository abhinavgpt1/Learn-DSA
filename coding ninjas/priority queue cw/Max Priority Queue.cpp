/*
Code : Max Priority Queue
Send Feedback
Implement the class for Max Priority Queue which includes following functions -
1. getSize -
Return the size of priority queue i.e. number of elements present in the priority queue.
2. isEmpty -
Check if priority queue is empty or not. Return true or false accordingly.
3. insert -
Given an element, insert that element in the priority queue at the correct position.
4. getMax -
Return the maximum element present in the priority queue without deleting. Return -Infinity if priority queue is empty.
5. removeMax -
Delete and return the maximum element present in the priority queue. Return -Infinity if priority queue is empty.
Note : main function is given for your reference which we are using internally to test the class.
*/
/***************
 * Following is the main function that er are using internally
 *
 
int main() {
    PriorityQueue pq;
    int choice;
    cin >> choice;
    while(choice != -1) {
        switch(choice) {
            case 1 : // insert
                int element;
                cin >> element;
                pq.insert(element);
                break;
            case 2 : // getMax
                cout << pq.getMax() << endl;
                break;
            case 3 : // removeMax
                cout << pq.removeMax() << endl;
                break;
            case 4 : // size
                cout << pq.getSize() << endl;
                break;
            case 5 : // isEmpty
                if(pq.isEmpty()) {
                    cout << "true" << endl;
                }
                else {
                    cout << "false" << endl;
                }
            default :
                return 0;
        }
        cin >> choice;
    }
}
*******************/
#include<vector>
#include<climits>
class PriorityQueue {
    // Complete this class
    vector<int> pq;
    public:
    int getSize(){
        if(isEmpty())
            return 0;
        return pq.size();
    }
    bool isEmpty(){
        return pq.size()==0;
    }
    int getMax(){
        if(isEmpty())
            return INT_MIN;
        return pq[0];
    }
    void insert(int x){
        pq.push_back(x);
        int childIndex = pq.size()-1;
        while(childIndex>0){
            int parentIndex = (childIndex-1)/2;
            if(pq[parentIndex]<pq[childIndex])
                swap(pq[parentIndex],pq[childIndex]);
            else
                break;
            childIndex = parentIndex;
        }
    }
    int removeMax(){
        if(isEmpty())
            return INT_MIN;
        int ans = pq[0];
        pq[0]=pq[pq.size()-1];
        pq.pop_back();
        //down-heapify
        int parentIndex = 0;
        int leftIndex = 2*parentIndex + 1;
        int rightIndex = 2*parentIndex + 2;
        
        while(leftIndex<pq.size()){
            int maxIndex = parentIndex;
            if(pq[leftIndex] > pq[maxIndex])
                maxIndex = leftIndex;
            if(rightIndex < pq.size() && pq[rightIndex] > pq[maxIndex])
                maxIndex = rightIndex;
            if(maxIndex == parentIndex)
                break;
            swap(pq[parentIndex], pq[maxIndex]);
            
            parentIndex = maxIndex;
            leftIndex = 2*parentIndex + 1;
        	rightIndex = 2*parentIndex + 2;
        }
        return ans;
    }
    
};
