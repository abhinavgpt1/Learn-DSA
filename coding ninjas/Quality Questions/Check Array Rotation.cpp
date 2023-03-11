/*
Check Array Rotation
Send Feedback
Given an integer array, which is sorted (in increasing order) and has been rotated by some number k in clockwise direction. Find and return the k.
Input format :
Line 1 : Integer n (Array Size)
Line 2 : Array elements (separated by space)
Output Format :
Integer k
Constraints :
0 <= n <= 10^7
Sample Input 1:
6
5 6 1 2 3 4
Sample Output 1:
2
Sample Input 2:
5
3 6 8 9 10
Sample Output 2:
0
*/
int FindSortedArrayRotation(int arr[], int n) {
	for(int i=0;i<n-1;i++)
        if(arr[i]>arr[i+1])
            return i+1;
}
*/
int FindSortedArrayRotation(int arr[], int n) {
    int left=0;int right=n-1;
    while(left<right){
    int mid=(right+left)/2;
        if(arr[mid]>arr[right])
        	left=mid+1;
        else
            right=mid;
    }
    return left;
}