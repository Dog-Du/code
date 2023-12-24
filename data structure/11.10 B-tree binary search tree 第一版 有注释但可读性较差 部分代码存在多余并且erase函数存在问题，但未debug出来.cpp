#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>

#define ll long long
#define m 35

using namespace std;

/*
为什么B-树文件索引（磁盘）更优？
1.对磁盘进行访问等同于指针的移动
2.磁盘具有局部访问优化，页访问
3.节点与节点之间，数据是不连续的，可能在不同的页之间
4.B-树比较矮，指针操作较少

在把磁盘里的数据加载到内存中的时候，是以页为单位来加载的，
而我们也知道，节点与节点之间的数据是不连续的，所以不同的节点，很有可能分布在不同的磁盘页中
*/

struct node{
    int key,value;
    bool operator<(const node&it)const{
        return key<it.key;
    }
    bool operator>(const node&it)const{
        return key>it.key;
    }
    bool operator==(const node&it)const{
        return key==it.key;
    }
};

struct BTNode{
    int keynum;
    BTNode*parent;
    node key[m+1]={0};//0号元素未用
    BTNode*ptr[m+1]={0};//子树元素指针，0号元素要用！
};  

struct result{//tag表示是否找到对于节点
    int i;//i表示位置
    bool tag;
    BTNode*ptr;//指向位置
};

//在调整的过程中，牢记一个问题：双亲和孩子的双向绑定（这是在踩了很多坑后总结出来的）

class B_Tree{
private:
    int Size;
    const int s=(m+1)/2;//中间分裂的位置
    const int min_key=(m-1)/2;//最小的keynum
    BTNode*root;
public:
    B_Tree()
    {
        Size=0;
        root=nullptr;
    }

    bool erase(int x)
    {
        result res=search(x);

        if(res.tag)
        {
            if(--res.ptr->key[res.i].value==0)
                erase(root,{x,0},res);
            return true;
        }
        else
            return false;
    }

    result search(int x)
    {
        node key={x,0};

        BTNode*p=root,*q=nullptr;
        bool flag=0;
        int i=0;

        while(p!=nullptr&&!flag)
        {
            //i最小是1,找的是第一个大于等于key的位置，如果没有，则应该指向p->keynum+1，
            //即尾指针才对，永远不会在查找时出现0
            i=lower_bound(p->key+1,p->key+p->keynum+1,key)-p->key;
            
            if(i<=p->keynum&&p->key[i]==key)flag=1;
            else
            {
                q=p;
                p=p->ptr[i-1];
                //要减去1，这才是应该下一步寻找的位置，书上的太不对啊
                //因为i指向的是第一个大于等于key的值，但是已知不相等，
                //所以应该减去1才不会漏过
            }
        }

        if(flag)//返回查找位置
        {
            return {i,flag,p};
        }
        else//返回插入位置，应该注意的是，如果查找失败，一定返回的是最底层的位置
        {
            return {i,flag,q};//返回的是插入节点
        }
    }
    
    bool insert(int x)//B-tree的插入总是插入到底端节点
    {
        result res=search(x);

        if(res.tag)
        {
            ++res.ptr->key[res.i].value;
            return false;
        }
        else
            return _insert(root,{x,1},res.ptr,res.i);//最底层的地方，并且i不等于0
    }

/* 计算出整棵树上记录条数的总和 */
int CountKeyNum(BTNode* tree) {
	// 空树则为 0
	if (tree == NULL) return 0;

	// 计算所有子树记录条数总和
	int childTotal = 0;
	for (int i = 0; i <= tree->keynum; i++) {
		childTotal += CountKeyNum(tree->ptr[i]);
	}

	// 子树加上自身的记录条数，即为总记录条数
	return tree->keynum + childTotal;
}

/* 打印 B 树 */
void TraverseBTree(BTNode *tree=nullptr) {//看的别人代码直接复制粘贴的调试函数

	// 动态创建一个数组，用于存放当前结点是否为最后结点的标识
    tree=this->root;
	int nowNum = 0;
	int* isLast = (int*)malloc(sizeof(int) * (CountKeyNum(tree) + 10));
	
	// 打印树形
	printf("\n");
	PrintBTree(tree, isLast, nowNum);
}

/* 递归打印树形 */
void PrintBTree(BTNode *tree, int isLast[], int nowNum) {
	// 空树直接跳过
	if (tree == nullptr) return;

	// 打印新节点先打印一下平台
	printf("-|\n");
	for (int i = 0; i <= tree->keynum; i++) {
		if (tree->ptr[i] != NULL) {
			printBranch(isLast, nowNum);
			printf("|----");
			isLast[nowNum++] = (i == tree->keynum);
			PrintBTree(tree->ptr[i], isLast, nowNum);
			nowNum--;
		}
		if (i != tree->keynum) {
			printBranch(isLast, nowNum);
			printf("|- %d\n", tree->key[i+1].key);
		}
	}
}

/* 打印树枝 */
void printBranch(int isLast[], int nowNum) {
	for (int i = 0; i < nowNum; i++) {
		if (isLast[i]) printf(" ");
		else printf("|");
		printf("      ");
	}
}

private:

