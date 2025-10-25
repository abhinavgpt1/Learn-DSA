int partition(int input[],int st, int en)
{
    int index=st;//count
    int x=input[st];
    
	for(int i=st+1;i<=en;i++)
    {
        if(input[i]<=x)
            index++;
    }
    //x at right place
    int temp=input[index];
    input[index]=x;
    input[st]=temp;
    
    //segregating
    // NOTE: Check SortingAlgos_StrategyDP.java for efficient quickSort - runs in a single loop [st aka 0, end]
    int i=st,j=en;
    while(i!=index && j!=index)
    {
        if(input[i]<=x)
            i++;
        else if(input[j]>x)//equality kaa decision decide krega index find krne wala loop
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
}
void quicksort(int input[],int start, int end)
{
    if(end<=start)
        return;
    int index=partition(input, start,end);
    
 	quicksort(input,start,index-1);
 	quicksort(input,index+1,end);
}
void quickSort(int input[], int size) {
	quicksort(input,0,size-1);
}
