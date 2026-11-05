Aditya Verma - Binary Search:
-----------------------------
ref: https://www.youtube.com/playlist?list=PL_z_8CaSLPWeYfhtuKHj-9MpYb6XQJ_f2

- In any problem where you see the word "sorted", check if Binary Search can be used. Generally a sorted collection is given to use BS only.
- BS on answer is a good variation

- Base/Terminating condition in 
    - recursion BS: start > end
    - iteration BS: start >= end
    - Both approaches hence emphasizes on processing the last element where start = end.

- Calculate mid as start + (end - start) / 2
    - QQ: Why?
    - Ans: To avoid integer overflow. eg. start = 20e9, end = 20e9 => mid = (start+end)/2 = negative value.
    - If not done carefully, then one or two test cases will fail.

- Apply basic BS or variations you know when you're clueless

/**
* Definitions:
* Binary Search: A searching algorithm that finds a target in a sorted array by repeatedly dividing the search space 
* into half, eliminating the half where the target cannot exist.
*/


Q1: Binary search in sorted array (ascending)
Sol: 
Using recursion:
```
int bs(int arr[], int start, int end, int k) {
    if (start > end)
        return -1;
    int mid = start + (end - start) / 2;
    if (arr[mid] == k)
        return mid;
    else if (k < arr[mid])
        return bs(arr, start, mid - 1, k);
    else
        return bs(arr, mid + 1, end, k);
}
```
Using iteration:
```
int bs(int arr[], int k) {
    int start = 0, end = n - 1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == k)
            return mid;
        else if (k < arr[mid])
            end = mid - 1;
        else
            start = mid + 1;
    }
    return -1;
}
```

Q2: Binary search in sorted array (descending)
Sol: 
```
// Just reverse definition of left-right search
int bs(int arr[], int start, int end, int k) {
    if (start > end)
        return -1;
    int mid = start + (end - start) / 2;
    if (arr[mid] == k)
        return mid;
    else if (k < arr[mid])
        return bs(arr, mid + 1, end, k);
    else
        return bs(arr, start, mid - 1, k);
}
```

Q3: Order agnostic binary search (ascending/descending order not known)
Soln: Check arr[0] < arr[n-1] before executing BS. if true, call asc. BS, else call desc. BS. 
Checking arr[0] < arr[1] is not sufficient (as missed by aditya verma).
```
int bs(int arr[], int k) {
    // sort order of arr is not known
    if (arr.length == 1) // not necessary
        return arr[0] == k ? 0 : -1;
    if (arr[0] < arr[arr.length - 1])
        return bsAsc(arr, 0, n - 1, k);
    else
        return bsDesc(arr, 0, n - 1, k);
}
```

Q4: First and last occurrence of an element in a sorted array
Soln: Search k and ensure it's the first occurrence. Keep storing the ans as you find k. Iterative soln. is better here.
PTR: Iterating to the left once you find k might turn time complexity to O(n). eg. all values in 10e6 size array are k.
```
int firstOcc(int arr[], int n, int k) {
    int start = 0, end = n - 1;
    int ans = -1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        // only this if block changes, rest is same
        if (arr[mid] == k) {
            ans = mid;
            end = mid - 1; // IMP.
        } else if (k < arr[mid])
            end = mid - 1;
        else
            start = mid + 1;
    }
    return ans;
}
```
```
int lastOcc(int arr[], int n, int k) {
    int start = 0, end = n - 1;
    int ans = -1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        // only this if block changes, rest is same
        if (arr[mid] == k) {
            ans = mid;
            start = mid + 1; // IMP.
        } else if (k < arr[mid])
            end = mid - 1;
        else
            start = mid + 1;
    }
    return ans;
}
```

Q5: Count of an element in a sorted array.
Soln: 
1. BS since the word sorted is present 
2. Check if firstOcc == -1, return 0. The following formula doesn't work if k is not present in the array.
3. count of k = lastOcc - firstOcc + 1

Q6: Find number of times a sorted array is (right) rotated.
Soln: Number of times the array is rotated = index of the min element. 
The min element is defined as the element which has both neighbours greater than it.
PTR: 
- if array is left rotated, the ans will be n - ans.
- This soln. works only when array has unique elements.


```
// ref: https://www.geeksforgeeks.org/dsa/find-rotation-count-rotated-sorted-array/
static int findKRotation(int[] arr) {
    int low = 0, high = arr.length - 1;

    while (low <= high) {
        
        // If subarray is already sorted, smallest is at low
        if (arr[low] <= arr[high])
            return low ;

        int mid = low + (high-low) / 2 ;

        // Minimum is in the right half
        if (arr[mid] > arr[high])
            low = mid + 1;
        // Minimum is in the left half (could be mid)
        else
            high = mid;
    }

    return low;
}
```