    void deleteroot(BTNode*&root)//空根只有一个孩子
    {
        //  this->root=root->ptr[0];
        //  this->root->parent=nullptr;
        //  delete root;
        
        // return ;

        if(root->ptr[0]!=nullptr)
        { BTNode*child=root->ptr[0];
         root->ptr[0]=child->ptr[0];

         if(child->ptr[0]!=nullptr)
             child->ptr[0]->parent=root;
        
         for(int i=1;i<=child->keynum;++i)
             _Insert(root,child->key[i],i,child->ptr[i]);
        
        delete child;}
        else
        {
            BTNode*child=root->ptr[1];
            root->ptr[1]=child->ptr[0];

            if(child->ptr[0]!=nullptr)
                child->ptr[0]->parent=root;
            
            int t=root->keynum;
            for(int i=1;i<=child->keynum;++i)
                _Insert(root,child->key[i],i+t,child->ptr[i]);
            
            delete child;
        }
    }

    //把右节点合并到左节点中
    void Combine(BTNode*&left,BTNode*&right)
    {
        if(left==nullptr)return;

        //把右节点的信息依次插入左边的最右边
        for(int i=1;i<=right->keynum;++i)
        {
            _Insert(left,right->key[i],left->keynum+1,right->ptr[i]);
        }

        delete right;
        right=nullptr;
    }

    void Restore(BTNode*&p,int pi)
    {
        BTNode*parent,*brother;
        parent=p->parent;

        while(1)
        {
            if(pi>0&&(brother=parent->ptr[pi-1])!=nullptr&&brother->keynum>min_key)
            {
                _Insert(p,parent->key[pi],1,p->ptr[0]);//把左兄弟的父节点给它
                p->ptr[0]=brother->ptr[brother->keynum];//把最左边的孩子节点改为左兄弟最右边孩子

                if(brother->ptr[brother->keynum]!=nullptr)//修改左兄弟的最右孩子的父亲
                    brother->ptr[brother->keynum]->parent=p;
                
                /*下面的这三步其实是复杂化了，只需要移动几次指针其实就好了*/

                Remove(parent,pi);//把父亲节点删去，但是不修改指针
                Insert(parent,pi,brother->key[brother->keynum]);//把左兄弟的最右节点给它，
                Remove(brother,brother->keynum);//删除最右边的
                break;
            }
            else if(pi<parent->keynum&&(brother=parent->ptr[pi+1])!=nullptr&&brother->keynum>min_key)
            {
                //和左兄弟同理，也有些复杂化了
                _Insert(p,parent->key[pi+1],p->keynum+1,brother->ptr[0]);
                Remove(parent,pi+1);
                Insert(parent,pi+1,brother->key[1]);
                Remove(brother,1);

                for(int i=0;i<=brother->keynum;++i)
                    brother->ptr[i]=brother->ptr[i+1];
                break;
            }
            else if(pi>0&&(brother=parent->ptr[pi-1])!=nullptr)//左兄弟也比较穷即 min_key = (m-1)/2 ，这是两个节点相加不超过m，所以合并！
            {  
                _Insert(p,parent->key[pi],1,p->ptr[0]);//把父亲节点拿到当前节点上
                Remove(parent,pi);//父亲这里删除
                Combine(brother,p);//兄弟合并
                p=brother;

                for(int i=pi;i<=parent->keynum;++i)//父亲这里修改指针
                    parent->ptr[i]=parent->ptr[i+1];
                
                if(parent->keynum<min_key)//如果父亲也变穷了
                {
                    if(parent->parent==nullptr)
                    {
                        deleteroot(parent);
                        break;
                    }
                    else
                    {
                        int i=lower_bound(parent->parent->key+1,parent->parent->key+parent->parent->keynum+1,p->key[1])-parent->parent->key-1;
                        p=parent;
                        pi=i;
                        parent=p->parent;//别忘了修改父亲
                    }
                }
                else //节点个数正常，直接break;
                    break;
            }
            else if(pi<p->keynum&&(brother=parent->ptr[pi+1])!=nullptr)
            {
                _Insert(p,parent->key[pi+1],p->keynum+1,brother->ptr[0]);
                Remove(parent,pi+1);
                Combine(p,brother);

                for(int i=pi+1;i<=parent->keynum;++i)
                    parent->ptr[i]=parent->ptr[i+1];
                
                if(parent->keynum<min_key)
                {
                    if(parent->parent==nullptr)
                    {
                        deleteroot(parent);
                        break;
                    }
                    else
                    {
                        int i=lower_bound(parent->parent->key+1,parent->parent->key+parent->parent->keynum+1,p->key[p->keynum+1])-parent->parent->key-1;
                        pi=i;
                        p=parent;
                        parent=p->parent;//parent别忘了修改
                    }
                }
                else    //如果父亲节点个数正常，直接break
                    break;  
            }
            else
            {
                _Insert(p,parent->key[pi],1,p->ptr[0]);
                Remove(parent,pi);
                for(int i=pi+1;i<=parent->keynum;++i)
                    parent->ptr[i]=parent->ptr[i+1];
                
                if(parent->keynum<min_key)
                {
                    if(parent->parent==nullptr)
                    {
                        deleteroot(parent);
                        break;
                    }
                    else
                    {
                        int i=lower_bound(parent->parent->key+1,parent->parent->key+parent->parent->keynum+1,p->key[p->keynum+1])-parent->parent->key-1;
                        pi=i;
                        p=parent;
                        parent=p->parent;//parent别忘了修改
                    }
                }
                else    //如果父亲节点个数正常，直接break
                    break;  
            }
        }
        
    }

