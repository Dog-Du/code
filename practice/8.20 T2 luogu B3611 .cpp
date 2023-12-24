#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <bitset>
#define ll long long

using namespace std;


//二进制优化floyd算法，可以达到O(n^2)

bitset<110> a[110];


int main()
{
    int n;

    scanf("%d",&n);

    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int t;
            scanf("%d",&t);
            a[i][j]=t;
        }
    }

    //一种简化，用二进制表示矩阵关系，a[i][j]表示第i行第j列元素
    //其中和floyd一样，中转站在最外侧，之所以可以少一层循环是因为
    //终点站直接被蕴含在结果中了

    for(int j=1;j<=n;++j)
        for(int i=1;i<=n;++i)
            if(a[i][j])
                a[i]|=a[j];
    
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            putchar(a[i][j]+'0'),putchar(' ');
        }
        putchar('\n');
    }

    cout<<endl;
    system("pause");
    return 0;
}

//spfa 求传递闭包
// const int maxn=1e2+10;

// struct EDGE{
//     int next,to;
// }edge[maxn<<2];

// int n,head[maxn],cnt=1,used[maxn],dist[maxn][maxn];

// void add(int x,int y)
// {
//     edge[cnt]={head[x],y};
//     head[x]=cnt++;
// }

// void spfa(int s)
// {
//     for(int i=1;i<=n;++i)used[i]=0;

//     queue<int> que;

//     que.push(s);
//     used[s]=1;

//     while(!que.empty())
//     {
//         int j=que.front();
//         que.pop();
//         used[j]=0;

//         for(int i=head[j],v;i;i=edge[i].next)
//         {
//             v=edge[i].to;

//             if(dist[s][v]==0)
//             {
//                 dist[s][v]=1;

//                 if(!used[v])
//                 {
//                     que.push(v);
//                     used[v]=1;
//                 }
//             }
//         }
//     }
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0),cout.tie(0);

//     cin>>n;

//     for(int i=1,t;i<=n;++i)
//     {
//         for(int j=1;j<=n;++j)
//         {
//             cin>>t;
            
//             if(t==1)add(i,j);
//         }
//     }

//     for(int i=1;i<=n;++i)
//         spfa(i);

//     for(int i=1;i<=n;++i)
//     {
//         for(int j=1;j<=n;++j)
//             cout<<dist[i][j]<<' ';
//         cout<<'\n';
//     }

//     cout<<endl;
//     system("pause");
//     return 0;
// }
//floyd求传递闭包
// const int maxn=1e2+10;

// int num[maxn][maxn];
// int n;

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0),cout.tie(0);

//     cin>>n;

//     for(int i=1;i<=n;++i)    
//         for(int j=1;j<=n;++j)
//             cin>>num[i][j];

//     for(int k=1;k<=n;++k)
//         for(int i=1;i<=n;++i)
//             for(int j=1;j<=n;++j)
//                 num[i][j]=num[i][j]|(num[i][k]&num[k][j]);
    
//     for(int i=1;i<=n;++i)
//     {
//         for(int j=1;j<=n;++j)
//             cout<<num[i][j]<<' ';
        
//         cout<<'\n';
//     }

//     cout<<endl;
//     system("pause");
//     return 0;
// }
