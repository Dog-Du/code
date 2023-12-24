#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

#define ll long long

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for(auto&it:s)
        {
            if(it=='('||it=='['||it=='{')st.push(it);
            else if(it==')'&&(st.empty()||st.top()!='('))return false;
            else if(it==']'&&(st.empty()||st.top()!='['))return false;
            else if(it=='}'&&(st.empty()||st.top()!='{'))return false;
            else st.pop();
        }

        return st.empty();
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