    void Insert(BTNode*&p,int i,node&x)//把x插入p的第i个位置
    {
        if(p==nullptr)return;

        for(int j=p->keynum;j>=i;--j)
            p->key[j+1]=p->key[j];
        
        p->key[i]=x;
        ++p->keynum;
    }


    void Remove(BTNode*&p,int i)//删除这个节点
    {
        /*删除记录这一部分，我省略了删除孩子指针的步骤，为什么呢？
        这里是为了方便后续的树形调整函数
        如果只删除记录的话，会导致孩子指针比原本多出一个，但好处也很明显，
        到后边有一个双亲记录替换的需求，我提供了只删除记录和只插入记录的操作
        ，可以在不影响孩子指针的情况下完成记录值的替换*/
        if(p==nullptr)return;

        for(;i<p->keynum;++i)//左移
            p->key[i]=p->key[i+1];
        
        p->keynum--;
        return;
    }

    void Successor(BTNode*&p,int &i)//获得前驱节点，并替换i和p
    {
        if(p==nullptr)return;//如果是空（比如本来就是最底层）
        if(p->ptr[i-1]==nullptr)return;

        BTNode*res=p->ptr[i-1];

        while(res->ptr[res->keynum]!=nullptr)
            res=res->ptr[res->keynum];
        
        p->key[i]=res->key[res->keynum];

        p=res;
        i=res->keynum;
    }

    void Next(BTNode*&p,int &i)
    {
        if(p==nullptr)return;
        if(p->ptr[i]==nullptr)return;

        BTNode*res=p->ptr[i];

        while(res->ptr[0]!=nullptr)
            res=res->ptr[0];
        
        p->key[i]=res->key[1];
        p=res;
        i=1;
    }

    //问题在于没有前驱怎么办
    void erase(BTNode*&root,node x,result&res)
    {
        int flag=0;

        if(res.ptr->ptr[res.i-1]!=nullptr)//判断当前节点是不是最下层非终端节点
            Successor(res.ptr,res.i);//不是，则替换
        else if(res.ptr->ptr[res.i]!=nullptr)
        {    Next(res.ptr,res.i);flag=1;}

        x=res.ptr->key[res.i];//保存要删除的那个节点，


        BTNode*parent=res.ptr->parent;

        //如果是根节点，就不再调整，因为既然删除操作放生在了根节点，说明已经没有了左右兄弟和双亲了
        //如果不是根节点，并且节点个数比较少，
        if(parent!=nullptr&&res.ptr->keynum-1<min_key)
        {
            Remove(res.ptr,res.i);//删除这个节点
            //在父节点找它的位置，因为已经被remove了，可以预测肯定是找不到这个节点的
            //这时得到最后一个小于本身的进行restore
            int pi=lower_bound(parent->key+1,parent->key+parent->keynum+1,x)-parent->key-1+flag;
            Restore(res.ptr,pi);
            /*这里的 RestoreBTree 函数，我和其他地方的不一样，参数 pi 并不是关键字在目标结点中的位置，
            而是整个目标节点在双亲节点中的位置，这样做的好处上边也提到了，可以很方便地找到左右双亲和左右兄弟
            也可以注意到 pi = Search -1; 这一句，和上边的 child[i-1] 是一样的道理，都是找到双亲中孩子的位置*/
        }
        else
        {
            for(int i=res.i;i<res.ptr->keynum;++i)
            {
                res.ptr->key[i]=res.ptr->key[i+1];
                res.ptr->ptr[i]=res.ptr->ptr[i+1];
            }
            --res.ptr->keynum;
        }
        return;
    }

