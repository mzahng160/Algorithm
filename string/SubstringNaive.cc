#include <iostream>
#include <string>

using namespace std;

int Index(string str, string sub)
{
	if (str.empty() || sub.empty() || str.size() < sub.size())
		return -1;

	int i = 0, j = 0;
	while (i < str.size() && j < sub.size())
	{
		if (str[i] == sub[j])
		{
			cout << '[' << str[i] << ']' << '{' << sub[j] << '}' << '\t';
			i++;
			j++;
		}
		else
		{
			cout << '[' << str[i] << ']' << '*' << sub[j] << '*' << '\t';
			i = i - j + 1;
			j = 0;
		}

		if (j == sub.size())
			return i - j;
	}

	return -1;
}

int main()
{
	int i = Index("thisisgoogle", "ogl");

	cout << i << endl;

	getchar();

	return 0;
}

