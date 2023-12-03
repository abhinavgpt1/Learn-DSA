#include <bits/stdc++.h>
using namespace std;
// arr:[whatever], sum = 0 - true, as {} has sum = 0
bool checkSubsetSum(int arr[], int n, int sum, int index){
    if(index == n){
        return sum == 0;
    }
    return checkSubsetSum(arr, n, sum, index + 1) || checkSubsetSum(arr, n, sum - arr[index], index + 1);
}
int main(){
    int arr[] = {2,3,7,8,10};
    int sum = 11;
    if(checkSubsetSum(arr, sizeof(arr)/sizeof(int), sum, 0))
    cout<<"Present"<<endl;
    else
    cout<<"Not Present"<<endl;
}