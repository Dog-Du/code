#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define ll long long

using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int Hash[1000]={0},Count[1000]={0};

        for(int i=0,n=s.size();i<n;++i)
        {
            if(Hash[s[i]]&&Hash[s[i]]!=t[i])return false;
            else if(!Hash[s[i]]&&Count[t[i]])return false;
            else if(!Hash[s[i]]&&!Count[t[i]])
            {
                Hash[s[i]]=t[i];
                Count[t[i]]=1;
            }
        }
        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    


    cout<<endl;
    system("pause");
    return 0;
}
