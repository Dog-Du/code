// #include <iostream>

// using namespace std;

// //基本思想：在有序数列中使用快慢双指针
// //l指向去重之后部分的后一个位置，表示下一个元素的位置
// //r指向后面的数据，如果r->data==r->next->data说明重复，直接让r指向下一个元素
// //最后l指向去重之后的数列的后一个指针，把l前一个指针的next置空，并将l及其之后的删除即可
// //时间效率：O(n) 空间效率：O(1)

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

// //快慢双指针去重
// void DelEqu(Linklist & list)
// {
//     Linklist l=list->next,r=list->next,temp;

//     while(r!=NULL)
//     {
//         if(r->next!=NULL&&r->next->data==r->data)
//             r=r->next;
//         else
//         {
//             //在这个地方temp用来保存l的上一个指针，用于该循环结束之后置空l的上一个指针的next

//             temp=l;
//             l->data=r->data;
//             l=l->next;
//             r=r->next;
//         }
//     }

//     //将l的上一个指针的next置空
//     temp->next=NULL;

//     //删除l及其之后的部分
//     while(l!=NULL)
//     {
//         temp=l->next;
//         free(l);
//         l=temp;
//     }

//     //置空，防止野指针
//     temp=NULL;
//     r=NULL;

//     return ;
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
//     Linklist list;

//     init_list(list);
//     init(list);

//     show(list);

//     DelEqu(list);

//     show(list);

//     Linklist temp;

//     while(list!=NULL)
//     {
//         temp=list->next;

//         free(list);

//         list=temp;
//     }

//     temp=NULL;
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
