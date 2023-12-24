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
    vector<vector<int>> ans;
    vector<int> path;
    int n,k;

    void dfs(int now,int cnt)
    {
        if(cnt==k)
        {
            ans.push_back(path);
            return;
        }

        for(int i=now;i<=n;++i)
        {
            path.push_back(i);
            dfs(i+1,cnt+1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combine(int n, int k) {
        this->n=n,this->k=k;
        dfs(1,0);
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
