/*
Number of occurrence of x in sorted array
Given a sorted array Arr of size N and a number X, you need to find the number of occurrences of X in Arr.
*/
// C++ program to count occurrences of an element 

//NOT binary_search(arr,arr+n,x): return bool

//bsearch(key,arr,arrSize,sizeof(element of array), comparator): return void ptr to that location
//method 2
//this is as it is
int compare(const void* ap, const void* bp) 
{ 
    // Typecasting 
    const int* a = (int*)ap; 
    const int* b = (int*)bp; 
  
    if (*a < *b) 
        return -1; 
    else if (*a > *b) 
        return 1; 
    else
        return 0; 
} 
//this is as it is too
int *ptr = (int*) std::bsearch(&x,arr,n,sizeof(arr[0]),compare);
// int* p1 = (int*)std::bsearch(&key1, arr, ARR_SIZE, sizeof(arr[0]), compare);
if(!ptr)
	return 0;
int index = ptr-arr;


#include <bits/stdc++.h> 
using namespace std; 

// A recursive binary search function. It returns 
// location of x in given array arr[l..r] is present, 
// otherwise -1 
int binarySearch(int arr[], int l, int r, int x) 
{ 
	if (r < l) 
		return -1; 

	int mid = l + (r - l) / 2; 

	// If the element is present at the middle 
	// itself 
	if (arr[mid] == x) 
		return mid; 

	// If element is smaller than mid, then 
	// it can only be present in left subarray 
	if (arr[mid] > x) 
		return binarySearch(arr, l, mid - 1, x); 

	// Else the element can only be present 
	// in right subarray 
	return binarySearch(arr, mid + 1, r, x); 
} 

// Returns number of times x occurs in arr[0..n-1] 
int countOccurrences(int arr[], int n, int x) 
{ 
	int ind = binarySearch(arr, 0, n - 1, x); 

	// If element is not present 
	if (ind == -1) 
		return 0; 

	// Count elements on left side. 
	int count = 1; 
	int left = ind - 1; 
	while (left >= 0 && arr[left] == x) 
		count++, left--; 

	// Count elements on right side. 
	int right = ind + 1; 
	while (right < n && arr[right] == x) 
		count++, right++; 

	return count; 
} 

// Driver code 
int main() 
{ 
	int arr[] = { 1, 2, 2, 2, 2, 3, 4, 7, 8, 8 }; 
	int n = sizeof(arr) / sizeof(arr[0]); 
	int x = 2; 
	cout << countOccurrences(arr, n, x); 
	return 0; 
}
