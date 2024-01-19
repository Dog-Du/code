#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=1e5+10,InsertMin=16,BufferN=33;

int a[maxn],buffer[BufferN];
int n;

void print(int *first,int *last)
{
    while(first!=last)
        cout<<*(first++)<<' ';
    cout<<endl;
}

void InsertSort(int *first,int *last)//插入排序
{
    for(int *i=first,*j;i!=last;++i)
        for(j=i;j!=first&&*j<*(j-1);--j)
            swap(*j,*(j-1));
    
}

void reverse(int *first,int *last)//翻转
{
    --last;
    while(last-first>0)
        swap(*(last--),*(first++));
}

void rotate(int *first,int *middle,int *last)//以middle为中心，翻转位置
{
    reverse(first,last);

    int *new_middle=first+(last-middle);

    reverse(first,new_middle);
    reverse(new_middle,last);
}

void MergeWithBuffer(int *first,int *middle,int *last,int buffer[])
{
    int *p1=first,*p2=middle,*p=buffer;

    while(p1!=middle&&p2!=last)
    {
        if(*p1<=*p2)
            *(p++)=std::move(*(p1++));
        else
            *(p++)=std::move(*(p2++));
    }

    while(p1!=middle)
        *(p++)=std::move(*(p1++));
    
    while(p2!=last)
        *(p++)=std::move(*(p2++));
    
    p=buffer;

    while(first!=last)
        *(first++)=std::move(*(p++));
}

//感觉上这个函数的时间复杂度可能在 O(n+m) 到 O((n+m)log(n+m)) 之间，常数比较原本的mergesort大
void MergeWithoutBuffer(int *first,int *middle,int *last)//不需buffer的归并,核心代码.
{
    int len1=middle-first,len2=last-middle;

    if(len1==0||len2==0)return;

    if(len1+len2==2)
    {
        if(*middle<*first)
            swap(*middle,*first);
        return;
    }

    if(len1+len2<BufferN)
    {
        InsertSort(first,last);
        //MergeWithBuffer(first,middle,last,buffer);
        return;
    }

    int len11=0,len22=0;
    int *first_cut=first,*second_cut=middle;

    if(len1>len2)
    {
        len11=len1/2;
        first_cut+=len11;
        second_cut=lower_bound(middle,last,*first_cut);
        len22=second_cut-middle;
    }
    else
    {
      len22=len2/2;
      second_cut+=len22;
      first_cut=upper_bound(first,middle,*second_cut);
      len11=first_cut-first;
    }

    rotate(first_cut,middle,second_cut);
    //print(first,last);
    int *new_middle=first_cut+(second_cut-middle);
    
    //分成了两部分.
    MergeWithoutBuffer(first,first_cut,new_middle);
    MergeWithoutBuffer(new_middle,second_cut,last);
}

void MergeSortWithoutBuffer(int *first,int *last)//归并排序
{
    if(last-first<InsertMin)
    {
        InsertSort(first,last);
        return;
    }

    int *midlle=first+(last-first)/2;
    MergeSortWithoutBuffer(first,midlle);
    MergeSortWithoutBuffer(midlle,last);

    MergeWithoutBuffer(first,midlle,last);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;++i)    
        cin>>a[i];
    
    MergeSortWithoutBuffer(a+1,a+1+n);

    print(a+1,a+n+1);

    cout<<endl;
    system("pause");
    return 0;
}