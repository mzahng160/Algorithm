class Different {
public:
    bool checkDifferent(string iniString) {
        // write code here
        for(int i = 0; i < iniString.size(); i++)
        {
            for(int j = i; j < iniString.size()-1; j++)
            {
                if(iniString.at(i) == iniString.at(j+1))
                    return false;
            }
        }
        
        return true;
    }
};
