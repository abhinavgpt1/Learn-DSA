//METHOD 2
// input - input array
// size - length of input array
// element - value to be searched
int binarySearch(int input[], int size, int element) {
    // Write your code here
    if(size<=0)
        return -1;
	
    int mid=(size-1)/2;//IMPORTANT to take first mid when size is even
    
    if(input[mid]==element)
        return mid;
    else if(input[mid]>element)
    {
        int c=binarySearch(input,mid,element);
        return (c==-1?-1:c);//as you go leftwards the index of mid remains same relative to base index
    }    
    else
    {
        int c=binarySearch(input+mid+1,size-mid-1,element);
        return (c==-1?-1:mid+1+c);//as you go rightwards the index of mid doesn't remain same relative to base index
        //but remains same relative to mid+1
    }
}

//METHOD 1
// input - input array
// size - length of input array
// element - value to be searched
int bin(int input[],int s, int e, int x)
{
    if(s>e)
        return -1;
    
    int mid=(e+s)/2;
    
    if(input[mid]==x)
        return mid;
    else if(input[mid]>x)
        return bin(input,s,mid-1,x);
    else
        return bin(input,mid+1,e,x);
}
int binarySearch(int input[], int size, int element) {
    // Write your code here
    return bin(input,0,size-1,element);
}
