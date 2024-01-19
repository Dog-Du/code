#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class Solution {
private:
    int n,m,k,ans=0;
    vector<vector<int>>* a;
    vector<int> path;

    int check(vector<vector<int>>& a,vector<int>&path)
    {
        int p=0,s=path.size();
        vector<bool> used(n,false);
        int cnt=0;

        for(int i=0;i<m;++i)
        {
            if(p<s&&i==path[p])
                ++p;
            else
            {
                for(int j=0;j<n;++j)
                {
                    if(a[j][i]==1)
                        cnt+=!used[j],used[j]=1;
                }               
            }
        }

        return n-cnt;
    }

    void dfs(int x,int start)
    {
        if(x==k)
        {
            ans=max(ans,check(*a,path));
            return;
        }

        for(int i=start;i<m;++i)
        {
            path.push_back(i);
            dfs(x+1,i+1);
            path.pop_back();
        }
    }

public:
    int maximumRows(vector<vector<int>>& matrix, int numSelect) {
        n=matrix.size(),m=matrix.front().size(),k=numSelect;
        a=&matrix;

        dfs(0,0);

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
