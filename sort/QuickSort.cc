#include <iostream>

using namespace std;

void print(int s[], int len)
{
	int i = 0;
	while (i < len)
	{
		cout << s[i] << '\t';
		i++;
	}
	cout << endl;
}

int quickSortPartition(int s[], int l, int r)
{
	int i = l, j = r, x = s[l];
	while (i < j)
	{
		while (i < j && x <= s[j])
			j--;
		if (i < j)
			s[i++] = s[j];

		while (i < j && x >= s[i])
			i++;
		if (i < j)
			s[j--] = s[i];
	}
	s[i] = x;
	return i;
}

void quickSort(int s[], int l, int r)
{
	if (l >= r)
		return;
	int mid = quickSortPartition(s, l, r);
	quickSort(s, l, mid - 1);
	quickSort(s, mid + 1, r);
}

int main(int argc, char* argv[])
{
	//int a[] = { 72, 6, 57, 88, 60, 42, 83, 73, 48, 85 };
	int a[] = { 1, 342, 21, 43, 22, 12, 44, 98 };
	int cnt = sizeof a / sizeof(int);

	print(a, cnt);
	quickSort(a, 0, cnt - 1);
	print(a, cnt);
	getchar();
	return 0;
}

