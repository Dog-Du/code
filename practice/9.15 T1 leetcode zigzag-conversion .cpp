#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows<=1)return s;

        int n=s.size(),p=0,l=-1,r=0;

        vector<vector<char>> vec(numRows,vector<char>(n,' '));
        string ans;

        while(p<n)
        {
           while(p<n&&l<numRows-1)
                vec[++l][r]=s[p++];

            while(p<n&&l>0)
                vec[--l][++r]=s[p++];
        }

        
        for(auto&v:vec)
            for(auto&it:v)
                if(it!=' ')
                    ans+=it;
        
        return ans;

    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    Solution one;
    string s="PAYPALISHIRING";

    cout<<one.convert(s,3);


    cout<<endl;
    system("pause");
    return 0;
}
