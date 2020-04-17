#include <iostream>
#include <set>

using namespace std;

int main()
{
	int x, i = 2;
	cout << "input number " << endl;
	set<int> allPrime;
	cin >> x;
	while(x >= 3)
	{
		while(0 == x%i)
		{		
			cout << x;
			x /= i;
			cout << '/' << i  << '=' << x << endl;
			allPrime.insert(i);
		}
		i++;
	}

	if(x != 1)
		cout << '[' << x << ']' << endl;


	for(set<int>::iterator it = allPrime.begin(); it != allPrime.end(); it++)
	{
		cout << ' ' << *it;
	}

	cout << endl;
	return 0;
}
