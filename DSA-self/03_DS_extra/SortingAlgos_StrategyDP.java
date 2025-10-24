// source: HW12_SortStringArr_StrategyDP.java in CoreJava Repository
import java.util.Arrays;

interface SortingAlgo {
	public void sort(String arr[]);
}

class BubbleSort implements SortingAlgo {
	@Override
	public void sort(String arr[]) {
		int n = arr.length;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n - i - 1; j++) {
				if (arr[j].compareTo(arr[j + 1]) > 0) {
					String temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}
	}
}

class QuickSort implements SortingAlgo {
	@Override
	public void sort(String arr[]) {
		quickSort(arr, 0, arr.length - 1);
	}

	private void quickSort(final String arr[], final int startIndex, final int endIndex) {
		if (startIndex >= endIndex)
			return;
		int pivotIndex = partition(arr, startIndex, endIndex);
		quickSort(arr, startIndex, pivotIndex - 1);
		quickSort(arr, pivotIndex + 1, endIndex);
	}

	/*
	 * This function focuses on finding the pivot index first.
	 * Only then it focuses on rearranging the elements. Hence a 2 step process.
	 * It's less efficient since loop from startIndex to endIndex is done twice.
	 */
	private int partition_less_efficient(final String arr[], final int startIndex, final int endIndex) {
		int pivotIndex = startIndex;
		for (int i = startIndex + 1; i <= endIndex; i++) {
			// no. of elements smaller than arr[startIndex] are counted
			if (arr[i].compareTo(arr[startIndex]) < 0) // place pivotIndex element first among duplicates
				pivotIndex++;
		}
		// place arr[startIndex] at its correct position
		String temp = arr[pivotIndex];
		arr[pivotIndex] = arr[startIndex];
		arr[startIndex] = temp;

		// move all smaller elements to left of pivotIndex and all greater elements to
		// right of pivotIndex
		// intention is not to sort them, but to group them
		int i = startIndex, j = endIndex;
		while (i < pivotIndex && j > pivotIndex) {
			while (arr[i].compareTo(arr[pivotIndex]) < 0)
				i++;
			while (arr[j].compareTo(arr[pivotIndex]) >= 0)
				j--;
			if (i < pivotIndex && j > pivotIndex) {
				String temp1 = arr[i];
				arr[i] = arr[j];
				arr[j] = temp1;
			}

			// other way to code above is to put 3 if-else condition, and execute one by one
			// if(arr[i].compareTo(arr[pivotIndex]) < 0)
			// i++;
			// else if(arr[j].compareTo(arr[pivotIndex]) >= 0)
			// j--;
			// else{
			// String temp1 = arr[i];
			// arr[i] = arr[j];
			// arr[j] = temp1;
			// i++;
			// j--;
			// }
		}
		return pivotIndex;

	}

	/*
	 * This function mainly focuses on rearranging the elements. 
	 * Its secondary goal is to find pivotIndex parallely.
	 */
	private int partition(final String arr[], final int startIndex, final int endIndex) {
		String pivot = arr[endIndex];
		int freeIndex = startIndex; // aka pivotIndex
		for (int i = startIndex; i < endIndex; i++) {
			// move all smaller elements towards startIndex
			if (arr[i].compareTo(pivot) < 0) { // place pivotIndex element first among duplicates
				// swap arr[i] and arr[freeIndex]
				String temp = arr[i];
				arr[i] = arr[freeIndex];
				arr[freeIndex] = temp;
				freeIndex++;
			}
		}
		// swap arr[freeIndex] and pivot
		String temp = arr[freeIndex];
		arr[freeIndex] = arr[endIndex];
		arr[endIndex] = temp;
		return freeIndex;
	}
}

class MergeSort implements SortingAlgo {
	@Override
	public void sort(String arr[]) {
		mergeSort(arr, 0, arr.length - 1);
	}

	private void mergeSort(final String arr[], final int startIndex, final int endIndex) {
		if (startIndex >= endIndex)
			return;
		int midIndex = (startIndex + endIndex) / 2;
		mergeSort(arr, startIndex, midIndex);
		mergeSort(arr, midIndex + 1, endIndex);
		merge(arr, startIndex, midIndex, endIndex);
	}

	private void merge(final String arr[], final int startIndex, final int midIndex, final int endIndex) {
		String temp[] = new String[endIndex - startIndex + 1];
		int i = startIndex, j = midIndex + 1, k = 0;
		while (i <= midIndex && j <= endIndex) {
			if (arr[i].compareTo(arr[j]) <= 0) {
				temp[k++] = arr[i++];
			} else {
				temp[k++] = arr[j++];
			}
		}
		while (i <= midIndex) {
			temp[k++] = arr[i++];
		}
		while (j <= endIndex) {
			temp[k++] = arr[j++];
		}
		// Copy the sorted elements back to the original array
		for (int l = 0; l < temp.length; l++) {
			arr[startIndex + l] = temp[l];
		}
	}
}

class InBuiltSort implements SortingAlgo {
	@Override
	public void sort(String arr[]) {
		Arrays.sort(arr);
	}
}

public class SortingAlgos_StrategyDP {
	public static void main(String[] args) {
		// Given array of strings, sort it in lexigographical order in-place
		// Using Strategy Design Pattern to pass any strategy (as object) to sort

		String[] tc1_arr = { "banana", "apple", "orange", "kiwi", "grape" };
		String[] tc1_expected_arr = { "apple", "banana", "grape", "kiwi", "orange" };
		String[] tc2_arr = { "banana", "apple", "orange", "banana", "kiwi", "grape", "apple", "apple" };
		String[] tc2_expected_arr = { "apple", "apple", "apple", "banana", "banana", "grape", "kiwi", "orange" };
		String[] tc3_arr = { "orange", "kiwi", "grape", "banana", "banana", "apple", "apple", "apple" };
		String[] tc3_expected_arr = { "apple", "apple", "apple", "banana", "banana", "grape", "kiwi", "orange" };

		System.out.println(assertTestCase(tc1_arr, new BubbleSort(), tc1_expected_arr) == true);
		System.out.println(assertTestCase(tc1_arr, new QuickSort(), tc1_expected_arr) == true);
		System.out.println(assertTestCase(tc1_arr, new MergeSort(), tc1_expected_arr) == true);
		System.out.println(assertTestCase(tc2_arr, new BubbleSort(), tc2_expected_arr) == true);
		System.out.println(assertTestCase(tc2_arr, new QuickSort(), tc2_expected_arr) == true);
		System.out.println(assertTestCase(tc2_arr, new MergeSort(), tc2_expected_arr) == true);
		System.out.println(assertTestCase(tc3_arr, new BubbleSort(), tc3_expected_arr) == true);
		System.out.println(assertTestCase(tc3_arr, new QuickSort(), tc3_expected_arr) == true);
		System.out.println(assertTestCase(tc3_arr, new MergeSort(), tc3_expected_arr) == true);
	}

	public static boolean assertTestCase(String[] arr, SortingAlgo sortingAlgo, String[] expectedArr) {
		// Copy the original array to avoid modifying it during sorting
		String[] arrCopy = Arrays.copyOf(arr, arr.length);
		sortingAlgo.sort(arrCopy);
		if (arrCopy.length != expectedArr.length) {
			return false;
		}
		for (int i = 0; i < arrCopy.length; i++) {
			if (!arrCopy[i].equals(expectedArr[i])) {
				return false;
			}
		}
		return true;
	}

	/**
	 * Output:
	 * -------
	 * true
	 * true
	 * true
	 * true
	 * true
	 * true
	 * true
	 * true
	 * true
	 */
}
