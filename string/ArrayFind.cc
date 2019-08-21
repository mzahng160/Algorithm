#include <vector>
#include <iostream>

using namespace std;

bool Arrayfind(int target, vector<vector<int> > array, int xpos, int ypos)
{
    int ret = false;
    std::vector<int> vec;

    if(target > array[xpos][ypos])
    {
        cout << "["<< xpos << "]" << "[" << ypos << "]" << 
                array[xpos][ypos] << endl;
        
        int xend = xpos + xpos / 2;
        int yend = ypos + ypos / 2;
        xpos = xend+yend*array[0].size();

        Arrayfind(target, array, xpos,ypos);
    }

    if(target < array[xpos][ypos])
    {
        cout << "["<< xpos << "]" << "[" << ypos << "]" << 
                array[xpos][ypos] << endl;

        int xend = ypos / 2;
        int yend = xpos / 2;
        ypos = xend+yend*array[0].size();
                
        
        Arrayfind(target, array, xpos,ypos);
    }

    if(target == array[xpos][ypos])
    {

        cout << "["<< xpos << "]" << "[" << ypos << "]" << 
                array[xpos][ypos] << endl;
        ret = true;
        
    }

    return ret;
}

bool Find(int target, vector<vector<int> > array) {
    
    int xend = array[0].size()-1;
    int yend = array.size() - 1;
    int i = xend/2, j = yend/2;
    
    if(target < array[0][0] || target > array[xend][yend])
        return false;
    Arrayfind(target, array, i, j);
}

int main()
{
    //int array[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    vector<vector<int> > array;
    for(int i = 0; i < 3; ++i)
    {
        vector<int> tmp;
        for(int j = i*3+1; ; ++j)
        {
            tmp.push_back(j);
            if(j % 3 == 0)
            {
                array.push_back(tmp);
                break;
            }
        }
    }

    cout << Find(2, array) << endl;
    //cout << Find(2, ) << endl;
}