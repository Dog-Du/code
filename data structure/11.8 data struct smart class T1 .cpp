#include "create tree and big list convert .cpp"
int getbf(node*&root)
{
    if(root==nullptr)return 0;
    int ldepth=getbf(root->l);
    int rdepth=getbf(root->r);
    root->bf=ldepth-rdepth;
    return max(ldepth,rdepth)+1;
}

void solve()
{
    string s;
    cin>>s;

    node* root=new node(' ');
    root->l=root->r=nullptr;

    another_answer(root,s);

    getbf(root);

    cout<<"preshow:"<<endl;
    preshow(root);
    cout<<"midshow:"<<endl;
    midshow(root);
    cout<<endl;
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
