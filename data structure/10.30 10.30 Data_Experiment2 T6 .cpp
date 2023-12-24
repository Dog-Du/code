#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=1e2+10;
int used[maxn];
int num[maxn];
int n;

void dfs(int x=1)
{
    if(x>n)
    {
        for(int i=1;i<=n;++i)
            cout<<num[i]<<' ';
        cout<<endl<<endl;
        return;
    }

    for(int i=1;i<=n;++i)
        if(!used[i])
        {
            num[x]=i;
            used[i]=1;
            dfs(x+1);
            used[i]=0;
        }
}

int main()
{
    cin>>n;

    dfs();


    cout<<endl;
    system("pause");
    return 0;
}
