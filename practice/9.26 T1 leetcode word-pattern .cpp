#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

#define ll long long

using namespace std;

class Solution {
public:
    bool wordPattern(string pattern, string s) {
        unordered_map<char,string> mp;
        unordered_set<string> se;

        int p1=0,p2=0,length=0,n=pattern.size(),m=s.size();

        while(p1<n&&p2<m)
        {
            while(p2+length<m&&s[p2+length]!=' ')++length;

            if(mp.count(pattern[p1])&&mp[pattern[p1]]!=s.substr(p2,length))return false;
            else if(!mp.count(pattern[p1])&&se.count(s.substr(p2,length)))return false;
            else if(!mp.count(pattern[p1])&&!se.count(s.substr(p2,length)))
            {
                mp[pattern[p1]]=s.substr(p2,length);
                se.insert(s.substr(p2,length));
            }

            ++p1;
            p2+=length+1;
            length=0;
        }

        if(p2<m||p1<n)return false;
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
