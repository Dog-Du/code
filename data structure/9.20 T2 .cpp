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

// void AmovB(Linklist La,Linklist & Lb,int i,int len,int j)
// {
//     while(La&&i--)La=La->next;

//     if(i>0)return;

//     Linklist pre,p,pa=La;

//     for(pre=Lb,p=Lb->next;p&&--j;pre=p,p=p->next);

//     if(j>0)return;

//     --len;
//     while(pa&&len--)pa=pa->next;

//     if(len>0)return;

//     pre->next=La;
//     pa->next=p;
// }

// void test()
// {
//     Linklist a,b;
//     init_list(a);
//     init_list(b);
//     init(a);
//     init(b);

//     int i,len,j;

//     cin>>i>>len>>j;

//     AmovB(a,b,i,len,j);

//     show(b);
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
