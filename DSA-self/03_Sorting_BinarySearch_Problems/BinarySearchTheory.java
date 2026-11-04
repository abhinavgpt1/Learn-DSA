import java.util.Arrays;
import java.util.Collections;

class BinarySearch {
    // SonarQube rule java:S1118 flags a class with only static memebers
    // and asks you to explicitly add a private constructor to prevent instantiation since new BinarySearch() makes no semantic sense.
    private BinarySearch() {
        /* This utility class should not be instantiated */
    }

    private static int binarySearchHelper(int arr[], int start, int end, int k) {
        if (end > start)
            return -1;
        int mid = start + (end - start) / 2;
        if (arr[mid] == k)
            return mid;
        else if (k < arr[mid])
            return binarySearchHelper(arr, start, mid - 1, k);
        else
            return binarySearchHelper(arr, mid + 1, end, k);
    }

    public static int binarySearch(int[] arr, int k) {
        System.out.println(arr.length);
        return binarySearchHelper(arr, 0, arr.length - 1, k);
    }
}

class LowerBound {
    // SonarQube rule java:S1118 flags a class with only static memebers
    // and asks you to explicitly add a private constructor to prevent instantiation since new LowerBound() makes no semantic sense.
    private LowerBound() {
        /* This utility class should not be instantiated */
    }

    private static int lowerBoundHelper(int[] arr, int start, int end, int k) {
        if (start > end) {
            if (start >= arr.length)
                return -1; // NA
            return arr[start];
        }
        int mid = start + (end - start) / 2;
        if (arr[mid] == k) {
            return k;
        } else if (k < arr[mid]) {
            return lowerBoundHelper(arr, start, mid - 1, k);
        } else {
            return lowerBoundHelper(arr, mid + 1, end, k);
        }
    }

    public static int lowerBound(int[] arr, int k) {
        System.out.print("Lower bound value for " + k + " : ");
        return lowerBoundHelper(arr, 0, arr.length - 1, k);
    }
}

class UpperBound {
    // SonarQube rule java:S1118 flags a class with only static memebers
    // and asks you to explicitly add a private constructor to prevent instantiation since new UpperBound() makes no semantic sense.
    private UpperBound() {
        /* This utility class should not be instantiated */
    }

    private static int upperBoundHelper(int[] arr, int start, int end, int k) {
        if (start > end) {
            if (start >= arr.length)
                return -1; // NA
            return arr[start];
        }
        int mid = start + (end - start) / 2;
        if (k < arr[mid]) {
            return upperBoundHelper(arr, start, mid - 1, k);
        } else {
            return upperBoundHelper(arr, mid + 1, end, k);
        }
    }

    public static int upperBound(int[] arr, int k) {
        System.out.print("Upper bound value for " + k + " : ");
        return upperBoundHelper(arr, 0, arr.length - 1, k);
    }
}

public class BinarySearchTheory {
    public static void main(String[] args) {
        int[] arr = { 1, 6, 9, 18, 50 };
        System.out.println("Given array: " + Arrays.toString(arr));
        System.out.println("------------------------------");
        /* Binary Search : Arrays.binarySearch() / Collections.binarySearch() */
        // IMP PTR: If key not found, it returns -(start +1).
        //  - start is the index where the key can be inserted to maintain sorted order.
        //  - This logic is VERY useful to find lower bound and upper bound.
        // IMP PTR: above methods return start E [0, N], so make sure to check for (start==N ? -1 : arr[start])
        Arrays.binarySearch(arr, 18);
        Collections.binarySearch(Arrays.stream(arr).boxed().toList(), 18);

        /* Lower Bound */
        System.out.println(LowerBound.lowerBound(arr, 0));
        System.out.println(LowerBound.lowerBound(arr, 1));
        System.out.println(LowerBound.lowerBound(arr, 5));
        System.out.println(LowerBound.lowerBound(arr, 10));
        System.out.println(LowerBound.lowerBound(arr, 400));

        // shortcut for lower bound
        int lowerBoundIndex = Collections.binarySearch(Arrays.stream(arr).boxed().toList(), 19);
        if (lowerBoundIndex < 0) {
            int start = -lowerBoundIndex - 1; // Since lowerBoundIndex = -(start +1) if key not found
            lowerBoundIndex = start;
        }
        System.out.println("Lower bound value for 19 using Collections.binarySearch: " + (lowerBoundIndex < arr.length ? arr[lowerBoundIndex] : -1));
        // PTR: start E [0, N], so make sure to check for (start==N ? -1 : arr[start])

        System.out.println();

        /* Upper Bound */
        System.out.println(UpperBound.upperBound(arr, 0));
        System.out.println(UpperBound.upperBound(arr, 1));
        System.out.println(UpperBound.upperBound(arr, 5));
        System.out.println(UpperBound.upperBound(arr, 9));
        System.out.println(UpperBound.upperBound(arr, 10));
        System.out.println(UpperBound.upperBound(arr, 25));
        System.out.println(UpperBound.upperBound(arr, 400));

        // shortcut for upper bound : find lower bound and iterate till the next value is same.
        int upperBoundIndex = Collections.binarySearch(Arrays.stream(arr).boxed().toList(), 19);
        if (upperBoundIndex < 0) {
            int start = -upperBoundIndex - 1; // Since upperBoundIndex = -(start +1) if key not found
            upperBoundIndex = start;
        }
        
        // PTR: start / upperBoundIndex(after equality check) E [0, N], so make sure to check for (start==N ? -1 : arr[start])
        while (upperBoundIndex < arr.length && arr[upperBoundIndex] <= 19) {
            upperBoundIndex++;
        }
        System.out.println("Upper bound value for 19 using Collections.binarySearch: " + (upperBoundIndex < arr.length ? arr[upperBoundIndex] : -1));

        // Binary search either finds the value or can be leveraged to find the element just smaller or greater than the key
        // case 1: if we go left to the element where start == end, then arr[start] is the element just greater than key
        // case 2: if we go right to the element where start == end, then arr[start] is the element just smaller than key
        // In both cases, start = the position where key can be inserted to keep array sorted -> push everything to right in case 1, and insert at start=mid+1 in case 2

        // sample problem: 
        // https://www.geeksforgeeks.org/problems/floor-in-a-sorted-array-1587115620/1
        // https://leetcode.com/problems/search-insert-position/description/
        // https://www.geeksforgeeks.org/problems/search-insert-position-of-k-in-a-sorted-array/1

        // Result from binary search problems: find what to return - low, high, mid or a custom value after some if-else. Max. problems should get solved.
    }
}

/**
 * Output:
 * -------
 * Given array: [1, 6, 9, 18, 50]
 * ------------------------------
 * Lower bound value for 0 : 1
 * Lower bound value for 1 : 1
 * Lower bound value for 5 : 6
 * Lower bound value for 10 : 18
 * Lower bound value for 400 : -1
 * Lower bound value for 19 using Collections.binarySearch: 50
 * 
 * Upper bound value for 0 : 1
 * Upper bound value for 1 : 6
 * Upper bound value for 5 : 6
 * Upper bound value for 9 : 18
 * Upper bound value for 10 : 18
 * Upper bound value for 25 : 50
 * Upper bound value for 400 : -1
 * Upper bound value for 19 using Collections.binarySearch: 50
 */