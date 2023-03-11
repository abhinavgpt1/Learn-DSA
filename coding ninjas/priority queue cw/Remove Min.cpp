/*
Code : Remove Min
Send Feedback
Implement the function RemoveMin for the min priority queue class.
For a minimum priority queue, write the function for removing the minimum element present. Remove and return the minimum element.
Note : main function is given for your reference which we are using internally to test the code.
*/
#include <vector>
#include<iostream>
using namespace std;
class PriorityQueue
{
    vector<int> pq;

public:
    bool isEmpty()
    {
        return pq.size() == 0;
    }

    int getSize()
    {
        return pq.size();
    }

    int getMin()
    {
        if (isEmpty())
        {
            return 0;
        }

        return pq[0];
    }

    void insert(int element)
    {
        pq.push_back(element);

        int childIndex = pq.size() - 1;

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

    int removeMin()
    {
        if (isEmpty())
            return -1;
        int ans = pq[0];
        swap(pq[0], pq[pq.size() - 1]);
        pq.pop_back();
        int parentIndex = 0;
        int childIndex1 = 2 * parentIndex + 1;
        int childIndex2 = 2 * parentIndex + 2;
        while (childIndex1 < pq.size())
        {
            int minIndex = parentIndex;
            if (pq[minIndex] > pq[childIndex1])
                minIndex = childIndex1;
            if (childIndex2 < pq.size() && pq[minIndex] > pq[childIndex2])
                minIndex = childIndex2;
            if (minIndex == parentIndex)
                break;
            swap(pq[minIndex], pq[parentIndex]);
            parentIndex = minIndex;
            childIndex1 = 2 * parentIndex + 1;
            childIndex2 = 2 * parentIndex + 2;
        }
        return ans;
    }
};

//wrong
int removeMin()
{
    // Complete this function
    if (pq.empty())
        return 0;
    int ans = pq[0];
    pq[0] = pq[pq.size() - 1];
    pq.pop_back();

    int parentIndex = 0;
    int size = pq.size();
    int childIndex1 = 2 * parentIndex + 1;
    int childIndex2 = 2 * parentIndex + 2;
    while (childIndex1 < size && childIndex2 < size)
    { //will fail at childINdex1 < size and childINdex2 = size && pq[parentINdex] < pq[childIndex1]

        int minIndex = parentIndex;
        if (pq[minIndex] > pq[childIndex1])
            minIndex = childIndex1;
        if (pq[minIndex] > pq[childIndex2])
            minIndex = childIndex2;
        if (minIndex == parentIndex)
            break;
        swap(pq[parentIndex], pq[minIndex]);

        parentIndex = minIndex;
        childIndex1 = 2 * parentIndex + 1;
        childIndex2 = 2 * parentIndex + 2;
    }
    return ans;
}