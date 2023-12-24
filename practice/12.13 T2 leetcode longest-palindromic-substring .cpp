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
    string longestPalindrome(string s) {
        int n=s.size(),ansl=0,ansr=0;

        for(int i=0,l,r;i<n-1;++i)
        {
            l=i-1,r=i+1;

            while(l>=0&&r<n&&s[l]==s[r])
                --l,++r;

            if(r-l-1>ansr-ansl+1)
                ansl=l+1,ansr=r-1;
            
            if(s[i]==s[i+1])
            {
                l=i-1,r=i+2;

                while(l>=0&&r<n&&s[l]==s[r])
                    --l,++r;

                if(r-l-1>ansr-ansl+1)
                    ansl=l+1,ansr=r-1;
            }
        }

        return s.substr(ansl,ansr-ansl+1);
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