Q7: Find element in rotated sorted array
Soln: Find the min element index, then BS on left and right of this index.

Q8: Find element in nearly sorted array. An array is nearly sorted if an element at index i can be at i-1, i, or i+1.
Soln: Just like traditional BS, check with mid. But now, check if mid-1, mid or mid+1 are equal to k.
Comparing with the middle element is enough as all the elements after mid+2 must be greater than the mid element and all elements before mid-2 must be smaller than the mid element.
```
// ref: https://www.geeksforgeeks.org/dsa/search-almost-sorted-array/
public static int findTarget(int[] arr, int target) {
    int low = 0, high = arr.length - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Check the middle 3 positions
        if (target == arr[mid])
            return mid;

        if (mid - 1 >= low && arr[mid - 1] == target)
            return mid - 1;

        if (mid + 1 <= high && arr[mid + 1] == target)
            return mid + 1;

        // Narrow the search range
        if (target < arr[mid])
            high = mid - 2;
        else
            low = mid + 2;
    }

    // Element not found
    return -1;
}

```

Q9: Find floor of an element in sorted array.
Soln: Floor = greatest element smaller than equal to k. Keep storing the ans for floor. Iterative soln. is better here.
```
int bsFloor(int arr[], int k) {
    int start = 0, end = n - 1;
    int ans = -1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == k)
            return mid;
        else if (k < arr[mid])
            end = mid - 1;
        else {
            ans = mid; // only this change is needed in traditional BS
            start = mid + 1;
        }
    }
    return ans;
}
```

Q10: Find ceil of an element in sorted array.
Soln: Ceil = smallest element greater than equal to k. Keep storing the ans for ceil. Iterative soln. is better here.
```
int bsCeil(int arr[], int k) {
    int start = 0, end = n - 1;
    int ans = -1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == k)
            return mid;
        else if (k > arr[mid])
            start = mid + 1;
        else {
            ans = mid; // only this change is needed in traditional BS
            end = mid - 1;
        }
    }
    return ans;
}
```

Q11: Next alphabetical element in sorted char array.
Soln: Ceil but on finding the element, move to right side.
```
int nextCharIndex(char arr[], char k) {
    int start = 0, end = n - 1;
    int ans = -1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == k)
            start = mid + 1; // only change here w.r.t. ceil code
        else if (k > arr[mid]) 
            start = mid + 1;
        else
        {
            ans = mid;
            end = mid - 1;
        }
    }
    return ans;
}
```

Q12: Find element in infinite sorted array
Soln: We know that the key in BS is bounded between start and end. The first challenge is how to assign the end value. 
Let's keep start = 0 and end = 1. Increase these limits until end >= k. Then binary search within these bounds.
After that, the infinite array aspect doesn't matter anymore.

```
int bsInfinite(int arr[], int k) {
    int start = 0, end = 1;
    // O(log(k))
    while (k > arr[end]) {
        start = end;
        end *= 2;
    }
    // start = 2^(y-1), end = 2^y, where 2^(y-1) <= k <= 2^y. Range of BS (n) = end - start = 2^(y-1)
    // Time complexity = O(logn). Here, n can be safely replaced with k since n = 2^(y-1) <=k
    // So, time complexity = O(logk)
    return bs(arr, start, end, k);
}
```

Q13: Find the index of the first 1 in an infinite binary sorted array. eg. 00000..0111111...
Soln: A combination of infinite sorted array & first occurrence problems.

Q14: (IMP) Minimum difference element in a sorted array. Find the element whose absolute difference with k is minimum.
Soln: Apply BS. If key is not found, low and high end up as neighbours of where the key would be. Compare both to find the closer one.
Rule: if the key is not found, then high and low are the neighbours of the key. This always happens; that's how the algo works.

Sol1:
```
int findMinDiffElement(int arr[], int n, int k) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if(arr[mid] == k)
            return arr[mid];
        else if (k < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    
    // Boundary checks
    if (high < 0)
        return arr[low];

    if (low >= n)
        return arr[high];

    if (abs(arr[low] - k) < abs(arr[high] - k))
        return arr[low];
    else
        return arr[high];
}
```

Sol2:
```
int findMinDiffElement(int arr[], int n, int k) {
    int floorIndex = bsFloor(arr, k);
    if (floorIndex == -1)
        return arr[floorIndex + 1];
    if (floorIndex == n - 1)
        return arr[floorIndex];
    
    if (abs(arr[floorIndex] - k) < abs(arr[floorIndex + 1] - k))
        return arr[floorIndex];
    else
        return arr[floorIndex + 1];
}
```

