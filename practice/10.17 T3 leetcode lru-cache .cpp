#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <list>

#define ll long long

using namespace std;


//哈希链表，通过两者的组合实现快速查询+快速增删，但是常数很大

class LRUCache {
public:

    struct Linknode{//双向链表
        int x,v;//保存原值和映射值 ，保存原值是为了删除mp中对应的节点
        Linknode*next,*last;
    };

    int k;
    Linknode*s;//头结点 next域指向下一个节点，last域指向最后一个节点

    unordered_map<int,Linknode*> mp;

    LRUCache(int capacity) {
        k=capacity;
        s=new Linknode;//初始化头结点
        s->next=NULL;
        s->last=NULL;
    }
    
    int get(int key) {
      
      if(mp.count(key))//如果在，就把这个节点放在头部，并且返回对应值
      {
        Linknode*t=mp[key];
        Linknode*pre=t->last,*next=t->next;
        pre->next=next;
        next->last=pre;

        next=s->next;
        t->next=next;
        t->last=s;
        s->next=t;
        next->last=t;

        return t->v;
      }
      else
      {
        return -1;
      }
    }
    
    void put(int key, int value) {
        if(mp.count(key))//如果在，就修改对应值，并且把对应节点放在头部
        {
            mp[key]->v=value;

             Linknode*t=mp[key];
           Linknode*pre=t->last,*next=t->next;
              pre->next=next;
              next->last=pre;

               next=s->next;
              t->next=next;
              t->last=s;
             s->next=t;
             next->last=t;
        }
        else
        {
            Linknode*p;

            if(mp.size()==k)//如果满了，删除尾部节点
            {
                Linknode*t=s->last;
                mp.erase(mp.find(t->x));//通过链表节点翻过去去找map里面的节点
                t->last->next=s;
                s->last=t->last;
                //free(t);

                p=t;//如果满了，不释放节点，把这个节点内存重新利用
            }
            else
                p=new Linknode;

            //Linknode*p=new Linknode;//新建节点
            p->x=key,p->v=value;
            mp[key]=p;

            if(s->next==NULL)//如果链表为空
            {
                s->next=p;
                p->last=s;
                p->next=s;
                s->last=p;
            }
            else//如果不为空
            {
                s->next->last=p;
                p->next=s->next;
                p->last=s;
                s->next=p;
            }
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    LRUCache it(2);

    it.put(1,1);
    it.put(2,2);
    cout<<it.get(1)<<endl;
    it.put(3,3);
    cout<<it.get(2)<<endl;
    it.put(4,4);
    cout<<it.get(1)<<endl;
    cout<<it.get(3)<<endl;
    cout<<it.get(4)<<endl;


    cout<<endl;
    system("pause");
    return 0;
}
