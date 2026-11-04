void printSubsetSumToK(int input[], int size, int k, int output[], int top) {
    // Write your code here
    if(size==0)
    {
        if(k==0){
        for(int i=0;i<top;i++)
            cout<<output[i]<<" ";
        cout<<endl;}
        return;
    }
    printSubsetSumToK(input+1,size-1,k,output,top);
    output[top]=input[0];
    top++;
    printSubsetSumToK(input+1,size-1,k-input[0],output,top);
}
void printSubsetSumToK(int input[], int size, int k) 
{
    int *output=new int[size];
    printSubsetSumToK(input, size, k, output, 0) ;
    delete[]output;
        
}