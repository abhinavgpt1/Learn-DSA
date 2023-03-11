//less code but little tough

int binarySearch(int input[], int size, int element)
{
    if (size <= 0)
        return -1;

    int mid = (size - 1) / 2;
    if (input[mid] == element)
        return mid;
    else if (input[mid] > element)
        return binarySearch(input, mid, element);
    else
    {
        int smallAns = binarySearch(input + mid + 1, size - mid - 1, element);
        if (smallAns == -1)
            return -1;
        return mid + 1+ smallAns;
    }
}
