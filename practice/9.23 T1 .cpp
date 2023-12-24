#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stack>

#define ll long long

using namespace std;

const int maxn=2e5+10;

string s1,s2;
int n1,n2,num1[maxn],num2[maxn],ans[maxn];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>s1>>s2;
    n1=s1.size();
    n2=s2.size();

    for(int i=0;i<n1;++i)num1[i]=s1[n1-i-1]-'0';
    for(int i=0;i<n2;++i)num2[i]=s2[n2-i-1]-'0';

    int n=max(n1,n2),flag=0;

    for(int i=0,temp;i<n;++i)
    {
        temp=num1[i]+num2[i]+flag;

        if(temp>=10)
        {
            ans[i]=temp%10;
            flag=1;
        }
        else
        {
            ans[i]=temp;
            flag=0;
        }
    }

    if(flag)
    {
        cout<<1;
    }
    
    for(int i=n-1;i>=0;--i)
        cout<<ans[i];
    

    cout<<endl;
    system("pause");
    return 0;
}
