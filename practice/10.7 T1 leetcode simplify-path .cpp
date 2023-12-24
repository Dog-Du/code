#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stack>

#define ll long long

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> st;
        
        int l=0,r=0,n=path.size();

        while(r+1<n&&path[r+1]=='/')++r;

        l=r;
        for(int length;r<n;)
        {
            while(r+1<n&&path[r+1]!='/')
                ++r;

            length=r-l+1;

            if(length==3&&path[r]=='.'&&path[r-1]=='.')
            {
                if(!st.empty())st.pop_back();
            }
            else if(length==2&&path[r]=='.'){}
            else
            {
                st.push_back(path.substr(l,length));
            }

            while(r+1<n&&path[r+1]=='/')++r;
            l=r++;
        }

        string ans;

        for(auto&it:st)ans+=it;

        return (ans.empty()?"/":ans);
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
