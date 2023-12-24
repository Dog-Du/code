#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

struct queue{

    struct list{
        int id;
        list*next;
    }*head,*rear;

    int Size=0;

    queue()
    {
        head=new list;
        rear=new list;
        head->next=rear;
        rear->next=head;
    }

    void push(int x)
    {
        rear->next->next=new list;
        rear->next->next->id=x;
        rear->next=rear->next->next;
        ++Size;
    }

    void pop()
    {
        list*temp=head->next;
        head->next=head->next->next;
        free(temp);
        --Size;
    }

    int front()
    {
        return head->next->id;
    }

    int back()
    {
        return rear->next->id;
    }

    int size()
    {
        return Size;
    }

    bool empty()
    {
        return Size==0;
    }
}man,woman;

int main()
{
    int m,n,k;

    cin>>m>>n>>k;

    for(int i=1;i<=m;++i)   
        man.push(i);
    
    for(int i=1;i<=n;++i)
        woman.push(i);

    int cnt=1;
    while(1)
    {
        printf("di %d lun : \n",cnt++);

        for(int i=1;i<=k;++i)
        {
            printf("man:%d woman:%d \n",man.front(),woman.front());
            man.push(man.front());
            woman.push(woman.front());
            man.pop();
            woman.pop();
        }

        _sleep(5*1000);
    }


    cout<<endl;
    system("pause");
    return 0;
}
