/*Pair sum in array
Send Feedback
Given a random integer array A and a number x. Find and print the pair of elements in the array which sum to x.
Array A can contain duplicate elements.
While printing a pair, print the smaller element first.
That is, if a valid pair is (6, 5) print "5 6". There is no constraint that out of 5 pairs which have to be printed in 1st line. You can print pairs in any order, just be careful about the order of elements in a pair.
Input format :
Line 1 : Integer N (Array size)
Line 2 : Array elements (separated by space)
Line 3 : Integer x
Output format :
Line 1 : Pair 1 elements (separated by space)
Line 2 : Pair 2 elements (separated by space)
Line 3 : and so on
Constraints :
1 <= N <= 1000
1 <= x <= 100
Sample Input:
9
1 3 6 2 5 4 3 2 4
7
Sample Output :
1 6
3 4
3 4
2 5
2 5
3 4
3 4
*/
#include<algorithm>
void pairSum(int input[], int size, int x) {
	sort(input,input+size);
    int first=0,last=size-1;

    while(first<last){
        if(input[first]+input[last]>x)
        {
        	last--;
        }
        else if(input[first]+input[last]<x){
            first++;
        }
        else{
            int dup_first=first;
            int dup_last=last;
            while(input[dup_first]==input[first]){
            	dup_last=last;
            	while(input[dup_last]==input[last] && dup_first<dup_last)
            	{
            	    cout<<input[first]<<" "<<input[last]<<endl;
            	    dup_last--;
            	}
                dup_first++;
            }
            first=dup_first;
            last=dup_last;
        }
    }
}
// Method 2
#include<algorithm>
void pairSum(int input[], int size, int x) {
	sort(input,input+size);
    int first=0,last=size-1;

    while(first<last){
        if(input[first]+input[last]>x)
        {
        	last--;
        }
        else if(input[first]+input[last]<x){
            first++;
        }
        else
        {
            int tempfirst=input[first];
            int leftcount=0;
            while(input[first]==tempfirst)
            {
                first++;
                leftcount++;
            }
            int paircount=0;
            int templast=input[last];
            
            if(tempfirst==templast)
                paircount=leftcount*(leftcount-1)/2;
            else{    
                int rightcount=0;
                while(input[last]==templast)
            	{
            	    last--;
            	    rightcount++;
            	}
                paircount=leftcount*rightcount;
            }
            for(int i=0;i<paircount;i++)
            {
                 cout<<tempfirst<<" "<<templast<<endl;
            }
        }
    }
}
