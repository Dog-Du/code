// #include <iostream>
// #include <cmath>
// #include <string>
// #include <cstring>
// #include <vector>
// #include <algorithm>

// #define ll long long

// using namespace std;

// //基本思想：快慢双指针
// //l指向去重之后部分的后一个位置，表示下一个元素的位置
// //r指向后面的数据，如果num[r]>=L&&num[r]<=R表明需要删去，直接让r指向下一个元素
// //最后l指向最后一个元素的后一个位置，代表长度，需要进行返回
// //时间复杂度：稳定的O(n) 空间复杂度:O(1)
// //但是这个跟递增不递增没关系，不需要这个条件


// //想了想怎么利用递增这个条件
// //基本思想：二分+reverse
// //得到一个奇怪的想法，可能比较慢，但也可以实现：
// //既然递增，用二分找到[x,y]对应位置,需要删除则是[l,r],
// //然后reverse l及其后半部分然后再reverse原来的r后面的部分
// //这样就把后半部分顺序再变了回去，
// //时间复杂度:不稳定的O(2*logn + n) 空间复杂度：O(1)
// //但是如果前面小于x的数字很多的话而后面的大于y的数字较少，这个算法会快很多

// void init(int n,int num[])
// {
//     for(int i=0;i<n;++i)
//         cin>>num[i];
// }

// //快慢双指针
// int Del(int L,int R,int length,int num[])
// {
//     int l=0,r=0;

//     while(r<length)
//     {
//         if(num[r]>=L&&num[r]<=R)
//             ++r;
//         else
//             num[l++]=num[r++];
//     }

//     return l;
// }

// void reverse(int l,int r,int num[])
// {
//     while(l<r)
//         swap(num[l++],num[r--]);
// }

// //二分+reverse方法
// int otheranswer(int L,int R,int length,int num[])
// {
//     int l=0,r=length-1,mid,p1=-1,p2=-1;

//     //二分查找两个端点

//     while(l<=r)
//     {
//         mid=l+r>>1;

//         if(num[mid]>=L)
//             r=mid-1,p1=mid;
//         else
//             l=mid+1;
//     }

//     l=0,r=length-1;

//     while(l<=r)
//     {
//         mid=l+r>>1;

//         if(num[mid]<=R)
//             l=mid+1,p2=mid;
//         else
//             r=mid-1;
//     }

//     //找到断点
//    // cout<<p1<<' '<<p2<<endl;

//     //reverse后半部分
//     reverse(p1,length-1,num);

//     //reverse符合要求的部分
//     reverse(p1,p1+length-1-p2-1,num);

//     //返回删除之后的长度
//     return p1+length-1-p2;
// }

// void test()
// {
//     int n,L,R;
//     cin>>n;

//     int *num=new int[n];

//     init(n,num);

//     cin>>L>>R;

//    // n=Del(L,R,n,num);

//     n=otheranswer(L,R,n,num);

//     for(int i=0;i<n;++i)
//         cout<<num[i]<<' ';
    
//     cout<<endl;

//     delete [] num;

//     return;
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0),cout.tie(0);

//     int n;
//     cin>>n;

//     while(n--)
//         test();


//     cout<<endl;
//     system("pause");
//     return 0;
// }
