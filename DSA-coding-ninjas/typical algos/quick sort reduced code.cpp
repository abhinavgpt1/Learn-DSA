int partition(int input[],int end)
{
    int x=input[0];
    int index=0;
    for(int i=1;i<=end;i++)
    {
        if(input[i]<x)
            index++;
    }
    
    //swapping
    int temp=input[index];
    input[index]=x;
    input[0]=temp;
    //segregating
    // NOTE: Check SortingAlgos_StrategyDP.java for efficient quickSort - runs in a single loop [st aka 0, end]
    int i=0,j=end;
    while(i!=index && j!=index)
    {
        if(input[i]<x)
            i++;
        else if(input[j]>=x)
            j--;
        else
        {
            temp=input[i];
   			input[i]=input[j];
   			input[j]=temp;
            i++;
            j--;
        }
    }
    return index;
}

void quickSort(int input[], int size) {
  /* Don't write main().
     Don't read input, it is passed as function argument.
     Change in the given array itself.
     Taking input and printing output is handled automatically.
  */
	if(size<=1)
        return;
    int index=partition(input,size-1);
    quickSort(input,index);
    quickSort(input+index+1,size-1 - index);
}
