/*
Split Array
Send Feedback
Given an integer array A of size N, check if the input array can be splitted in two parts such that -
- Sum of both parts is equal
- All elements in the input, which are divisible by 5 should be in same group.
- All elements in the input, which are divisible by 3 (but not divisible by 5) should be in other group.
- Elements which are neither divisible by 5 nor by 3, can be put in any group.
Groups can be made with any set of elements, i.e. elements need not to be continuous. And you need to consider each and every element of input array in some group.
Return true, if array can be split according to the above rules, else return false.
Note : You will get marks only if all the test cases are passed.
Input Format :
Line 1 : Integer N (size of array)
Line 2 : Array A elements (separated by space)
Output Format :
true or false
Constraints :
1 <= N <= 50
Sample Input 1 :
2
1 2
Sample Output 1 :
false
Sample Input 2 :
3
1 4 3
Sample Output 2 :
true
*/
bool check(int arr[], int size, int s1, int s2){
    if(size == 0)
        return s1==s2;
    
    return check(arr+1,size-1, s1 + arr[0],s2) || check(arr+1,size-1,s1, s2 + arr[0]);
}
bool splitArray(int *input, int size) {
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Return output and don't print it.
     * Taking input and printing output is handled automatically.
     */
    int sum1 = 0;
    int sum2 = 0;
    int arr[size];
    int arr_size=0;
    for(int i = 0; i < size ; i++){
        if(input[i] % 5 == 0)
            sum1+=input[i];
        else if(input[i] % 3 == 0)
            sum2+=input[i];
        else
            arr[arr_size++] = input[i];
    }
    if(arr_size == 0)
        return sum1 == sum2;
    return check(arr,arr_size,sum1,sum2);
}
