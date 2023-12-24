#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <algorithm>

#define ll long long

using namespace std;

class Solution {
private:
    int __gcd(int a,int b)
    {
        return b==0?a:__gcd(b,a%b);
    }

public:
    int maxPoints(vector<vector<int>>& points) {
        int ans=0,n=points.size();
        if(n<=2)return n;

        for(int i=0;i<n;++i)
        {
            //统计以points[i]为起点的各个直线上的点的个数

            unordered_map<int,int> mp;//first是直线的编号，second是点的个数

            for(int j=i+1;j<n;++j)
            {
                int x=points[i].front()-points[j].front();
                int y=points[i].back()-points[j].back();

                if(x==0)y=1;
                else if(y==0)x=1;
                else
                {
                    if(y<0)
                        x=-x,y=-y;
                    
                    int g=__gcd(abs(x),abs(y));
                    x/=g,y/=g;
                }

                //因为已知起点，所以可以由dx,dy唯一确定一条直线。
                mp[y+x*20001]++;
            }

            int maxn=0;

            for(auto&it:mp)
                maxn=max(maxn,it.second+1);//算上本身，所以需要加1
            
            ans=max(ans,maxn);
        }
        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    


    cout<<endl;
    system("pause");
    return 0;
}
