// #include <iostream>

// using namespace std;

// //遍历寻找最小值，保存前面一个节点和本节点
// //时间复杂度：O(n），空间复杂度：O(1）
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

// void reverse(Linklist&L)
// {
//     Linklist pre=L,p=L->next,pretemp=L,temp=L->next;

//     while(temp)
//     {
//         if(temp->data<p->data)
//         {
//             pre=pretemp;
//             p=temp;
//         }

//         pretemp=temp;
//         temp=temp->next;
//     }

//     pre->next=p->next;
//     p->next=L->next;
//     L->next=p;
// }

// void test()
// {
//     Linklist a,b;
//     init_list(a);
//     init(a);

//     reverse(a);
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
