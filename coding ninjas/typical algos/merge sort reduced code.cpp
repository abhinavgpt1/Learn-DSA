void merge(int input[],int start, int end)
{
    int mid=(start+end)/2;
    int size=end-start+1;
    int *temp=new int[size];int top=-1;
    int i=start, j=mid+1;
    while(i<=mid && j<=end)
    {
        if(input[i]<input[j])
        {
            temp[++top]=input[i];
            i++;
        }
        else
        {
            temp[++top]=input[j];
            j++;
        }
    }
    while(i<=mid)
    {
        temp[++top]=input[i];
        i++;
    }
    while(j<=end)
    {
        temp[++top]=input[j];
        j++;
    }
    int m=0;
    for(int i=start;i<=end;i++)
    {
        input[i]=temp[m];
        m++;
    }
    delete [] temp;
}
void mergeSort(int input[], int size)
{
	if(size<=1)
		return;
	int st=0;
	int end=size-1;
	int mid=end/2;
	mergeSort(input, mid+1);
	mergeSort(input+mid+1,end-mid);
	merge(input,st,end);
}
