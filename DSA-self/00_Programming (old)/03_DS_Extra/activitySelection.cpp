#include <bits/stdc++.h>
using namespace std;
bool activityComp(pair<int, int> a, pair<int, int> b){
	return a.second < b.second;
}
int maxActivities(vector<int> start, vector<int> finish, int n){
	vector<pair<int, int>> times;
	for(int i=0; i<n; i++){
		times.push_back({start[i], finish[i]});
	}
	sort(times.begin(), times.end(), activityComp);
	int count = 0, fin = 0;
	for(int i=0; i<n; i++){
		if(i ==0 || times[i].first>=fin){
			fin = times[i].second;
			cout<<times[i].first<<" "<<times[i].second<<endl;
			count++;
		}
	}
	return count;
}
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		vector<int> start(n), finish(n);
		for(int i = 0; i<n; i++){
			cin>>start[i];
		}
		for(int i = 0; i<n; i++){
			cin>>finish[i];
		}
		cout<<maxActivities(start, finish, n)<<endl;
	}
}