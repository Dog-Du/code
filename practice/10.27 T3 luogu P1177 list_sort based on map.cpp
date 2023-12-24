#include <iostream>
#include <list>
#include <unordered_map>
#include <map>

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
    
//时间复杂度: O(nlogn) 但是常数比较大  空间复杂度 ： O(n) 常数也比较大
void list_sort(Linklist& list)
{
    if(list->next==nullptr||list->next->next==nullptr)return;//一个元素或者空

    map<int,Linklist> mp;
    map<int,Linklist>::iterator iter;//设置一个迭代器


    Linklist p=list->next,it,temp;
    list->next=nullptr;//防止自环

    while(p)
    {
        temp=p->next;//记录下一个位置

        iter=mp.upper_bound(p->data);//寻找第一个大于这个数的迭代器 不是大于等于
        
        if(iter==mp.begin())//如果是begin说明这个数是最小的，it放在头结点上即可
        {
            it=list;
        }
        else//不然，找到最后一个小于等于它的迭代器，获得链表节点
        {
            --iter;
            it=iter->second;
        }

        //刨下节点，
        p->next=it->next;
        it->next=p;

        mp[p->data]=p;//新建或者覆盖key一样的节点，即可以减少节点个数也可以实现稳定排序

        p=temp;//进行下一个节点
    }
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
