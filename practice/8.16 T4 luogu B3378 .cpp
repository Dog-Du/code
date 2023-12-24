#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

#define ll long long

using namespace std;

struct HEAP{
    int num[(int)1e6+10];
    int p=1;

    void push(int x)
    {
        num[p++]=x;

        //从堆低开始调整

        for(int i=p-1;i>1;i/=2){
            if(num[i/2]>num[i])swap(num[i/2],num[i]);
            else break;
        }
    }

    void pop()
    {
        swap(num[1],num[--p]);

        //交换堆底和堆顶后，从堆顶开始调整


        for(int i=1,t;i<=p-1;i=t)
        {
            t=2*i;

            if(t+1<=p-1&&num[t]>num[t+1])++t;//把最小的放在上面

            if(t<=p-1&&num[i]>num[t])swap(num[i],num[t]);
            else 
                break;
            
        }
    }

    int query()
    {
        return num[1];
    }

}heap;


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
            int x;

            cin>>x;

            heap.push(x);
        }
        else if(op==2)
        {
            cout<<heap.query()<<'\n';
        }
        else if(op==3)
        {
            heap.pop();
        }
    }

    cout<<endl;
    system("pause");
    return 0;
}
