#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

#define ll long long

using namespace std;

const int maxn=1e4+10;

int pre[maxn];

int find(int x)
{
    return x==pre[x]?x:pre[x]=find(pre[x]);
}

void Union(int x,int y)
{
    x=find(x);
    y=find(y);

    if(x==y)return;

    pre[x]=y;
}

int n,m;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    
    cin>>n>>m;

    for(int i=1;i<=n;++i)pre[i]=i;

    while(m--)
    {
        int op,x,y;

        cin>>op>>x>>y;

        if(op==1)
        {
            Union(x,y);
        }
        else
        {

            if(find(x)==find(y))
            {
                cout<<"Y\n";
            }
            else
                cout<<"N\n";
        }
    }

    cout<<endl;
    system("pause");
    return 0;
}
