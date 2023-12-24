#include "create tree and big list convert .cpp"

char search(char x,char y,node*&root)
{
    if(root==nullptr)return ' ';
    if(root->ch==x||root->ch==y)return root->ch;

    char l=search(x,y,root->l);
    char r=search(x,y,root->r);

    if(l!=' '&&r!=' ')return root->ch;
    else if(l!=' ')return l;
    else if(r!=' ')return r;
    else return ' ';
}

void solve()
{
    string s;
    cin>>s;
    node* root=new node(' ');

    another_answer(root,s);
    
    cout<<"answer: "<<search('x','y',root)<<endl<<endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int n;
    cin>>n;

    while(n--)
    {
        solve();
    }


    cout<<endl;
    system("pause");
    return 0;
}
