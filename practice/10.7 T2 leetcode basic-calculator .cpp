#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class Solution {
public:
    int calculate(string s) {
        vector<long long> num;
        vector<char> ch;

        num.push_back(0);

        for(long long i=0,flag=0,temp=0;i<s.size();++i)
        {
            if(s[i]==' ')continue;

            flag=0,temp=0;

            while(s[i]>='0'&&s[i]<='9')
                flag=1,temp=temp*10+s[i++]-'0';
            
            if(flag)
            {
                num.push_back(temp);
                --i;
            }
            else
            {
                if(s[i]=='(')
                {
                    ch.push_back('(');

                    for(int j=i+1;j<s.size();++j)
                        if(s[j]==' ')
                            continue;
                        else if(s[j]>'9'||s[j]<'0')
                        {    num.push_back(0);break; }
                        else
                            break;

                }
                else 
                {
                    while(!ch.empty()&&ch.back()!='(')
                    {
                        int num2=num.back();
                        num.pop_back();
                        int num1=num.back();
                        num.pop_back();

                        if(ch.back()=='+')num.push_back(num1+num2);
                        else  num.push_back(num1-num2);

                        ch.pop_back();
                    }

                    if(s[i]==')')ch.pop_back();
                    else ch.push_back(s[i]);
                }
            }
        }

        while(!ch.empty())
                    {
                        int num2=num.back();
                        num.pop_back();
                        int num1=num.back();
                        num.pop_back();

                        if(ch.back()=='+')num.push_back(num1+num2);
                        else  num.push_back(num1-num2);

                        ch.pop_back();
                    }

        return num.back();
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    string s;
    cin>>s;

    Solution one;

   cout<< one.calculate(s);


    cout<<endl;
    system("pause");
    return 0;
}
