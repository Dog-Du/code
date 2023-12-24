#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

#define ll long long

using namespace std;


const int maxn=1e6+10;

struct STACK{
    unsigned ll num[maxn]={0};
    int p=0;

    void push(unsigned ll x)
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

    void query()
    {
        if(p==0)
        {
            cout<<"Anguei!\n";
            return;
        }
        else
        {
           cout<<num[p-1]<<'\n';
           return;
        }
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


void solve()
{
    int n;

    cin>>n;

    while(n--)
    {
        string t;
        
        cin>>t;

        if(t=="push")
        {
            unsigned ll x;

            cin>>x;

            stack.push(x);
        }
        else if(t=="pop")
        {
            stack.pop();
        }
        else if(t=="query")
        {
            stack.query();
        }
        else if(t=="size")
        {
            cout<<stack.size()<<'\n';
        }

    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    
    int t;

    cin>>t;

    while(t--)
    {
        solve();
        stack.clear();
    }

    cout<<endl;
    system("pause");
    return 0;
}
