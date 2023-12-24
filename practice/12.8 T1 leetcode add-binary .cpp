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
    string addBinary(string a, string b) {
        bool t=0;
        if(a.size()>b.size())a.swap(b);
        string ans;
        int n=a.size(),m=b.size();
        int i,j,sum;

        for(i=n-1,j=m-1;i>=0;--i,--j)
        {
            sum=a[i]-'0'+b[j]-'0'+t;

            ans.push_back(sum%2+'0');
            t=sum>=2;
        }

        while(j>=0)
        {
            sum=b[j]-'0'+t;
            ans.push_back(sum%2+'0');
            t=sum>=2;
            --j;
        }

        if(t)ans.push_back('1');

        reverse(ans.begin(),ans.end());
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
