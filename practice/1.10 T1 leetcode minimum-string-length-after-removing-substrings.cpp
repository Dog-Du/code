#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

//利用栈，O(n);
class Solution {
public:
    int minLength(string s) {
        vector<char> st;
        int cnt=0;

        for(auto&it:s)
        {
            if(it=='B'&&!st.empty()&&st.back()=='A')
                ++cnt,st.pop_back();
            else if(it=='D'&&!st.empty()&&st.back()=='C')
                ++cnt,st.pop_back();
            else
                st.push_back(it);
        }      

        return s.size()-cnt*2;
    }
};

//暴力 O(n^2)
class Solution {
public:
    int minLength(string s) {
        int i=string::npos;

        while((i=s.find("AB"))!=string::npos||
            (i=s.find("CD"))!=string::npos)
        {
            s.erase(s.begin()+i,s.begin()+i+2);
        }

        return s.size();
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    string S="CCCCDDDD";
    Solution one;
    cout<<one.minLength(S);    


    cout<<endl;
    system("pause");
    return 0;
}
