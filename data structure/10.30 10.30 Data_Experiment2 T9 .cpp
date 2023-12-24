#include <iostream>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=1e3+10;
int weight[maxn],path[maxn];//path为所选重量
int n,m,cnt=0;

void dfs(int x,int w)
{
    if(w==m)
    {
        for(int i=0;i<cnt;++i)
            cout<<path[i]<<' ';
        cout<<endl;
        return;
    }

    if(w+weight[x]>m)return;

    for(int i=x;i<=n;++i)
    {
        path[cnt++]=weight[i];
        dfs(i+1,w+weight[i]);
        --cnt;
    }
}

int main()
{
    cin>>m>>n;

    for(int i=1;i<=n;++i)
    {
        cin>>weight[i];
    }
    
    sort(weight+1,weight+1+n);

    dfs(1,0);

    cout<<endl;
    system("pause");
    return 0;
}
