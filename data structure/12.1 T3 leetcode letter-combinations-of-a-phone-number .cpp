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
    string ch[10]={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

    void dfs(int now,string&s,vector<string>&ans,string&digits)
    {
        if(now==digits.size())
        {
            ans.push_back(s);
            return;
        }

        for(auto&it:ch[digits[now]-'0'])
        {
            s.push_back(it);
            dfs(now+1,s,ans,digits);
            s.pop_back();
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        if(digits.size()==0)return {};
        vector<string> ans;
        string s;
        dfs(0,s,ans,digits);
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