    void split(BTNode*&q,const int &mid,BTNode*&ap)//节点q的mid之后全部分给ap，但是mid之前全部保留
    {
        int i,j;
        ap=new BTNode;
        ap->ptr[0]=q->ptr[mid];//节点零是这个时候会去填写的

        for(i=mid+1,j=1;i<=m;++i,++j)//优化的话，可以考虑这里改成move函数
        {
            ap->key[j]=q->key[i];
            ap->ptr[j]=q->ptr[i];
        }

        ap->keynum=m-mid;
        ap->parent=q->parent;
        //置于同一层，保证最底层在同一层次上，就这么一句话保证了在插入时所有最下端节点都在同一层上

        for(i=0;i<=m-mid;++i)
            if(ap->ptr[i]!=nullptr)
                ap->ptr[i]->parent=ap;
        
        q->keynum=mid-1;//后面的全部舍弃
    }

    void _Insert(BTNode*&q,node&x,int i,BTNode*&ap)
    {
        for(int j=q->keynum;j>=i;--j)
        {
            q->key[j+1]=q->key[j];
            q->ptr[j+1]=q->ptr[j];
        }

        q->key[i]=x;
        q->ptr[i]=ap;

        if(ap!=nullptr)
        {
            ap->parent=q;
        }

        ++q->keynum;
    }

    void newroot(BTNode*&T,BTNode*&p,node&x,BTNode*&ap)//这个函数只对根节点使用！
    {
        T=new BTNode;
        T->keynum=1;
        T->ptr[0]=p;
        T->ptr[1]=ap;
        T->key[1]=x;

        if(p!=nullptr)
            p->parent=T;
        if(ap!=nullptr)
            ap->parent=T;

        T->parent=nullptr;
    }

    bool _insert(BTNode*&T,node x,BTNode*q,int i)
    {
        bool finished=false;
        BTNode*ap=nullptr;
        //ap表示x所在的节点的指针，初始时为空，毕竟是节点
    
        while(q!=nullptr&&!finished)
        {
            _Insert(q,x,i,ap);//事实上，i不可能为0

            if(q->keynum<m)finished=1;
            else
            {
                split(q,s,ap);
                x=q->key[s];

                //q=q->parent;
                //问题出现在了这里，如果q变成了空，那么下面判断出根节点出现了分裂，
                //那应该是把q放在新的根节点的最左子树上，但是q却变成了空，那还放个屁，直接没有了
                //就是这里的问题导致的时不时会出错而且不容易发现，超你妈的费我老半天劲找不出来为什么。
                //这样insert函数就十分完善了，

                if(q->parent!=nullptr)
                {
                    q=q->parent;
                    i=lower_bound(q->key+1,q->key+q->keynum+1,x)-q->key;
                }
                else 
                    break;
            }
        }

        //如果根节点为空，或者根节点出现分裂，
        //因为finished为false，只能是根节点为空或者根节点出现了分裂
        if(!finished)newroot(T,q,x,ap);

        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

     fstream p;
     p.open("E:\\DOWNLOAD\\P1177_1.in");

    B_Tree it;
    int n;
    cin>>n;
    int a[n+1];

    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        it.insert(a[i]);
       // it.TraverseBTree();
    }

    
    sort(a+1,a+1+n);
    //int tot=unique(a+1,a+1+n)-a-1;

    for(int i=1;i<=n;++i)
    {
        it.TraverseBTree();
        result p=it.search(a[i]);
        
        if(p.tag)cout<<a[i]<<' ';

        it.erase(a[i]);
    }

    //it.TraverseBTree();

    cout<<endl;
    system("pause");
    return 0;
}
