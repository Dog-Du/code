#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>

#define ll long long

using namespace std;

const int maxn=2e5+10;

struct old_driver_tree{
    int l=0,r=maxn;
    mutable int v=-1;
    bool operator<(const old_driver_tree&it)const{
        return l<it.l;
    }
};

struct OLD_DRIVER_TREE{
    int l=0,r=maxn;

    mutable set<old_driver_tree> tree;

    bool operator<(const OLD_DRIVER_TREE&it)const{
        return l<it.l;
    }
};

set<OLD_DRIVER_TREE> tr;

    set<old_driver_tree>::iterator split(int pos,set<old_driver_tree>&tree)
    {
        auto it=tree.lower_bound({pos,-1,-1});

        if(it!=tree.end()&&it->l==pos)return it;

        --it;

        int l=it->l,r=it->r;

        int v=it->v;

        tree.erase(it),tree.insert({l,pos,-1});

        return tree.insert({pos,r,v}).first;
    }

    void merge(int l,int r,int v,set<old_driver_tree>&tree)
    {
        auto itr=split(r+1,tree),itl=split(l,tree);

        tree.erase(itl,itr);
        tree.insert({l,r,v});
    }

set<OLD_DRIVER_TREE>::iterator Split(int pos)
{
    set<old_driver_tree> temp;
    auto it=tr.lower_bound({pos,-1,temp});

    if(it!=tr.end()&&it->l==pos)return it;

    --it;

    int l=it->l,r=it->r;

    temp=it->tree;

    tr.erase(it),tr.insert({l,pos,temp});

    return tr.insert({pos,r,temp}).first;
}

void Merge(int l,int r,int x,int y,int k)
{
    auto itr=Split(r+1),itl=Split(l);

    for(auto it=itl;it!=itr;++it)
    {
        auto tree=it->tree;
        merge(x,y,k,tree);
        it->tree=tree;
    }
}

int find(int x,int y,set<OLD_DRIVER_TREE>&tree)
{
    set<old_driver_tree> se;

    auto itx=tree.lower_bound({x,0,se});
    auto ity=itx->tree.lower_bound({y,0,0});

    return ity->v;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int n;
    cin>>n;

    set<old_driver_tree> tree;
    tree.insert({0,maxn,-1});

    tr.insert({0,maxn,tree});

    for(int i=1,x1,x2,y1,y2;i<=n;++i)
    {
        cin>>x1>>y1>>x2>>y2;
        x2+=x1,y2+=y1;

        Merge(x1,x2,y1,y2,i);
    }

    int x,y;
    cin>>x>>y;

    cout<<find(x,y,tr);


    cout<<endl;
    system("pause");
    return 0;
}
