/*
Code : In-place heap sort
Send Feedback
Given an integer array of size N. Sort this array (in decreasing order) using heap sort.
Note: Space complexity should be O(1).
Input Format:
The first line of input contains an integer, that denotes the value of the size of the array or N.
The following line contains N space separated integers, that denote the value of the elements of the array.
Output Format :
The first and only line of output contains array elements after sorting. The elements of the array in the output are separated by single space.
Constraints :
1 <= n <= 10^6
Time Limit: 1 sec
Sample Input 1:
6 
2 6 8 5 4 3
Sample Output 1:
8 6 5 4 3 2
*/
void swap(int &a, int &b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}
void heapSort(int input[], int n)
{
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Change in the given input itself.
     * Taking input and printing output is handled automatically.
     */
    //heapify
    for (int i = 1; i < n; i++)
    {
        int childIndex = i;
        while (childIndex > 0)
        {
            int parentIndex = (childIndex - 1) / 2;
            if (input[parentIndex] > input[childIndex])
                swap(input[parentIndex], input[childIndex]);
            else
                break;
            childIndex = parentIndex;
        }
    }
    //remove Min
    for (int i = n - 1; i > 0; i--)
    {

        swap(input[0], input[i]);
        int size = i;
        int parentIndex = 0;
        int childIndex1 = 2 * parentIndex + 1;
        int childIndex2 = 2 * parentIndex + 2;
        while (childIndex1 < size)
        {
            int minIndex = parentIndex;
            if (input[minIndex] > input[childIndex1])
                minIndex = childIndex1;
            if (childIndex2 < size && input[minIndex] > input[childIndex2])
                minIndex = childIndex2;
            if (minIndex == parentIndex)
                break;
            swap(input[minIndex], input[parentIndex]);

            parentIndex = minIndex;
            childIndex1 = 2 * parentIndex + 1;
            childIndex2 = 2 * parentIndex + 2;
        }
    }
}

void inplaceHeapSort(int pq[], int n)
{
    // Build the heap in input array
    for (int i = 1; i < n; i++)
    {

        int childIndex = i;
        while (childIndex > 0)
        {
            int parentIndex = (childIndex - 1) / 2;

            if (pq[childIndex] < pq[parentIndex])
            {
                int temp = pq[childIndex];
                pq[childIndex] = pq[parentIndex];
                pq[parentIndex] = temp;
            }
            else
            {
                break;
            }
            childIndex = parentIndex;
        }
    }
    // Remove elements

    int size = n;

    while (size > 1)
    {
        int temp = pq[0];
        pq[0] = pq[size - 1];
        pq[size - 1] = temp;

        size--;

        int parentIndex = 0;
        int leftChildIndex = 2 * parentIndex + 1;
        int rightChildIndx = 2 * parentIndex + 2;

        while (leftChildIndex < size)
        {
            int minIndex = parentIndex;
            if (pq[minIndex] > pq[leftChildIndex])
            {
                minIndex = leftChildIndex;
            }
            if (rightChildIndx < size && pq[rightChildIndx] < pq[minIndex])
            {
                minIndex = rightChildIndx;
            }
            if (minIndex == parentIndex)
            {
                break;
            }
            int temp = pq[minIndex];
            pq[minIndex] = pq[parentIndex];
            pq[parentIndex] = temp;

            parentIndex = minIndex;
            leftChildIndex = 2 * parentIndex + 1;
            rightChildIndx = 2 * parentIndex + 2;
        }
    }
}
