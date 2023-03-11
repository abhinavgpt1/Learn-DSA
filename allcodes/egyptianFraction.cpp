/*
The Greedy algorithm works because a fraction is always reduced to a form 
where denominator is greater than numerator and numerator doesn’t divide denominator. 
For such reduced forms, the highlighted recursive call is made for reduced numerator. 
So the recursive calls keep on reducing the numerator till it reaches 1. 
*/
#include <bits/stdc++.h>
using namespace std;

void reduce(int &nr, int &dr)
{
	int x = __gcd(nr, dr);
	nr /= x;
	dr /= x;
}

void egyptian_fraction(int nr, int dr)
{
	int numr = nr, denr = dr;
	reduce(nr, dr);
	int count = 1;
	while (numr != 0)
	{

		int x = (ceil)(1.0 * denr / numr);
		if (count)
		{
			cout << "1/" << x;
			count--;
		}
		else
		{
			if (numr != 0)
				cout << " + 1/" << x;
		}
		numr = numr * x - denr;
		denr = denr * x;
		reduce(numr, denr);
	}
	cout << endl;
}
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int nr, dr;
		cin >> nr >> dr;
		egyptian_fraction(nr, dr);
	}
}