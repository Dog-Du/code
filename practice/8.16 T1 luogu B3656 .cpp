#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include<list>

#define ll long long

using namespace std;

const int maxn=1e6+10;

list<ll> li[maxn];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    
    int q;

    cin>>q ;

    
    while(q--)
    {
        string s;

        cin>>s;

        if(s=="pop_back")
        {
            int x;
            cin>>x;

            if(!li[x].empty())li[x].pop_back();
        }
        else if(s=="push_back")
        {
            int x;
            ll num;

            cin>>x>>num;

            li[x].push_back(num);
        }
        else if(s=="push_front")
        {
            int x;
            ll num;

            cin>>x>>num;

            li[x].push_front(num);
        }
        else if(s=="pop_front")
        {
            int x;

            cin>>x;

            if(!li[x].empty())li[x].pop_front();
        }
        else if(s=="size")
        {
            int x;

            cin>>x;

            cout<<li[x].size()<<'\n';
        }
        else if(s=="front")
        {
            int x;

            cin>>x;

            if(!li[x].empty())cout<<li[x].front()<<'\n';
        }
        else if(s=="back")
        {
            int x;

            cin>>x;

            if(!li[x].empty())cout<<li[x].back()<<'\n';
        }
    }

    cout<<endl;
    system("pause");
    return 0;
}
