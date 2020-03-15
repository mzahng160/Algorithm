#include <iostream>
#include <string>

using namespace std;

int GetLastWordsLen(string& words)
{

    int count = 0;
    for (int i = words.size() - 1; i >= 0; --i)
    {
        if (words.at(i) == ' ')
        {
            cout << "[" << words[i] << "]" << endl;
            break;
        }
        else
        {
            cout << "(" << words[i] << ")" << endl;
            count++;
        }
            
    }
    return count;
}

int main()
{
    char words[5000];
    string str;
    
    cin.getline(words, sizeof words);
    str = words;
    int count = GetLastWordsLen(str);
    cout << count << endl;

    return 0;
}
