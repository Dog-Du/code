#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class WordDictionary {
private:
    struct node{
        node*child[26];
        int cnt;
        node(node*p){
            for(int i=0;i<26;++i)
                child[i]=p;
            cnt=0;
        }
    }*root;
    
    bool search(node*now,string&s,int i)
    {
        if(i==s.size())
        {
            if(now==root)return false;

            int sum=0;
            for(int j=0;j<26;++j)
                sum+=now->child[j]->cnt;
            
            if(sum==now->cnt)return false;
            return true;
        }

        if(s[i]=='.')
        {
            for(int j=0;j<26;++j)
                if(now->child[j]!=root)
                    if(search(now->child[j],s,i+1))return true;
        }
        else
        {
            if(now->child[s[i]-'a']!=root)
                if(search(now->child[s[i]-'a'],s,i+1))return true;
        }

        return false;
    }

public:
    WordDictionary(){
        root=new node(nullptr);
        for(int i=0;i<26;++i)
            root->child[i]=root;
    }
    
    void addWord(string word) {
        node*p=root;
        int len=word.size();

        for(int i=0;i<len;++i)
        {
            if(p->child[word[i]-'a']==root)
                p->child[word[i]-'a']=new node(root);

            p=p->child[word[i]-'a'];
            ++p->cnt;    
        }
    }
    
    bool search(string word) {
        return search(root,word,0);
    }
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    WordDictionary it;
    int n=10;

    while(n--)
    {
        int op;
        string s;
        cin>>op>>s;

        if(op==1)it.addWord(s);
        else
        {
            cout<<it.search(s)<<endl;
        }
    }


    cout<<endl;
    system("pause");
    return 0;
}
