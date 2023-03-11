/*
Triplet sum
Send Feedback
Given a random integer array and a number x. Find and print the triplets of elements in the array which sum to x.
While printing a triplet, print the smallest element first.
That is, if a valid triplet is (6, 5, 10) print "5 6 10". There is no constraint that out of 5 triplets which have to be printed on 1st line. You can print triplets in any order, just be careful about the order of elements in a triplet.
*/
// arr - input array
// size - size of array
// x - sum of triplets
#include<algorithm>
void FindTriplet(int arr[], int n, int x) {
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Print output and don't return it.
     * Taking input is handled automatically.
     */
    sort(arr,arr+n);
    for(int i=0;i<n-2;i++)
    {
        
    int temp_x=x-arr[i];
        int mid=i+1;
        int last=n-1;
    int left=mid,right=last;
	while(left<right)
    {        
        if(arr[left]+arr[right]>temp_x)
            right--;
        else if(arr[left]+arr[right]<temp_x)
            left++;
        else{
        	int templeft=arr[left];
        	int leftcount=0;
        	while(arr[left]==templeft)
        	{
        	    leftcount++;
        	    left++;
        	}
        	int tempright=arr[right];
        	int totalCount=0;
        	
        	if(tempright==templeft)
        	{
        	    totalCount=(leftcount)*(leftcount-1)/2;
        	}
        	else{
        	    int rightcount=0;
        		while(arr[right]==tempright)
        		{
        		    right--;
        		    rightcount++;
        		}
        	    totalCount=leftcount*rightcount;
        	}
        	for(int j=0;j<totalCount;j++)
        	    cout<<arr[i]<<" "<<templeft<<" "<<tempright<<endl;
        }
    }
    }
}
