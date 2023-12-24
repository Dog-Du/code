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
//     list* next;

//     void init()
//     {
//         int n;
//         cin>>n;

//         list *p =this;

//         for(int i=0;i<n;++i)
//         {
//             list*temp=new list;

//             cin>>temp->data;
//             temp->next=NULL;
//             p->next=temp;
//             p=p->next;
//         }
//     }
// }a,b,c;

// void merge_list(list & a,list & b,list & c)
// {
//     list * pa=&a;
//     list * pb=&b;
//     list * pc=&c;

//     while(pa&&pb)
//     {
//         if(pa->data<=pb->data)
//         {
//             pc->next=pa;
//             pc=pa;

//             if(pa->data==pb->data)
//                 pb=pb->next;
            
//             pa=pa->next;
//         }
//         else
//         {
//             pc->next=pb;
//             pc=pb;
//             pb=pb->next;
//         }
//     }

//     pc->next=(pa==NULL?pb:pa);
// }

// void show(list & a)
// {
//     list * it=a.next;

//     while(it)
//     {  
//         cout<<it->data<<' ';
//         it=it->next;
//     }

//     cout<<endl;
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0),cout.tie(0);

//     a.init();
//     b.init();

//     merge_list(a,b,c);

//     show(c);

//     cout<<endl;
//     system("pause");
//     return 0;
// }