Q15: (concept) Binary search on answer
Soln: Sorted -> BS. Unsorted -> BS on answer. Just like in BS, we had a criterion to reject one half, same happens here too. So, 1) we need to check if mid element is ans or not. 2) if not on what criteria should we move left / right.
eg. Peak element problem (Q16)

Q16: Peak Element. Given an unsorted array, find any peak element. An element is peak if it is greater than its neighbours. Neighbours of end elements are only the elements next to them. So, if an end element is greater than the element next to it, then it is a peak element. Return any peak element index.
Soln: Understand intuition how BS works here. 1) is mid peak element or not 2) left or right 3) ans
1) mid element is peak element if it is greater than mid - 1 (if available) and mid + 1 (if available) elements.
2) find the promising side eg. 5 10 20 15. For mid = 10, peak element can't be 5. 20 looks more promising. We're not saying that you won't find a peak element in the left half; there can be multiple peak elements.

```
int peakElementIndex(int arr[]) {
    int low = 0, high = arr.length - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (mid > 0 && mid < arr.length - 1) {
            if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1])
                return mid;
            else if (arr[mid - 1] > arr[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        else if (mid == 0) {
            if (arr[0] > arr[1])
                return 0;
            else
                return 1; // IMP. to realise
        }
        else if (mid == arr.length - 1) {
            if (arr[arr.length - 1] > arr[arr.length - 2])
                return arr.length - 1;
            else
                return arr.length - 2; // IMP. to realise
        }
    }
    return -1;
}
```

Q17: Find max. element in bitonic array. Bitonic array is an array which is monotonically increasing and then monotonically decreasing. A monotonic array is increasing where arr[i] != arr[i+1]. If arr[i] == arr[i+1] for any i, then it is just an increasing array, not monotonically increasing. FYI, a bitonic array != a rotated sorted array.
Soln: It is the same as peak element problem i.e. find an element which is greater than its neighbors. Here the max element would be exactly one, unlike peak elements.

Q18: Search element in bitonic array
Soln: Find max element, and then do BS in left and right parts. Beware the right side would be sorted in decreasing order, so the conditions for left-right traversal would flip.

Q19: Search in row-wise and column-wise sorted array
Soln: O(m+n) time approach where you start at the top-right corner element (mid) and traverse down if element (k) is greater than mid. Traverse left if element (k) is less than mid. If element (k) is equal to mid, you have found the element.
```
int search(int matrix[][], int n, int m, int k) {
    int i = 0, j = m - 1;
    while (i < n && j >= 0) {
        if (matrix[i][j] == k)
            return 1;
        else if (matrix[i][j] < k)
            i++;
        else
            j--;
    }
    return -1;
}
```

Q20: (IMP.) Allocate minimum number of pages. Given an (unsorted) array of numbers (arr) where each element represents a number of pages in a book. You have to allocate books to k students such that the maximum number of pages allocated to a student is minimum. At least one book should be allocated to every student. Allocation of books should be in contiguous order. Partial book allocation is not allowed. Return this minimum number.
Soln: Say you have to allocate [10,20,40,30] books to 2 people only. The min book pages you can allocate = 0, max = sum(booksArr). Since we have to minimize the max pages allocated to a student, we can assign the max(booksArr) book to a student and then check if the remaining books can be allocated to the remaining students. So our range of search is from max(booksArr) to sum(booksArr). 
Now, we can do BS on this range. If we can allocate books to k students with mid as the max pages allocated to a student, then we can try to minimize it further by moving left. If we can't, we have to move right.
```
boolean isValid(int[] arr, int k, long maxPages) {
    long sum = 0;
    int students = 1;
    for(int i=0; i<arr.length; i++) {
        sum += arr[i];
        if(sum > maxPages) {
            students++;
            sum = arr[i];
        }
        if(students > k)
            return false;
    }
    return true;
}

int allocateBooks(int arr[], int n, int k) {
    if(k > arr.length)
        return -1;

    long low = Arrays.stream(arr).max().getAsLong();
    long high = Arrays.stream(arr).mapToLong(i-> (long)i).sum();
    // Arrays.stream(arr).sum(); // integer overflow
    long ans = -1;
    while(low <= high) {
        long mid = low + (high - low) / 2;
        if(isValid(arr, k, mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return (int) ans;
}
```
This type of question is classical BS hard problem in which main task is to write the isValid function.

Extras:
QQ1: Search in a normal sorted 2D array can be treated as a 1D array BS with low = 0, high = n*m - 1, mid = low + (high-low)/2. Mid element = arr[mid/col][mid%col]

```
int search(int matrix[][], int n, int m, int k) {
    int low = 0, high = n * m - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int midElement = matrix[mid / m][mid % m];
        if (midElement == k)
            return mid;
        else if (midElement < k)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}
```