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
void mergeSort(int input[], int st, int end)
{
    if(end<=st)
        return;
    int mid=(st+end)/2;
    mergeSort(input,st,mid);
    mergeSort(input,mid+1, end);
    merge(input,st,end);
}
void mergeSort(int input[], int size){
	// Write your code here
	mergeSort(input, 0,size-1);
}
