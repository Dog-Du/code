#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include<unordered_map>
#define ll long long

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
       unordered_map<string,vector<string>> mp;
        vector<vector<string>> ans;

       for(auto &it:strs)
       {
            string key=it;
            sort(key.begin(),key.end());
            mp[key].push_back(it);
       }

        for(auto&it:mp)
            ans.push_back(it.second);
        
        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    vector<string> ss={"eat","tea","tan","ate","nat","bat"};
    Solution one;
    one.groupAnagrams(ss);

    cout<<endl;
    system("pause");
    return 0;
}
