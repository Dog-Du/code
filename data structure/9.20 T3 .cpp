// #include <iostream>

// using namespace std;

// //基本思想：把前K个节点的next指向翻转，然后把头结点指向前K个节点的最后一个，把第一个元素next指向后面的元素
// //时间复杂度:O(k) 空间复杂度 ：O(1）
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

// void reverse_k(Linklist& L,int k)
// {
//     Linklist pre=L,p=L->next,temp;

//     while(p&&k--)
//     {
//         temp=p->next;
//         p->next=pre;

//         pre=p;
//         p=temp;
//     }

//     L->next->next=p;
//     L->next=pre;
// }

// void test()
// {
//     Linklist a,b;
//     init_list(a);
//     init(a);

//     int k;
//     cin>>k;

//     reverse_k(a,k);
//     show(a);
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0),cout.tie(0);

//     int t;
//     cin>>t;

//     while(t--)
//     {
//         test();
//     }
    

//     cout<<endl;
//     system("pause");
//     return 0;
// }
