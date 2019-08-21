#include <string>
#include <iostream>

using namespace std;

bool IsPalindrom(string str)
{
	int len = str.size();
	for(int i = 0; i < len / 2; ++i)
	{
		if(str[i] != str[len - i- 1])
			return false;
	}

	return true;
}

int main(int argc, char const *argv[])
{
	
	cout << (IsPalindrom("abccba") ? "true":"false") << endl;

	return 0;
}