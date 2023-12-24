#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;


class Trie {
private:
    struct node{
        int total;
        node * son[26];
        node(){
            total=0;
            for(int i=0;i<26;++i)son[i]=nullptr;
        }
    }*root;


public:
    Trie() {
        root=new node;
    }
    
    void insert(string word) {
        node*p=root,*pre=nullptr;
        ++root->total;

        for(int i=0,len=word.size();i<len;++i)
        {
            if(p->son[word[i]-'a']==nullptr)
                p->son[word[i]-'a']=new node;
            
            p=p->son[word[i]-'a'];
            ++p->total;
        }
    }
    
    bool search(string word) {
        node*p=root;

        for(int i=0,len=word.size();i<len&&p!=nullptr;++i)
        {
            p=p->son[word[i]-'a'];
        }

        if(p==nullptr)return false;

        int total=0;

        for(int i=0;i<26;++i)
            if(p->son[i]!=nullptr) total+=p->son[i]->total;
        
        return total<p->total;
    }
    
    bool startsWith(string word) {
        node*p=root;

        for(int i=0,len=word.size();i<len&&p!=nullptr;++i)
        {
            p=p->son[word[i]-'a'];
        }

        if(p==nullptr)return false;
        return true;
    }
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    


    cout<<endl;
    system("pause");
    return 0;
}
