#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

using namespace std;

const int maxn=3e3+10;

int f[maxn][maxn];


bool dfs(int m,int n)//当大气球m个，小气球n个的时候先手的胜负情况
{

    if(f[m][n]!=-1)return f[m][n];

    if(m==0&&n==0)return f[m][n]=0;//已经用完了，已经输了

    if(n==0&&(m==1||m==2||m==5))return f[m][n]=1;
    if(m==0&&n>0)return f[m][n]=1;


    for(int i=0,x;i<=2;++i)
    {
        if(m-i*i-1>=0&&!dfs(m-i*i-1,n))return f[m][n]=1;
    }

    for(int i=1;i<=n;++i)
        if(!dfs(m,n-i))return f[m][n]=1;
    
    return f[m][n]=0;
}


int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(0),cout.tie(0);
    
    memset(f,-1,sizeof f);

    int n,m;

    cin>>m>>n;

    if(dfs(m,n))cout<<"Alice";
    else cout<<"Bob";

    cout<<endl;
    system("pause");
    return 0;
}
