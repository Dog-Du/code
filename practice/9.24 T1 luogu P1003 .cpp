#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=1e4+10;

struct NODE{
    int x1,x2,y1,y2;
}node[maxn];

int n,x,y;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;++i)    
    {
        cin>>node[i].x1>>node[i].y1>>node[i].x2>>node[i].y2;
        node[i].x2+=node[i].x1;
        node[i].y2+=node[i].y1;
    }

    cin>>x>>y;

    for(int i=n;i>=0;--i)
    {
        if(node[i].x1<=x&&node[i].x2>=x
            &&node[i].y1<=y&&node[i].y2>=y)
        {
            cout<<i<<endl;
            system("pause");
            return 0;
        }
    }

    cout<<-1;

    cout<<endl;
    system("pause");
    return 0;
}
