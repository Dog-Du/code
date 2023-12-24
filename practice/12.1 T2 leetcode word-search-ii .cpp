#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_set>

#define ll long long

using namespace std;

class Solution {
private:
    struct node{
        node*child[26];
        string word;//字典树中放特殊值来分辨到底是不是叶子结点。
        node(node*p){
            for(int i=0;i<26;++i)
                child[i]=p;
        }
    }*root;
    int n,m;
    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};

    void insert(string&s)
    {
        node*p=root;
        int n=s.size();

        for(int i=0;i<n;++i)
        {
            if(p->child[s[i]-'a']==root)
                p->child[s[i]-'a']=new node(root);
            
            p=p->child[s[i]-'a'];
        }

        p->word=s;
    }

    void dfs(vector<vector<char>>&board,int x,int y,node*now,unordered_set<string>&se)
    {
        char ch=board[x][y];

        if(now->child[ch-'a']==root)return;

        now=now->child[ch-'a'];

        if(now->word.size()>0)se.insert(now->word);

        board[x][y]='?';

        for(int i=0,nx,ny;i<4;++i)
        {
            nx=x+dx[i];
            ny=y+dy[i];

            if(nx>=0&&nx<n&&ny>=0&&ny<m&&board[nx][ny]!='?')
                dfs(board,nx,ny,now,se);
        }

        board[x][y]=ch;
    }
public: 
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> ans;
        unordered_set<string> res;
        root=new node(nullptr);
        for(int i=0;i<26;++i)root->child[i]=root;

        n=board.size(),m=board.front().size();

        for(auto&it:words)insert(it);

        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
                dfs(board,i,j,root,res);
        
        for(auto&it:res)
            ans.push_back(it);
        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    vector<vector<char>> vec={{'o','a','a','n'},{'e','t','a','e'},{'i','h','k','r'},{'i','f','l','v'}};
    vector<string> words={"oath","pea","eat","rain"};

    Solution one;
    one.findWords(vec,words);

    cout<<endl;
    system("pause");
    return 0;
}
