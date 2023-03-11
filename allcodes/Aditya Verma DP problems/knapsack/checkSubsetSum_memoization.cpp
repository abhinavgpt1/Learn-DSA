/*
right to left
*/
#include <bits/stdc++.h>
using namespace std;
int dp[1000][1000];
bool checkSubsetSum(int arr[], int n, int sum){
    if(n == 0){
        return sum == 0;
    }
    if(dp[n-1][sum] != -1)
        return dp[n-1][sum];

    return dp[n-1][sum] = (checkSubsetSum(arr, n - 1, sum) || checkSubsetSum(arr, n-1, sum - arr[n-1]));
}
int main(){
    int arr[] = {2,3,7,8,10};
    int sum = 11;
    memset(dp, -1, sizeof(dp));
    if(checkSubsetSum(arr, sizeof(arr)/sizeof(int), sum))
    cout<<"Present"<<endl;
    else
    cout<<"Not Present"<<endl;
// }

/*
left to right
*/
#include <bits/stdc++.h>
using namespace std;
int dp[1000][1000];
bool checkSubsetSum(int arr[], int n, int sum, int index){
    if(index == n){
        return sum == 0;
    }
    if(dp[index][sum] != -1)
        return dp[index][sum];

    return dp[index][sum] = (checkSubsetSum(arr, n, sum, index + 1) || checkSubsetSum(arr, n, sum - arr[index], index + 1));
}
int main(){
    int arr[] = {2,3,7,8,10};
    int sum = 11;
    memset(dp, -1, sizeof(dp));
    if(checkSubsetSum(arr, sizeof(arr)/sizeof(int), sum, 0))
    cout<<"Present"<<endl;
    else
    cout<<"Not Present"<<endl;
}