#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=1e5+10;

struct NODE{
    int val,id;
    bool operator<(const NODE&other)const{
        return val==other.val?id>other.id:val>other.val;
    }
}node[maxn];


priority_queue<NODE> que[maxn];
int pre[maxn];
bool is_del[maxn];

int find(int x)
{
    return x==pre[x]?x:pre[x]=find(pre[x]);
}



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

#ifdef LOCAL
    clock_t c1 = clock();
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif

//-------------------------------------------------

    int n,m;
    cin>>n>>m;

    for(int i=1;i<=n;++i)
    {
        cin>>node[i].val;
        node[i].id=i;
        que[i].push(node[i]);
        pre[i]=i;
    }


    while(m--)
    {
        int op,x,y;
        cin>>op;

        if(op==1)
        {
            cin>>x>>y;

            int fx=find(x),fy=find(y);
            if(fx==fy||is_del[x]||is_del[y])continue;

            //小的合并进入大的，时间复杂度为 logn*logn
            if(que[fx].size()<que[fy].size())
            {
                pre[fx]=fy;

                while(!que[fx].empty())
                {
                    que[fy].push(que[fx].top());
                    que[fx].pop();
                }
            }
            else
            {
                pre[fy]=fx;
                
                while(!que[fy].empty())
                {
                    que[fx].push(que[fy].top());
                    que[fy].pop();
                }
            }
        }
        else
        {
            cin>>x;
            int fx=find(x);

            if(is_del[x]||que[fx].empty())
                cout<<"-1\n";
            else
            {
                is_del[que[fx].top().id]=true;
                cout<<que[fx].top().val<<'\n';
                que[fx].pop();
            }

        }
    }
//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
