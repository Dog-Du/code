#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int n,p;
    cin>>n>>p;
    //查分数组相当于斜率.
    int a[n+1]={0},b[n+1]={0};//a为差分，b为原数组,a[i]=b[i]-b[i-1];

    for(int i=1;i<=n;++i)
        cin>>b[i],a[i]=b[i]-b[i-1];

    while(p--)
    {
        int x,y,z;
        cin>>x>>y>>z;

        a[x]+=z;//起点加上增量
        a[y+1]-=z;//尾端减去增量，为了不影响后续的数字
    }

    int ans=1e9;

    for(int i=1;i<=n;++i)
    {
        b[i]=b[i-1]+a[i];//还原,b[i]=b[i-1]+a[i];
        ans=min(ans,b[i]);
    }

    cout<<ans<<endl;
    
    cout<<endl;
    system("pause");
    return 0;
}
