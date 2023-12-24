#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include <unordered_map>

#define ll long long

using namespace std;

const int maxn=1e6+10;

int node[maxn<<2][65],cnt[maxn<<2];

int n,q,tot=0;

int getnum(char &ch)
{
    if(ch>='0'&&ch<='9')return ch-'0';
    else if(ch>='a'&&ch<='z')return ch-'a'+10;
    else return ch-'A'+10+26;
}

void insert(string &s)
{
    int p=0;

    for(auto&it:s)
    {
        int temp=getnum(it);

        if(!node[p][temp])node[p][temp]=++tot;//如果没有这个子树，则创建，是一种动态开点的树

        p=node[p][temp];//下一层递归
        ++cnt[p];//路径上均+1
    }
}

int find(string &s)
{
    int p=0;

    for(auto&it:s)
    {
        int temp=getnum(it);

        if(!node[p][temp])return 0;//如果没有这个节点，直接return 0

        p=node[p][temp];
    }

    return cnt[p];//找到了最后的cnt
}

void solve()
{
    cin>>n>>q;

    string s;
    for(int i=1;i<=n;++i)
    {
        cin>>s;
        insert(s);
    }

    while(q--)
    {
        cin>>s;

        cout<<find(s)<<'\n';
    }

    for(int i=0;i<=tot;++i)
    {  
        for(int j=0;j<65;++j)
            node[i][j]=0;
        cnt[i]=0;
    }

    tot=0;
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int t;

    cin>>t;

    while(t--)
    {
        solve();
    }


    cout<<endl;
    system("pause");
    return 0;
}
