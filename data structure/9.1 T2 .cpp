// #include <iostream>
// #include <cmath>
// #include <string>
// #include <cstring>
// #include <vector>
// #include <algorithm>

// #define ll long long

// using namespace std;

// struct list
// {
//     int data;
//     list * next;
// }*a,*b,*c;

// void list_init(list * & x)
// {
//     x=new list;
//     x->next=NULL;
// }

// void list_input(list*&x)
// {
//     list*p=x;
//     int n;
//     cin>>n;

//     for(int i=0;i<n;++i)
//     {
//         list * temp=new list;
//         cin>>temp->data;
//         temp->next=NULL;
//         p->next=temp;
//         p=p->next;
//     }

// }

// void list_merge(list *& a,list*&b,list*&c)
// {
//     list*pa=a->next;
//     list*pb=b->next;
//     list*pc=c=a;

//     while(pa&&pb)
//     {
//         if(pa->data<=pb->data)
//         {
//             pc->next=pa;
//             pa=pa->next;
//             pc=pc->next;
//         }
//         else
//         {
//             pc->next=pb;
//             pb=pb->next;
//             pc=pc->next;
//         }
//     }

//     pc->next=(pa?pa:pb);
// }

// void show(list*&x)
// {
//     list * p=x->next;

//     while(p)
//     {
//         cout<<p->data<<' ';
//         p=p->next;
//     }
//     cout<<endl;
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0),cout.tie(0);

//     list_init(a);
//     list_init(b);

//     list_input(a);
//     list_input(b);

//     list_merge(a,b,c);

//     show(c);
//     show(a);
//     show(b);
    
//     cout<<endl;
//     system("pause");
//     return 0;
// }
