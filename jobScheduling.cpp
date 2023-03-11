/*

// readjusts the excedding deadline limit beyond n 
// eg. deadline is 100 but we are given 4 jobs only

struct Job
{
char id;	 // Job Id
int dead; // Deadline of job
int profit; // Profit if job is over before or on deadline
};

// This function is used for sorting all jobs according to profit
bool comparison(Job a, Job b)
{
	return (a.profit > b.profit);
}

// Returns minimum number of platforms required
void printJobScheduling(Job arr[], int n)
{
	// Sort all jobs according to decreasing order of profit
	sort(arr, arr+n, comparison);

	int result[n]; // To store result (Sequence of jobs)
	bool slot[n]; // To keep track of free time slots

	// Initialize all slots to be free
	for (int i=0; i<n; i++)
		slot[i] = false;

	// Iterate through all given jobs
	for (int i=0; i<n; i++)
	{
	// Find a free slot for this job (Note that we start
	// from the last possible slot)
	for (int j=min(n, arr[i].dead)-1; j>=0; j--)
	{
		// Free slot found
		if (slot[j]==false)
		{
			result[j] = i; // Add this job to result
			slot[j] = true; // Make this slot occupied
			break;
		}
	}
	}
}
*/
#include <bits/stdc++.h>
using namespace std;
//id, deadline , profit
bool jobComp(tuple<char, int, int> const &a, tuple<char, int, int> const &b)
{
	return get<2>(a) > get<2>(b);
}
int jobSchedule(vector<tuple<char, int, int>> jobs, int n)
{

	int glob_profit = 0;
	vector<char> slots(101, '\0');
	
	sort(jobs.begin(), jobs.end(), jobComp);
	
	for(int i=0; i<n; i++){
		tuple<char, int, int> tmp = jobs[i];
		for(int j = get<1>(tmp); j>=1; j--){
			if(slots[j] == '\0'){
				slots[j] = get<0>(tmp);
				glob_profit += get<2>(tmp);
				break;
			}
		}
	}
	for(auto x: slots){
		if(x != '\0')
		cout<<x<<" ";
	}
	cout<<endl;
	return glob_profit;
}
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;

		vector<tuple<char, int, int>> jobs;
		for (int i = 0; i < n; i++)
		{
			char job_id;
			int deadline, profit;
			cin >> job_id >> deadline >> profit;
			jobs.push_back({job_id, deadline, profit});
		}
		cout << jobSchedule(jobs, n) << endl;
	}
}