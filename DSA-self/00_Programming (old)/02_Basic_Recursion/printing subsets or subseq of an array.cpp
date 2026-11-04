void print(int arr[],int size)
{
    for(int i=0;i<size;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}
void psoa(int input[],int start, int size,int output[], int top)
{
    if(start==size)
    {
        print(output,top);
        return;
    }
    psoa(input,start+1,size,output,top);
    output[top++]=input[start];
    psoa(input,start+1,size,output,top);
    
}
void printSubsetsOfArray(int input[], int size) {
	// Write your code here
    int *output=new int[size];
    psoa(input,0,size,output,0);
    delete [] output;
}
