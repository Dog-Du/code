#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

#define ll long long

using namespace std;

//dj算法
class Solution {
private:
    int n,m;
    int dx[2]={1,0};
    int dy[2]={0,1};

    int getid(pair<int,int> pos)
    {
        return pos.first*m+pos.second;
    }

    pair<int,int> getpos(int id)
    {
        return make_pair(id/m,id%m);
    }

public:
    int minPathSum(vector<vector<int>>& grid) {
        n=grid.size(),m=grid.front().size();

        vector<int> dis(n*m,(int)1e9);
        vector<bool> used(n*m,false);
        dis[0]=0;
        
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> que;

        que.push({0,0});

        pair<int,int> j,now;

        while(!que.empty())
        {
            j=que.top();
            que.pop();

            if(used[j.second])continue;
            used[j.second]=1;

            now=getpos(j.second);

            for(int i=0,nx,ny,nid;i<2;++i)
            {
                nx=now.first+dx[i];
                ny=now.second+dy[i];
                nid=getid(make_pair(nx,ny));

                if(nid<0||nid>=n*m||used[nid])continue;

                if(dis[nid]>dis[j.second]+grid[now.first][now.second])
                {
                    dis[nid]=dis[j.second]+grid[now.first][now.second];
                    if(!used[nid])
                        que.push({dis[nid],nid});
                }
            }

            // for(int i=0;i<n;++i)
            // {
            //     for(int j=0;j<m;++j)
            //     {
            //         cout<<dis[i*m+j]<<' ';
            //     }
            //     cout<<endl;
            // }
        }

        return dis.back()+grid.back().back();
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    Solution one;
    vector<vector<int>> vec={{1,2,3},{4,5,6}};
    one.minPathSum(vec);


    cout<<endl;
    system("pause");
    return 0;
}
