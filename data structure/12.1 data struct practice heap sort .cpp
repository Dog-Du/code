#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=1e6+10;
int a[maxn];//零号元素表示堆的大小
int n;

void push(int a[],int i)
{
    ++a[0];
    for(int j=i/2;j>=1;i=j,j/=2)
    {
        if(a[j]>=a[i])break;
        else
            swap(a[j],a[i]);
    }
}

void pop(int a[])
{
    swap(a[a[0]--],a[1]);

    for(int i=1,j=i*2;j<=a[0];i=j,j*=2)
    {
        if(j+1<=a[0]&&a[j]<a[j+1])++j;

        if(a[i]>a[j])break;
        else
            swap(a[i],a[j]);
    }
}

void heap_sort(int a[])
{
    a[0]=1;
    for(int i=2;i<=n;++i)
        push(a,i);
    
    for(int i=1;i<=n;++i)
        pop(a);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;++i)
        cin>>a[i];

    heap_sort(a);

    for(int i=1;i<=n;++i)
        cout<<a[i]<<' ';

    cout<<endl;
    system("pause");
    return 0;
}
