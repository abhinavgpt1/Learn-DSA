#include <bits/stdc++.h>
using namespace std;
int minSubsetSumDiff(int arr[], int n, int localSum, int sumArr){
    if(n == 0)
    return abs(sumArr - 2*localSum);

    return min(minSubsetSumDiff(arr, n-1, localSum, sumArr), minSubsetSumDiff(arr, n-1, localSum + arr[n-1], sumArr));
}
int main(){
    int arr[] = {2,3,7,8,11};
    int sumArr = 0;
    sumArr = accumulate(arr, arr+sizeof(arr)/sizeof(int),0);
    cout<<minSubsetSumDiff(arr, sizeof(arr)/sizeof(int), 0, sumArr)<<endl;
}