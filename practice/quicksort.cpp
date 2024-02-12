#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>

#define ll long long

using namespace std;

vector<int> vec;
int n;



void quicksort(int *first,int *last)
{

}

//这种quicksort写法算是原教义quicksort了，
//每次能都保证pivot在应该在的位置。

// void quicksort(int L,int R)
// {
//     if(L>=R)return;

//     int l=L,r=R;
//     //先把pivot放到最左边，然后l从第二个开始找位置
//     swap(vec[l++],vec[rand()%(R-L+1)+L]);

//     while(l<=r)
//     {
//         //虽然没想到为什么，但是确实是，如果不加l<=r的话，P1177会RE，应该是越界了。
//         while(l<=r&&vec[l]<vec[L])++l;
//         while(l<=r&&vec[r]>vec[L])--r;
//         if(l>=r)break;
//         //这里处理了上面相减可能导致的l>r的情况，这个时候直接break，不然可能导致r左边的不全都是小于等于的pivot的，比如：1 2 3 4 5抽取到3的时候
//         swap(vec[l++],vec[r--]);
//     }

//     //因为vec[r]<=pivot所以和它进行交换是没有任何问题的。
//     //这个时候r就是pivot所在位置，r-1都是小于等于的，r+1都是大于等于的。
//     swap(vec[L],vec[r]);
//     quicksort(L,r-1);
//     quicksort(r+1,R);
// }

//这样不行，分成了左右两边一
void quicksort(int L,int R,vector<int>&vec)
{
    if(L>=R)return;
    int pivot=(L+R>>1),l,r;
    pivot=vec[pivot];
    
    for(l=L,r=L;r<=R;++r)
        if(vec[r]<=pivot)
            swap(vec[l++],vec[r]);
    
    quicksort(L,l-1,vec);
    quicksort(l,R,vec);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>n;
    vec.resize(n);
    srand(114514);

    for(int i=0,t;i<n;++i)
    {
        cin>>t;
        vec[i]=t;
    }

    quicksort(0,n-1,vec);

    for(int i=0;i<n;++i)
        cout<<vec[i]<<' ';

    cout<<endl;
    system("pause");
    return 0;
}
