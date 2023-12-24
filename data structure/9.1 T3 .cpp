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
// }*a,*b;

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

// void list_merge(list*&a,list*&b)
// {
//     list * pa=a;
//     list * pb=b;
    
//     while(pa->next&&pb->next)
//     {
//         while(pa->next&&pb->next&&pa->next->data<pb->next->data)
//         {
//             list*temp=pa->next;
//             pa->next=pa->next->next;
//             free(temp);
//             pa=pa->next;
//         }
        
//         while(pa->next&&pb->next&&pa->next->data>pb->next->data)
//             pb=pb->next;

//         while(pa->next&&pb->next&&pa->next->data==pb->next->data)
//             pb=pb->next,pa=pa->next;
//     }
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0),cout.tie(0);

//     list_init(a);
//     list_init(b);

//     list_input(a);
//     list_input(b);

//     list_merge(a,b);

//     show(a);

//     cout<<endl;
//     system("pause");
//     return 0;
// }
