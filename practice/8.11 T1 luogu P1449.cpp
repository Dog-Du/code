#include <iostream>
#include <cmath>
#include <string>
#include <cstring>


#define ll long long

using namespace std;

const int maxn=1e6+10;

struct STACK{
    ll num[maxn]={0};
    int p=0;

    void push(ll x)
    {
        num[p++]=x;
    }

    void pop()
    {
        if(p==0)
        {
            cout<<"Empty\n";
        }
        else
        {
            --p;
        }
    }

    ll query()
    {
       return num[p-1];
    }

    int size()
    {
        return p;
    }

    void clear()
    {
        p=0;
    }
}stack;


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    
    char ch;

    while(cin>>ch)
    {
        if(ch=='.'||ch=='@')continue;

        if(ch>='0'&&ch<='9')
        {
            ll x=ch-'0';

            cin>>ch;
            while(ch!='.')
            {
                x=x*10+ch-'0';
                cin>>ch;
            }

            stack.push(x);
        }

        if(ch=='+')
        {
            ll num2=stack.query();
            stack.pop();
            ll num1=stack.query();
            stack.pop();

            stack.push(num1+num2);
        }
        else if(ch=='-')
        {
            ll num2=stack.query();
            stack.pop();
            ll num1=stack.query();
            stack.pop();

            stack.push(num1-num2);
        }
        else if(ch=='*')
        {
            ll num2=stack.query();
            stack.pop();
            ll num1=stack.query();
            stack.pop();

            stack.push(num1*num2);
        }
        else if(ch=='/')
        {
            ll num2=stack.query();
            stack.pop();
            ll num1=stack.query();
            stack.pop();

            stack.push(num1/num2);
        }
    }



    cout<<stack.query()<<endl;
    system("pause");
    return 0;
}
