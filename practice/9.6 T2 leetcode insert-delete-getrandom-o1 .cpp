#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_set>
#define ll long long

using namespace std;

class RandomizedSet {
public:

    static const int maxn=2e5+10;

    int hash[maxn]={0};

    RandomizedSet() {

    }
    
    bool insert(int val) {

        int t=(val+maxn)%maxn;

        while(hash[t]!=0)
        {
            if(hash[t]==val)return false;
            t=(t+1)%maxn;
        }

        hash[t]=val;

        return true;
    }   
    
    bool remove(int val) {

        int t=(val+maxn)%maxn;

        while(hash[t]!=0)
        {
            if(hash[t]==val)
            {
                hash[t]=0;
                return true;
            }

            t=(t+1)%maxn;
        }

        return false;
    }
    
    int getRandom() {
        
        
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */


class RandomizedSet {
public:

    unordered_set<int> se;

    RandomizedSet() {
        return;
    }
    
    bool insert(int val) {
        if(se.count(val))return false;
        else 
        {
            se.insert(val);
            return true;
        }
    }
    
    bool remove(int val) {
        
        unordered_set<int>::iterator it;

        if((it=se.find(val))!=se.end())
        {
            se.erase(it);
            return true;
        }
        else
            return false;
    }
    
    int getRandom() {
        
        int t=rand()%se.size();
        
        auto it=se.begin();

        for(;t--;++it);

        return *it;
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    RandomizedSet it;

    int t=10;


    while(t--)
    {

    }

    cout<<endl;
    system("pause");
    return 0;
}
