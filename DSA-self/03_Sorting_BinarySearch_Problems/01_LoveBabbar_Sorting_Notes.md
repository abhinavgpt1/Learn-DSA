Love Babbar - Sorting
---------------------
ref: https://www.youtube.com/playlist?list=PLDzeHZWIZsTp4pb_WBRahP1tnipLuX9qM

Definition: Sorting algorithm: An algorithm that puts elements of a given dataset in a specific order.
Definition: Stable and Unstable algorithm: A stable sorting algorithm maintains the relative order of identical elements (elements with equal keys) after sorting, whereas an unstable sorting algorithm does not guarantee that this original order will be preserved.
Definition: In-place sorting: An in-place sorting algorithm is a sorting method that rearranges the elements within the original data structure itself, requiring a minimal, constant amount of extra memory (usually O(1) auxiliary space complexity).

1. Selection Sort
- Definition: The selection sort algorithm sorts an array by repeatedly finding the minimum element (considering ascending order) from the unsorted part and putting it at the beginning.
```
void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
void selectionSort(int arr[], int n) {
    for(int i=0; i<n-1; i++) {
        int min_idx = i;
        for(int j=i+1; j<n; j++) {
            if(arr[j] < arr[min_idx])
                min_idx = j;
        }

        if(min_idx != i) { // slight optimisation to avoid unnecessary swaps
            swap(arr, i, min_idx);
        }
    }
}
```
- Space Complexity: O(1)
- Time Complexity:
    - Best Case: O(n^2)
        - Even if the array is sorted, finding the min element takes O(n) time.
    - Average Case: O(n^2)
    - Worst Case: O(n^2)
- Stability: Unstable
    - eg. [4A,5,4B,1] -> round 1 swaps 1 and 4A, thus moving 4A after 4B.
- In-place: Yes

Use case: For small arrays

2. Bubble Sort
- Definition: The bubble sort algorithm sorts an array by repeatedly swapping the adjacent elements if they are in the wrong order.
```
void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
void bubbleSort(int arr[], int n) {
    for(int i=1; i<n; i++) {
        // for round 1 to n-1

        boolean swapped = false;
        for(int j=0; j<n-i; j++) {
            if(arr[j] > arr[j+1]) {
                swap(arr, j, j+1);
                swapped = true;
            }
        }

        if(!swapped)
            break;
    }
}
```
- Space Complexity: O(1)
- Time Complexity:
    - Best Case: O(n)
        - Exit the loop if no swaps are done.
    - Average Case: O(n^2)
    - Worst Case: O(n^2)
- Stability: Stable
- In-place: Yes

3. Insertion Sort
- Definition: The insertion sort algorithm sorts an array by repeatedly inserting an element from the unsorted part into its correct position in the sorted part.
FYI, you shift the elements in this algorithm, not swap.
```
void insertionSort(int arr[], int n) {
    for(int i=1; i<n; i++) {
        int key = arr[i];
        int j = i-1;
        while(j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        
        // can optimise this assignment by checking if j != i - 1
        arr[j+1] = key;
    }
}
```
- Space Complexity: O(1)
- Time Complexity:
    - Best Case: O(n)
        - Exit the loop if arr[i-1] <= arr[i], i.e. no swap at the first iteration of round i
    - Average Case: O(n^2)
    - Worst Case: O(n^2)
- Stability: Stable
- In-place: Yes
Use case: For small arrays, partially sorted arrays

