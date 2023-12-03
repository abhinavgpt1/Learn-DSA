/*
Given an array of length N and an integer x, you need to find all the indexes where x is present in the input array. Save all the indexes in an array (in increasing order).
Do this recursively. Indexing in the array starts from 0.
*/
#include<iostream>
using namespace std;


//forward cutting
int allIndexes2(int input[], int size, int x, int output[]) 
{
    if(input==NULL)
        return -1;
    if(size==1)
    {
        int top=0;
        if(input[0]==x)
        {
            output[0]=0;
            top++;
        }
        return top;
        
    }
    int top=allIndexes2(input+1,size-1,x,output);
    // printf("%d",top);
    for(int i=0;i<top;i++)
    {
        output[i]++;
    }
    if(input[0]==x)
    {
        for(int i=top;i>0;i--)
        {
            output[i]=output[i-1];
        }
        output[0]=0;
        top++;
    }
    return top;
}

//backward cutting
int allIndexes(int input[], int size, int x, int output[]) 
{
    if(input==NULL)
        return -1;
    if(size==1)//same function as above
    {
        int top=0;
        if(input[size-1]==x)
            {output[top++]=size-1;return top;}
        return top;
    }
    int top=allIndexes(input,size-1,x,output);
    //printf("%d",top);
    if(input[size-1]==x)
    {output[top++]=size-1;return top;}
    return top;
}



int main(){
    int n;
    cin >> n;
  
    int *input = new int[n];
    
    for(int i = 0; i < n; i++) {
        cin >> input[i];
    }
    
    int x;
    
    cin >> x;
    
    int *output = new int[n];
    
    int size = allIndexes(input, n, x, output);
    for(int i = 0; i < size; i++) {
        cout << output[i] << " ";
    }
    
    delete [] input;
    
    delete [] output;
    

}


