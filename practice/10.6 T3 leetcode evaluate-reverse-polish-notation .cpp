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

    int func(string&s)
    {
        int ans=0;
        int flag=1;

        for(auto&it:s)
            if(it>='0'&&it<='9')
                ans=ans*10+it-'0';
            else 
                flag=-1;
        
        return ans*flag;
    }

    void pop(stack<int> &st,int &n)
    {
        n=st.top();
        st.pop();
    }

    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        int num1,num2;

        for(auto&it:tokens)
        {
            if(it=="+")
            {
                pop(st,num1);
                pop(st,num2);
                st.push(num1+num2);
            }
            else if(it=="-")
            {
                pop(st,num2);
                pop(st,num1);
                st.push(num1-num2);
            }
            else if(it=="*")
            {
                pop(st,num2);
                pop(st,num1);
                st.push(num1*num2);
            }
            else if(it=="/")
            {
                pop(st,num2);
                pop(st,num1);
                st.push(num1/num2);
            }
            else
                st.push(func(it));
        }

        return st.top();
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
