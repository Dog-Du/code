#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>

#define ll long long

using namespace std;

class Solution {
private:

    bool dfs(string &x,string &y,double&ans,map<string,vector<pair<string,double>>> &mp,unordered_set<string>&se)
    {
        if(x==y)return true;
        se.emplace(x);

        for(auto&iter:mp[x])
        {
            ans*=iter.second;
            if(!se.count(iter.first)&&dfs(iter.first,y,ans,mp,se))return true;
            ans/=iter.second;
        }

        se.erase(se.find(x));

        return false;
    }

public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        map<string,vector<pair<string,double>>> mp;
        unordered_set<string> se,ch;

        vector<double> vec;

        int n=equations.size(),m=queries.size();

        for(int i=0;i<n;++i)
        {
            ch.emplace(equations[i].front());
            ch.emplace(equations[i].back());

            mp[equations[i].front()].push_back({equations[i].back(),values[i]});
            mp[equations[i].back()].push_back({equations[i].front(),1/values[i]});
        }

        double ans;

        for(int i=0;i<m;++i)
        {
            ans=1;

            if(!ch.count(queries[i].front())||!ch.count(queries[i].back()))
            {
                vec.push_back(-1);
                continue;
            }

            if(queries[i].front()==queries[i].back())
            {
                vec.push_back(1);
                continue;
            }
            if(dfs(queries[i].front(),queries[i].back(),ans,mp,se))
                vec.push_back(ans);
            else   
                vec.push_back(-1);
            se.clear();
        }

        return vec;
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
