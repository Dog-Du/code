#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

#define ll long long

using namespace std;

const int maxn=1e5+10;

int n;
int a[maxn];

void quicksort(int L,int R)
{
    if(L>=R)return;

    int pivot=rand()%(R-L+1)+L,l=L,r=R;
    pivot=a[pivot];

    while(l<=r)
    {
        while(a[l]<pivot)++l;
        while(a[r]>pivot)--r;

        if(l<=r)swap(a[l++],a[r--]);
    }

    quicksort(L,r);
    quicksort(l,R);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;++i)cin>>a[i];

    quicksort(1,n);

    for(int i=1;i<=n;++i)cout<<a[i]<<' ';
    
    cout<<endl;
    system("pause");
    return 0;
}
