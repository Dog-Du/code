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
    bool canConstruct(string ransomNote, string magazine) {
        int Hash[26]={0};

        for(auto&it:magazine)++Hash[it-'a'];
        for(auto&it:ransomNote)
            if((--Hash[it-'a'])<0)return false;
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
