/*
Check Max-Heap
Send Feedback
Given an array of integers, check whether it represents max-heap or not.
Return true or false.
Input Format :
Line 1 : An integer N i.e. size of the array
Line 2 : N integers which are elements of the array, separated by spaces
Output Format :
true if it represents max-heap and false if it is not a max-heap
Constraints :
1 <= N <= 10^5
1 <= Ai <= 10^5
*/
bool isMaxHeap(int arr[], int n) {
    // Write your code here
    for(int i=0; i<n; i++){
        int parentIndex = i;
        int childIndex1 = 2*parentIndex + 1;
        int childIndex2 = 2*parentIndex + 2;
        if((childIndex1 < n && arr[childIndex1] > arr[parentIndex]) || (childIndex2 < n && arr[childIndex2] > arr[parentIndex]))
            return false;
    }
    return true;
}

//to avoid checking at last level
bool isMaxHeap(int arr[], int n) {
    // Write your code here
    for(int i=0; i<n; i++){
        int parentIndex = i;
        int childIndex1 = 2*parentIndex + 1;
        int childIndex2 = 2*parentIndex + 2;
        if(childIndex1 >= n && childIndex2 >=n)
            continue;
        if((childIndex1 < n && arr[childIndex1] > arr[parentIndex]) || (childIndex2 < n && arr[childIndex2] > arr[parentIndex]))
            return false;
    }
    return true;
}

//will fail at childIndex < n but childIndex2 = n, 

// also breaking will not promise all leaf nodes satisfy heap property - not necessary if heap will always be provided
    //     10
    //    6  8
    //   2 3 5 4
    //  1       2
bool checkMaxHeap(int input[], int n){
    for(int i = 0; i < n; i++){
        int parentIndex = i;
        int childIndex1 = 2 * parentIndex + 1;
        int childIndex2 = 2 * parentIndex + 2;
        if(childIndex1 >= n)
            break;
        if(input[parentIndex] < input[childIndex1] || input[parentIndex] < input[childIndex2])
            return false;
    }
    return true;
}
/*//method 2
bool checkMaxHeap(int arr[], int n){
    
    
    for(int i=0;i<n;i++){
        int parentIndex = i;
        int childL = 2*parentIndex + 1;
        int childR = 2*parentIndex + 2;
        
        if(childL < n){
            if(arr[childL] > arr[parentIndex])
                return false;
            if(childR < n){
                if(arr[childR] > arr[parentIndex])
                return false;
            }
        }
    }
    return true;
}

*/