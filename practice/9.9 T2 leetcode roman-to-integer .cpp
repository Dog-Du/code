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
    int romanToInt(string s) {

        int n=s.size(),ans=0;

        for(int i=0;i<n;++i)
        {
            if(s[i]=='I')
            {
                if(i+1<n&&(s[i+1]=='V'||s[i+1]=='X'))
                    --ans;
                else
                    ++ans;
            }
            else if(s[i]=='V')
                ans+=5;
            else if(s[i]=='X')
            {
                if(i+1<n&&(s[i+1]=='L'||s[i+1]=='C'))
                    ans-=10;
                else 
                    ans+=10;
            }
            else if(s[i]=='L')
                ans+=50;
            else if(s[i]=='C')
            {
                if(i+1<n&&(s[i+1]=='D'||s[i+1]=='M'))
                    ans-=100;
                else
                    ans+=100;
            }
            else if(s[i]=='D')
                ans+=500;
            else if(s[i]=='M')
                ans+=1000;
        }

        return ans;
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
