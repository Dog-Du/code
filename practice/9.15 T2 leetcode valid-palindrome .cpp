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
    bool isPalindrome(string s) {
        int l=0,r=0,n=s.size();

        while(r<n)
        {
            s[r]=tolower(s[r]);

            if((s[r]>='a'&&s[r]<='z')||(s[r]>='0'&&s[r]<='9'))
                s[l++]=s[r++];
            else
                ++r;
        }

        r=l-1,l=0;

        while(l<r)
            if(s[l++]!=s[r--])
                return false;
        
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
