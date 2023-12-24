#include <iostream>
#include <list>

#define ll long long

using namespace std;

typedef struct LIST{
    int data;
    LIST*next;
}*Linklist;

void init_list(Linklist & list)
{
    Linklist p= new LIST;
    list=p;
    list->next=NULL;
}

//尾插法初始化
void init(Linklist&list)
{
    int n,x;
    Linklist p=list;

    cin>>n;

    while(n--)
    {
        cin>>x;

        Linklist temp=new LIST;
        temp->next=NULL;
        temp->data=x;

        p->next=temp;
        p=p->next;
    }
}

void show(Linklist&list)
{
    Linklist p=list;

    while(p->next!=NULL)
    {
        cout<<p->next->data<<' ';
        p=p->next;
    }
    
    cout<<endl;
    return;
}
    
bool empty(Linklist&p)
{
    return p==NULL||p->next==NULL;
}

void splice_front(Linklist&head,Linklist & p)
{
    Linklist temp=head->next;
    head->next=temp->next;
    temp->next=p->next;
    p->next=temp;
}

void list_merge(Linklist &list,Linklist& p)
{
    Linklist it=list,p1=list->next,p2=p->next;

    while(p1&&p2)
    {
        if(p1->data<p2->data)
        {
            it->next=p1;
            p1=p1->next;
        }
        else
        {
            it->next=p2;
            p2=p2->next;
        }

        it=it->next;
    }

    if(!p1)it->next=p2;
    else it->next=p1;

    p->next=NULL;
}


void list_sort(Linklist& list)
{
    if(list->next==NULL||list->next->next==NULL)return;

    Linklist carry=new LIST;
    Linklist counter[64];

    for(int i=0;i<64;++i)
        counter[i]=new LIST,counter[i]->next=NULL;
        
    carry->next=NULL;

    int fill=0;

    while(!empty(list))
    {
        splice_front(list,carry);
        int i=0;

        while(i<fill&&!empty(counter[i]))
        {
            list_merge(counter[i],carry);
        
            swap(carry,counter[i++]);
        }

        swap(carry,counter[i]);

        if(i==fill)++fill;
    }

    for(int i=1;i<fill;++i)
        list_merge(counter[i],counter[i-1]);
    
    list->next=counter[fill-1]->next;

    for(int i=0;i<64;++i)
        delete counter[i];
    
    delete carry;

    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    Linklist it;

    init_list(it);
    init(it);

    list_sort(it);

    show(it);

    cout<<endl;
    system("pause");
    return 0;
}
