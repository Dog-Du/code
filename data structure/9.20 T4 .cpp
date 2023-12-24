// #include <iostream>

// using namespace std;

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

// void MergeList(Linklist&LA,Linklist LB)
// {
//     Linklist p1=LA->next,pre=LA,p2=LB->next;

//     while(p1)
//     {
//         if(p1->next&&p1->data==p1->next->data)
//         {
//             pre=p1->next;
//             p1->next=p1->next->next;
//             free(pre);
//         }
//         else
//             p1=p1->next;
//     }

//     p1=LA->next,pre=LA;

//     while(p1&&p2)
//     {
//         if(p1->data>p2->data)
//         {
//             Linklist temp=p2->next;
//             pre->next=p2;
//             p2->next=p1;
//             pre=p2;
//             p2=temp;
//         }
//         else if(p1->data<p2->data)
//         {
//             pre=p1;
//             p1=p1->next;
//         }
//         else
//         {
//             pre->next=p1->next;
//             p2=p2->next;
//             p1=p1->next;
//         }
//     }

//     if(!p1)pre->next=p2;
// }

// void test()
// {
//     Linklist a,b;

//     init_list(a);
//     init_list(b);
//     init(a);
//     init(b);

//     MergeList(a,b);

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