4. Merge Sort
- Definition: The merge sort algorithm sorts an array by repeatedly dividing the array into halves, sorting each half, and merging them back together following the divide-and-conquer programming paradigm.
```
// Solution is not exactly the same as in the video
void merge(int arr[], int start, int mid, int end) {
    int i = start, j = mid + 1;
    int[] temp = new int[end-start+1];
    int k = 0;
    
    while(i <= mid && j <= end) {
        if(arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    
    while(i <= mid)
        temp[k++] = arr[i++];
    
    while(j <= end)
        temp[k++] = arr[j++];
    
    for(i=start; i<=end; i++)
        arr[i] = temp[i-start];
}
void mergeSort(int arr[], int start, int end) {
    if(start >= end)
        return;
    int mid = start + (end-start)/2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid+1, end);
    merge(arr, start, mid, end);
}
void mergeSort(int[] arr) {
    mergeSort(arr, 0, arr.length - 1);
}
```
- Space Complexity: O(n)
- Time Complexity:
    - Best Case: O(n log n)
        - You can't skip the merge which takes O(n) every time
    - Average Case: O(n log n)
    - Worst Case: O(n log n)
- Stability: Stable
- In-place: No
Use case: 
- For large arrays
- Sorting linked lists is efficient since there's no need to create a new array
- Inversion Count problem

5. Quick Sort
- Definition: The quick sort algorithm sorts an array by repeatedly partitioning the array into two sub-arrays based on an element called pivot and sorts them recursively following the divide-and-conquer programming paradigm.

Algo:
- Pick the first element of array as pivot
- Partition creation process: put the pivot at its correct position, move the smaller elements to the left, and the greater or equal elements to the right.
- Repeat the process for left and right sub-arrays

```
void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
int partition(int arr[], int start, int end) {
    int pivot = arr[start];
    int cnt = 0;
    for(int i=start+1; i<=end; i++) {
        if(arr[i] < pivot)
            cnt++;
    }
    
    int pivotIndex = start + cnt;
    swap(arr, start, pivotIndex);

    // rearrange elements around pivot. Intention is not to sort them, but to group them.
    int i = start, j = end;
    while(i < pivotIndex && j > pivotIndex) {
        if(arr[i] < pivot)
            i++;
        else if(arr[j] >= pivot)
            j--;
        else {
            swap(arr, i, j);
            i++;
            j--;
        }
    }
    return pivotIndex;
}
void quickSort(int arr[], int start, int end) {
    if (start >= end)
        return;
    int pivot = partition(arr, start, end);
    quickSort(arr, start, pivot-1);
    quickSort(arr, pivot+1, end);
}
void quickSort(int[] arr) {
    quickSort(arr, 0, arr.length - 1);
}
```
- Space Complexity: O(log n)
    - Worst case: O(n)
        - Reason: if the array is sorted, the stack space will be O(n)
- Time Complexity:
    - Best Case: O(n log n)
        - Reason: even if the array is sorted, you will calculate cnt in O(n)
    - Average Case: O(n log n)
    - Worst Case: O(n^2)
        - Reason: if the array is sorted in decreasing order, cnt finding takes O(n), and every iteration results in an (n-i, 0) partition, leading to (n-1), (n-2), ..., 1 operations each with cnt finding(O(n)) => O(n^2).
- Stability: Unstable
    - Even with the optimised partition logic. eg. [3A, 2, 3B, 1]. cnt = 0 => 1 goes to its correct place, and swaps with 3A.
- In-place: No
Use case: 
- For large arrays
- Sorting arrays is more efficient than linked lists since there's an overhead to traverse the LL to find the pivot and rearrange elements. Merge sort loses for arrays due to O(N) space complexity.

Optimised partition logic:
- Consider the last element as pivot
- Take a pointer (smallElementPointer) at which the smaller elements are to be placed
- Traverse the array from start to end-1
    - If current element is smaller than pivot, swap it with the element at smallElementPointer and increment smallElementPointer
- Swap the pivot with the element at smallElementPointer
```
int partition(int[] arr, int start, int end) {
    int pivot = arr[end];
    int smallElementPointer = start;
    for(int i=start; i<end; i++) {
        if(arr[i] < pivot) {
            swap(arr, i, smallElementPointer);
            smallElementPointer++;
        }
    }
    swap(arr, end, smallElementPointer);
    return smallElementPointer;
}
```
This doesn't change the best and worst time complexity, because the partition() process is still O(n) in every case.