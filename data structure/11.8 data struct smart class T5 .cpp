#include "create tree and big list convert .cpp"

bool dfs(node*&root,char x,char path[],int &len)
{
    if(root==nullptr)return false;
    if(root->ch==x)return true;

    path[len++]=root->ch;

    if(dfs(root->l,x,path,len))return true;
    if(dfs(root->r,x,path,len))return true;

    --len;

    return false;
}

void solve()
{
    string s;
    cin>>s;

    node*root=new node(' ');

    another_answer(root,s);

    char path[maxn];
    int len=0;

    if(dfs(root,'x',path,len))
    {
        for(int i=0;i<len;++i)
            cout<<path[i]<<"->";
        cout<<'x'<<endl;
    }
    else
    {
        cout<<"empty"<<endl;
    }

    cout<<endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int t;
    cin>>t;

    while(t--)
    {
        solve();
    }


    cout<<endl;
    system("pause");
    return 0;
}
