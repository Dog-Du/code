#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

#define ll long long

using namespace std;

struct QUEUE{
    int num[(int)1e6+10];
    int l=0,r=l;

    int size()
    {
        return r-l;
    }

    bool empty()
    {
        if(size()>0)return false;
        return true;
    }

    void push(int x)
    {
        num[r++]=x;
    }

    void pop()
    {
        if(empty())cout<<"ERR_CANNOT_POP\n";
        else
            ++l;
    }

    void query()
    {
        if(empty())cout<<"ERR_CANNOT_QUERY\n";
        else
            cout<< num[l]<<'\n';
    }
}queue;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    
    int n;

    cin>>n;

    while(n--)
    {
        int op;

        cin>>op;

        if(op==1)
        {
            int num;

            cin>>num;

            queue.push(num);
        }
        else if(op==2)
        {
            queue.pop();
        }
        else if(op==3)
        {
            queue.query();
        }
        else if(op==4)
        {
            cout<<queue.size()<<'\n';
        }

    }

    cout<<endl;
    system("pause");
    return 0;
}
