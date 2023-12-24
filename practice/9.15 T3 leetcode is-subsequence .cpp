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
    bool isSubsequence(string s, string t) {
        int p1=0,p2=0,l1=s.size(),l2=t.size();

        while(p1<l1&&p2<l2)
        {
            if(t[p2]==s[p1])
                ++p1;
            ++p2;
        }

        return p1==l1;
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
