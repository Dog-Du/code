// #include <iostream>
// #include <cmath>
// #include <string>
// #include <cstring>
// #include <vector>
// #include <algorithm>

// #define ll long long

// using namespace std;

// //基本思想：快慢双指针
// //l每次移动一格，r每次移动两个即可，
// //但是我不理解，如果n为偶数中间位置是什么？
// //所以我写的是返回中位数的函数
// //时间复杂度：O(n) 而且是 n/2  空间复杂度：O(1)

// typedef struct LIST{
//     LIST *next;
//     int data;
// }*Linklist;

// void init_list(Linklist & list)
// {
//     Linklist p= new LIST;
//     list=p;
//     list->next=NULL;
// }

// //尾插法初始化
// void init(Linklist&list)
// {
//     int n,x;
//     Linklist p=list;

//     cin>>n;

//     while(n--)
//     {
//         cin>>x;

//         Linklist temp=new LIST;
//         temp->next=NULL;
//         temp->data=x;

//         p->next=temp;
//         p=p->next;
//     }
// }

// double find_mid_data(Linklist&list)
// {
//     Linklist l=list->next,r=list->next;

//     while(r->next!=NULL&&r->next->next!=NULL)
//     {
//         r=r->next->next;
//         l=l->next;
//     }

//     //如果是偶数，返回中位数

//     if(r->next!=NULL)
//         return 1.0*(l->data+l->next->data)/2;
//     else
//         return l->data;
// }

// void test()
// {
//     Linklist p;

//     init_list(p);
//     init(p);

//     cout<<find_mid_data(p)<<endl;

//     Linklist temp;

//     while(p!=NULL)
//     {
//         temp=p->next;

//         free(p);

//         p=temp;
//     }

//     temp=NULL;
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0),cout.tie(0);

//     int n;
//     cin>>n;

//     while(n--)
//     {
//         test();
//     }


//     cout<<endl;
//     system("pause");
//     return 0;
// }
