// #include <iostream>
// #include <cmath>
// #include <string>
// #include <cstring>
// #include <vector>
// #include <algorithm>

// #define ll long long

// using namespace std;

// //基本思想:遍历，然后temp指向p的上一个，

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

// void Del(int l,int r,Linklist&list)
// {
//     if(l>r)return;

//     Linklist p=list->next,temp=list;

//     while(p!=NULL)
//     {
//         if(p->data>=l&&p->data<=r)
//         {
//             temp->next=p->next;
//             free(p);
//             p=temp->next;
//         }
//         else
//             p=p->next,temp=temp->next;
//     }
// }

// void show(Linklist&list)
// {
//     Linklist p=list;

//     while(p->next!=NULL)
//     {
//         cout<<p->next->data<<' ';
//         p=p->next;
//     }
    
//     cout<<endl;
//     return;
// }


// void test()
// {
//     Linklist p,temp;
//     init_list(p);
//     init(p);

//     int l,r;
//     cin>>l>>r;

//     Del(l,r,p);

//     show(p);


//     while(p!=NULL)
//     {
//         temp=p->next;

//         free(p);

//         p=temp;
//     }
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
