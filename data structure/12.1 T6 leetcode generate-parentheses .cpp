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
    int tot;
    vector<string> ans;
    string path;

    void dfs(int now,int cnt)
    {
        if(now==tot)
        {
            ans.push_back(path);
            return;
        }
        
        if(now+cnt<tot)
        {
            path.push_back('(');
            dfs(now+1,cnt+1);
            path.pop_back();
        }

        if(cnt>0)
        {
            path.push_back(')');
            dfs(now+1,cnt-1);
            path.pop_back();
        }
    }

public:
    vector<string> generateParenthesis(int n) {
        tot=2*n;
        path.push_back('(');
        dfs(1,1);
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
