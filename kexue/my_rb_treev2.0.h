#include <bits/stl_function.h>
#include <bits/stl_pair.h>
#include <bits/allocator.h>
#include <ext/aligned_buffer.h>
#include <bits/stl_construct.h>


//相比于第一版本，在rb_tree_node_base中新增了
// node_count表示当前子树的大小，可以支持log(n)时间 get_val和 get_rank，然后AC洛谷P3369

//以老版本为主，新版本在语法上借鉴吧。
namespace my_rb_tree
{

const bool RED=true;
const bool BLACK=false;

//先对红黑树进行声明，后面友元要用
template<typename Key,typename Value,typename KeyOfValue,typename Compare>
class Rb_tree;

//进行了节点定义，完成了getmin函数和getmax函数，
//是rb_tree_node的父亲
struct rb_tree_node_base
{
    typedef rb_tree_node_base* base_ptr;
    typedef unsigned long long size_t;
    //---const暂时不知道有啥用
    typedef const rb_tree_node_base* const_base_ptr;

    bool color;
    //定义了parent，在iterator中省去了空间。
    //也可以在iterator中定义一个栈实现相关功能
    base_ptr parent;
    base_ptr left;
    base_ptr right;
    size_t node_count; 

    rb_tree_node_base():node_count(1){}

    ////TODO:新版C++stl标准增加了const类型的，暂时不知道有什么用
    static base_ptr get_min(base_ptr x)
    {
        while(x->left!=nullptr)x=x->left;
        return x;
    }
    static base_ptr get_max(base_ptr x)
    {
        while(x->right!=nullptr)x=x->right;
        return x;
    }
};

////TODO:-------C++新标准用了Key_compare帮助比较，rb_tree_header.之后再看

template <typename Value>
struct rb_tree_node:public rb_tree_node_base
{
    typedef rb_tree_node<Value>* Link_type;//指针类型
    Value value;    //节点值,新标准中用另一种方式存储
    rb_tree_node(){this->node_count=1;}

    //因为对于const类型不能修改，只能在这里列表初始化。
    rb_tree_node(const Value&v):value(v){this->node_count=1;}
};

////TODO:这里对齐新版本，删除了父类。
//end()为header，在header中left为begin,right为最右边的，parent指向根
//rb_tree_base_iterator是rb_tree_iterator的父亲
//这里完成了基本的++和--操作
//这下好了，杂糅了老版本和新版本，测。 
/*
struct rb_tree_base_iterator
{
    //定义指针，距离，双向迭代器
    //base_ptr,const_base_ptr在父类中
    typedef rb_tree_node_base::base_ptr base_ptr;

    base_ptr M_node;

    void increment()//迭代器++，需要对end()特判
    {
        if(M_node->right!=nullptr)
        //右孩子不为空，那么直接去左子树的最左偏
        {
            M_node=M_node->right;
            M_node=M_node->get_min(M_node);
        }
        else
        {
            base_ptr M_parent=M_node->parent;
            //如果当前节点一直是父节点的右孩子，
            //那么需要一直找父亲的父亲，知道当前节点为父亲节点的左孩子，这个
            //这个时候父亲节点即下一个
            while(M_node==M_parent->right)
                M_node=M_parent,M_parent=M_parent->parent;

            //特判M_node为根节点的情况，即根节点只有左子树，没有右子树
            //这个判断主要是为了end()，
            //如果M已经是最右边的节点，那么理应返回end()即header

            if(M_node->right!=M_parent)
                M_node=M_parent;
        }
    }

    void decrement()//迭代器--，需要对begin()特判
    {
        ////TODO:嘶，红色说明不是根，那父亲的父亲怎么会是本身呢？
        //答：特判header，如果是header，说明当前迭代器是end(),
        //那么减去一个就变成了末迭代器。也就是header的右孩子，可以直接返回
        if(M_node->color==RED&&M_node->parent->parent==M_node)
            M_node=M_node->right;
        else if(M_node->left!=nullptr)//左孩子不为空
        {
            M_node=M_node->left;
            M_node=M_node->get_max(M_node);
        }
        else
        {
            base_ptr M_parent=M_node->parent;
            while(M_node==M_parent->left)
                M_node=M_parent,M_parent=M_parent->parent;
            
            ////TODO:为什么--不需要对header特判？
            //答：首先header表示end()而不是begin()，
            //所以--之后即使变成end()也没有问题，不需要特判
            M_node=M_parent;
        }
    }
};
*/


//继承rb_tree_base_iterator
//end()为header，在header中left为begin,right为最右边的，parent指向根
//rb_tree_base_iterator是rb_tree_iterator的父亲
//这里完成了基本的++和--操作
//这下好了，杂糅了老版本和新版本，测。 
template<typename Value>
struct rb_tree_iterator
{
    //base_ptr在父类中，

     //定义指针，距离，双向迭代器
    typedef Value value_type;
    typedef Value& reference;
    typedef Value* pointer;

    typedef std::bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;

    typedef rb_tree_iterator<Value> Self;
    typedef rb_tree_node_base::base_ptr base_ptr;
    typedef rb_tree_node<Value>*    Link_type;

protected:

    base_ptr M_node;//指针

//比起第一版本，这里改成了get_M_node函数获取，更加统一。
template<typename Key,typename V,typename KeyOfValue,typename Compare>
friend  typename Rb_tree<Key,V,KeyOfValue,Compare>::Base_ptr&
        Rb_tree<Key,V,KeyOfValue,Compare>::
    get_M_node(typename Rb_tree<Key,V,KeyOfValue,Compare>::iterator& p);

public:
    rb_tree_iterator() {} //noexcept //noexpect()表示()中如果为true则必然无异常,编译器不会再对其检查

    explicit  //explicit关键字表示不允许隐性构造
    rb_tree_iterator(base_ptr x):M_node(x){}//noexcept

protected:

    //对于end如果继续++那么还是end

    void increment()//迭代器++，需要对end()特判
    {
        if(M_node->right!=nullptr)
        //右孩子不为空，那么直接去左子树的最左偏
        {
            if(M_node==M_node->right)return;//

            M_node=M_node->right;
            M_node=rb_tree_node_base::get_min(M_node);
        }
        else
        {
            base_ptr M_parent=M_node->parent;
            //如果当前节点一直是父节点的右孩子，
            //那么需要一直找父亲的父亲，知道当前节点为父亲节点的左孩子，这个
            //这个时候父亲节点即下一个
            while(M_node==M_parent->right)
                M_node=M_parent,M_parent=M_parent->parent;

            //特判M_node为根节点的情况，即根节点只有左子树，没有右子树
            //这个判断主要是为了end()，
            //如果M已经是最右边的节点，那么理应返回end()即header

            if(M_node->right!=M_parent)
                M_node=M_parent;
        }
    }

    //begin如果--那么会变成end
    void decrement()//迭代器--，需要对begin()特判
    {
        ////TODO:嘶，红色说明不是根，那父亲的父亲怎么会是本身呢？
        //答：特判header，如果是header，说明当前迭代器是end(),而header是红色的
        //那么减去一个就变成了末迭代器。也就是header的右孩子，可以直接返回

        if(M_node->parent==nullptr)return;
        //所有节点都应该有父亲，但是当树为空且当前为header时不是这样的，对此特判

        if(M_node->color==RED&&M_node->parent->parent==M_node)
            M_node=M_node->right;
        else if(M_node->left!=nullptr)//左孩子不为空
        {
            if(M_node==M_node->left)return;
            M_node=M_node->left;
            M_node=rb_tree_node_base::get_max(M_node);
        }
        else
        {
            base_ptr M_parent=M_node->parent;
            while(M_node==M_parent->left)
                M_node=M_parent,M_parent=M_parent->parent;
            
            ////TODO:为什么--不需要对header特判？
            //答：首先header表示end()而不是begin()，
            //所以--之后即使变成end()也没有问题，不需要特判
            M_node=M_parent;
        }
    }

public:
    //解引用，返回值的引用

    reference 
    operator*()const noexcept//const加在类中函数后面表示这个函数不会修改类中的
                            //值，如果修改会报错，除非值用Mutable修饰
    {
        //link_type需要转化成这样才能访问value
        return Link_type(M_node)->value;
    }

    //返回value的指针，先解引用再取址，
    ////TODO:为什么不直接返回this？
    //答：pointer指的是value的指针，所以应该返回value的指针
    pointer operator->()const noexcept
    {
        return &(operator*());
    }

    ////TODO:-----为什么operator++会有()和(int)两种？-----//

    //返回迭代器的引用，这个是 ++it 会返回引用
    //operator++()参数为空是这样的。
    Self& operator++() noexcept
    {
        increment();
        return *this;//这个地方返回的是迭代器本身
    }

    //返回迭代器的拷贝，这个是 it++ 不会返回引用，
    //返回的是拷贝，operator++()参数为int是这样的
    Self operator++(int)noexcept//it++后面不知道为什么会出现一个0
    {
        Self tmp=*this;
        increment();
        return tmp;//返回的是迭代器本身的拷贝
    }

    //和上面的同理。
    Self& operator--()noexcept
    {
        decrement();
        return *this;
    }

    Self operator--(int)noexcept
    {
        Self tmp=*this;
        decrement();
        return tmp;
    }

    //迭代器看的那个operator==有两个参数好像是老版本的。
    bool operator==(const Self&other)const noexcept
    {
        return this->M_node==other.M_node;
    }

    bool operator!=(const Self&other)const noexcept
    {
        return this->M_node!=other.M_node;
    }


    //因为函数和传入的参数无关，所以没有命名
    //我超，为什么新版没有这个反而。猜想可能是标准改成了可以直接使用
    //struct里面typedef的

    // std::bidirectional_iterator_tag iterator_category(const rb_tree_base_iterator&)
    // {return std::bidirectional_iterator_tag();}
    
    ////TODO:这个函数是干啥的？
    //是返回指针类型的。
    //template<typename Value,typename Ref,typename Ptr>
    // inline Value* value_type(const rb_tree_iterator&)
    // {
    //     return (Value*)0;
    //     //return nullptr;//返回空指针
    // }
};

inline void
update_node_count(rb_tree_node_base*x)
{
    if(x==nullptr)return;
    x->node_count=1;
    x->node_count+=(x->left==nullptr?0:x->left->node_count);
    x->node_count+=(x->right==nullptr?0:x->right->node_count);
}

//------全局函数，左右旋--------//

//左旋，对x进行左旋，需要传入root作为参数
//左旋，必有右孩子
////TODO:为什么这个传入root为引用型
//答：看下面

inline void  //内联
rb_tree_rotate_left(rb_tree_node_base*x,rb_tree_node_base*&root)
{
    rb_tree_node_base*y=x->right;
    x->right=y->left;
    if(y->left!=nullptr)
        y->left->parent=x;
    y->parent=x->parent;

    //因为没有传入header，但是却需要,如果x是root的时候修改header的指针
    //所以需要对root传入引用
    if(x==root)
        root=y;
    
    //下面对父亲进行处理
    else if(x==x->parent->left)
        x->parent->left=y;
    else 
        x->parent->right=y;
    
    y->left=x;
    x->parent=y;

    update_node_count(x),update_node_count(y);//先更新x在更新y，下面同理
}

//右旋，必有左孩子
inline void 
rb_tree_rotate_right(rb_tree_node_base*x,rb_tree_node_base*&root)
{
    rb_tree_node_base*y=x->left;
    x->left=y->right;
    if(y->right!=nullptr)
        y->right->parent=x;
    y->parent=x->parent;

    if(x==root)
        root=y;
    else if(x==x->parent->right)
        x->parent->right=y;
    else
        x->parent->left=y;
    
    y->right=x;
    x->parent=y;

    update_node_count(x),update_node_count(y);
}

//---------全局函数，红黑树的Rebalance，解决双红和双黑问题------//
//方法论：插入节点站在祖父，删除节点站在父亲

inline void
rb_tree_rebalance_for_insert(rb_tree_node_base*x,rb_tree_node_base*&root)
{
    //x指向新插入的节点,新节点为红色
    //同时x永远指向红色的节点。
    x->color=RED;
    rb_tree_node_base*parent=x->parent,*grandparent=parent->parent,*y;

    //站在祖父考虑问题。
    while(x!=root&&parent->color==RED)
    {
        update_node_count(parent);
        //左型
        if(parent==grandparent->left)
        {
            y=grandparent->right;

            //两个孩子都是红色，
            //策略：本节点染红，两个孩子染黑，则满足性质
            if(y!=nullptr&&y->color==RED)
            {
                parent->color=BLACK;
                y->color=BLACK;
                grandparent->color=RED;
                x=grandparent;
                //需要继续检查
                update_node_count(x);
            }
            //左双红
            //策略：分两种LL红和LR红，LR红需要先左旋
            //然后，孩子染黑，父亲染红，
            else
            {
                //LR型，先左旋
                //这代码正确吗？
            //if里面x=x->parent这个时候x的位置改变了啊，变成了父亲,抱歉，不该质疑
            //左旋之前，x先移动到父亲，左旋之后x的位置又降下来了。
            //所以每次旋转之后parent,grandparent都需要修改
                if(x==parent->right)
                {
                    x=parent;
                    rb_tree_rotate_left(x,root);
                    parent=x->parent;//需要刷新
                    grandparent=parent->parent;
                }
                parent->color=BLACK;//父亲染黑，祖父染红
                grandparent->color=RED;
                rb_tree_rotate_right(grandparent,root);//这个时候右旋，循环结束
                //还得是stl，rebalance代码比我的简短多了。
            }
        }
        else
        {
            y=grandparent->left;
            if(y!=nullptr&&y->color==RED)
            {
                y->color=parent->color=BLACK;
                grandparent->color=RED;
                x=grandparent;

                update_node_count(x);
            }   
            else
            {
                if(x==parent->left)
                {
                    x=parent;
                    rb_tree_rotate_right(x,root);
                    parent=x->parent;//需要刷新
                    grandparent=parent->parent;
                }
                parent->color=BLACK;
                grandparent->color=RED;
                rb_tree_rotate_left(grandparent,root);
            }

        }

        //应该放在while循环在下面，
        parent=x->parent;
        grandparent=parent->parent;
    }

    
    while(parent!=root)
        update_node_count(parent),parent=parent->parent;
    
    update_node_count(root);
    root->color=BLACK;
}

//站在父亲节点 
////TODO:leftmost?rightmost?
inline rb_tree_node_base*
rb_tree_rebalance_for_erase(rb_tree_node_base*z,
                    rb_tree_node_base*&root,
                    rb_tree_node_base*&leftmost,
                    rb_tree_node_base*&rightmost)
{
    ////TODO:x为什么始终指向空？x是干啥的啊？
    rb_tree_node_base*y=z,*x=nullptr,*x_parent=nullptr;

    //作用，让y指向被删除节点，x指向被删除节点的继任节点。
    //x_parent指向删除y之后的x的父亲,之所以不直接 x->parent是因为x可能为空
    if(y->left==nullptr)
        x=y->right;
    else if(y->right==nullptr)
        x=y->left;
    else
    {
        y=y->right;//需要直接后继；
        y=rb_tree_node_base::get_min(y);

        x=y->right;
    }

    //p=y;//指向后继。

    ////TODO:老版本没有move函数，所以没有进行值替代，而是进行的指针替代
    //这里为了方便进行值替代
    //然而我想多了，如果想要值替代，需要传入的是rb_tree_node而不是rb_tree_node_base
    
    //下面做的是把用y把z指针替代，同时用x把y指针替代。
    
    if(y!=z)//y是z的后继,注意，这个时候z的左节点必然不是y但是右节点可能是，需要讨论
    {
        z->left->parent=y;
        y->left=z->left;

        if(y!=z->right) //对y不是z的右节点特判
        {
            x_parent=y->parent;//x_parent
            if(x!=nullptr)x->parent=y->parent;
            y->parent->left=x;//y一定在父亲的左边，因为是后继
            y->right=z->right;
            z->right->parent=y;
        }
        else
            x_parent=y;
        
        //把z摘下来，y放上去。
        if(root==z)
            root=y;
        else if(z->parent->left==z)
            z->parent->left=y;
        else 
            z->parent->right=y;
        
        y->parent=z->parent;
        std::swap(y->color,z->color);

        y=z;
        // __y now points to node to be actually deleted
    }
    else//z本身就只剩一个孩子,所以y==z
    {
        x_parent=y->parent;
        if(x!=nullptr)x->parent=y->parent;
        

        if(root==z)
            root=x;
        else if(z->parent->left==z)
            z->parent->left=x;
        else
            z->parent->right=x;
        
        if(leftmost==z)
        {
            if(z->right==nullptr)
                leftmost=z->parent;
            else
                leftmost=rb_tree_node_base::get_min(x);
        }

        if(rightmost==z)
        {
            if(z->left==nullptr)
                rightmost=z->parent;
            else
                rightmost=rb_tree_node_base::get_max(x);
        }
    }

    if(y->color==BLACK)//如果删除的是黑色节点，这个时候处理双黑问题
    {
        rb_tree_node_base*brother;//指向x的兄弟

        while(x!=root&&(x==nullptr||x->color==BLACK))
        {
            update_node_count(x_parent);//应该更新父亲，因为x可能为空，而且x也不需要

            if(x==x_parent->left)
            {
                brother=x_parent->right;

                //右兄弟有红，这个时候有以下条件：
                //1.父亲为黑 2.右兄弟必有两个黑色孩子
                //3.右兄弟的两个黑色孩子可能还有红色孩子
                
                //策略：兄弟染黑，父亲染红，父亲左旋
                //这个时候x,x_parent相对位置没有变，
                //但是x_parent变成了红色，问题转化
                if(brother->color==RED)
                {
                    brother->color=BLACK;
                    x_parent->color=RED;
                    rb_tree_rotate_left(x_parent,root);
                    brother=x_parent->right;
                }

                //兄弟为黑，且孩子双黑，这个时候需要进一步调整，进入下一次循环。
                //因为删去的节点为黑色，可以知道，左子树比右子树少了一个黑色路径。
                
                if((brother->left==nullptr||brother->left->color==BLACK)&&
                    (brother->right==nullptr||brother->right->color==BLACK))
                {
                    //如果父亲为红色，那么这里可能会出现双红现象。在while循环最下面进行了处理。
                    //还以为没有考虑父亲为红色呢，不该质疑
                    brother->color=RED;
                    x=x_parent;
                    x_parent=x_parent->parent;
                }
                else//兄弟为黑，且至少有一个红孩子
                {
                    if(brother->right==nullptr||brother->right->color==BLACK)
                    {
                        ////TODO:这个判断是必要的吗？
                        //左节点应该必然存在并且是红色的啊
                        if(brother->left!=nullptr)
                            brother->left->color=BLACK;
                        
                        //RL型红色，先右旋
                        brother->color=RED;
                        rb_tree_rotate_right(brother,root);
                        brother=x_parent->right;
                    }

                    brother->color=x_parent->color;
                    x_parent->color=BLACK;

                    //这里也不应该啊，这里应该必然为红色啊。
                    if(brother->right!=nullptr)
                        brother->right->color=BLACK;

                    rb_tree_rotate_left(x_parent,root);
                    break;
                }
            }
            else
            {
                brother=x_parent->left;
                if(brother->color==RED)
                {
                    brother->color=BLACK;
                    x_parent->color=RED;
                    rb_tree_rotate_right(x_parent,root);
                    brother=x_parent->left;
                }

                if((brother->right==nullptr||brother->right->color==BLACK)&&
                    (brother->left==nullptr||brother->left->color==BLACK))
                {
                    brother->color=RED;
                    x=x_parent;
                    x_parent=x_parent->parent;
                }
                else
                {
                    if(brother->left==nullptr||brother->left->color==BLACK)
                    {
                        if(brother->right!=nullptr)
                            brother->right->color=BLACK;
                        brother->color=RED;
                        rb_tree_rotate_left(brother,root);//之前弄错了，写成了right
                        brother=x_parent->left;
                    }

                    brother->color=x_parent->color;
                    x_parent->color=BLACK;
                    if(brother->left!=nullptr)
                        brother->left->color=BLACK;
                    rb_tree_rotate_right(x_parent,root);
                    break;
                }
            }

        }
        
        if(x!=nullptr)x->color=BLACK;//应该放在while外面，可以排除继任节点是红色
    }

    while(x_parent!=root)
        update_node_count(x_parent),x_parent=x_parent->parent;
    
    update_node_count(root);
    return y;//返回y，y是待删除节点，这个应该是来删除的（为什么不直接在这里删除？）
}

//正活开始。

template<typename Value>
struct rb_tree_base
{
    rb_tree_base():M_header(nullptr){M_header=new rb_tree_node<Value>;}
    ~rb_tree_base(){M_put_node(M_header);}

    protected:
        rb_tree_node<Value>* M_header;

        rb_tree_node<Value>* M_get_node(const Value &v)
        {
            rb_tree_node<Value>*tmp=new rb_tree_node<Value>(v);
            tmp->left=tmp->right=tmp->parent=nullptr;
            tmp->color=RED;
            return tmp;
        }

        void M_put_node(rb_tree_node<Value>*p)
        {
            delete p;
        }
};

//KeyOfValue是仿函数，用于取出需要比较的值
template<typename Key,typename Value,typename KeyOfValue,typename Compare>
class Rb_tree:protected rb_tree_base<Value> //继承于rb_tree_base,天生有一个初始化好的头结点。
{
    typedef rb_tree_base<Value> Base;
    typedef Rb_tree<Key,Value,KeyOfValue,Compare> RB_Self;
protected:
    typedef rb_tree_node_base* Base_ptr;
    typedef rb_tree_node<Value> Rb_tree_node;
public:
    typedef Key key_type;
    typedef Value value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef Rb_tree_node* Link_type;
    typedef unsigned long long size_type;
    typedef std::ptrdiff_t difference_type;

protected:

    //rb_tree_node<Value>* M_header;

    Link_type M_create_node(const value_type& x)
    {
        Link_type tmp=this->M_get_node(x);
        return tmp;
    }

    Link_type M_clone_node(Link_type x)
    {
        Link_type tmp=new Rb_tree_node;
        tmp->value=x->value;
        tmp->color=x->color;
        tmp->left=tmp->right=nullptr;
        return tmp;
    }

    void destory_node(Link_type p)
    {
        //Destproy就是调用析构函数，对于new出来的则delete
        std::_Destroy(&p->value);
        this->M_put_node(p);
    }

protected:
    size_type M_node_count;
    Compare M_key_compare;

    Link_type& M_root()const{
        return (Link_type&) this->M_header->parent;
    }

    Link_type& M_leftmost()const{
        return (Link_type&) this->M_header->left;
    }

    Link_type& M_rightmost()const{
        return (Link_type&) this->M_header->right;
    }

    static Link_type& S_left(Link_type x){
        return (Link_type&)(x->left);
    }

    static Link_type& S_right(Link_type x){
        return (Link_type&)(x->right);
    }

    static Link_type& S_parent(Link_type x){
        return (Link_type&)(x->parent);
    }

    static reference S_value(Link_type x){
        return x->value;
    }

    static const Key& S_key(Link_type x){
        return KeyOfValue()(S_value(x));
    }

    // static bool& S_color(Link_type x){
    //     return (bool&)(x->color);
    // }

  static Link_type& S_left(Base_ptr __x)
    { return (Link_type&)(__x->left); }
  static Link_type& S_right(Base_ptr __x)
    { return (Link_type&)(__x->right); }
  static Link_type& S_parent(Base_ptr __x)
    { return (Link_type&)(__x->parent); }
  static reference S_value(Base_ptr __x)
    { return ((Link_type)__x)->value; }
  static const Key& S_key(Base_ptr __x)
    { return KeyOfValue()(S_value(Link_type(__x)));} 
  static bool& S_color(Base_ptr __x)
    { return (bool&)(Link_type(__x)->color); }

  static Link_type S_minimum(Link_type __x) 
    { return (Link_type)  rb_tree_node_base::get_min(__x); }

  static Link_type S_maximum(Link_type __x)
    { return (Link_type) rb_tree_node_base::get_max(__x); }


public:
    typedef rb_tree_iterator<value_type> iterator;

private:
    iterator M_insert(Base_ptr x,Base_ptr y,const value_type& v);
    Link_type M_copy(Link_type x,Link_type p);
    void M_erase(Link_type x);

    Base_ptr& get_M_node(iterator& p)
    {return p.M_node;}

public:
    Rb_tree():
        M_node_count(0),M_key_compare()
        {M_empty_initilaize();}
    
    Rb_tree(const Compare&comp):
        M_node_count(0),M_key_compare(comp)
        {M_empty_initilaize();}
    

    //也是深拷贝
    ////TODO:
    Rb_tree(const RB_Self&x):
        M_node_count(0),M_key_compare(x.M_key_compare)
    {
        if(x.M_root()==nullptr)
            M_empty_initilaize();
        else
        {
            S_color(this->M_header)=RED;
            M_root()=M_copy(x.M_root(),this->M_header);
            M_leftmost()=S_minimum(M_root());
            M_rightmost()=S_maximum(M_root());
        }

        M_node_count=x.M_node_count;
    }

    ~Rb_tree(){clear();}
    //深拷贝
    RB_Self& operator=(const RB_Self&x);
    
private:

    void M_empty_initilaize()
    {
        //M_header->color=RED;
        S_color(this->M_header)=RED;
        M_root()=nullptr;
        M_leftmost()=this->M_header;
        M_rightmost()=this->M_header;
    }

public:
    Compare key_comp() const {return M_key_compare;}
    iterator begin() {return iterator(M_leftmost());}
    iterator end() {return iterator(this->M_header);}

    bool empty()const {return M_node_count==0;}
    size_type size()const {return M_node_count;}
    size_type max_size() const{return size_type(-1);}

    //只需要换header，count和compare
    void swap(RB_Self&t)
    {
        std::swap(this->M_header,t.M_header);
        std::swap(M_node_count,t.M_node_count);
        std::swap(M_key_compare,t.M_key_compare);
    }

public:
    std::pair<iterator,bool> insert_unique(const value_type&x);
    iterator insert_equal(const value_type&x);

    //将x插入rb，保持节点独一无二
    iterator insert_unique(iterator position,const value_type&x);
    //允许节点重复
    iterator insert_equal(iterator position,const value_type&x);

    //这里和新保持一致，erase之后应该返回下一个迭代器
    iterator erase(iterator position);
    size_type erase(const key_type&x);
    iterator erase(iterator first,iterator last);
    
    void clear()
    {
        if(M_node_count>0)
        {
            M_erase(M_root());
            M_leftmost()=this->M_header;
            M_rightmost()=this->M_header;
            M_root()=nullptr;
            M_node_count=0;
        }
    }

public:
    iterator find(const key_type&x);
    size_type count(const key_type&x)const;
    iterator lower_bound(const key_type&x);
    iterator upper_bound(const key_type&x);
    //由值获得排名
    size_type get_rank(const key_type&x);
    //由排名获得值（迭代器）
    iterator get_val(size_t x);

    std::pair<iterator,iterator> equal_range(const key_type&x);

    bool __rb_verify();//debugging

    //这个放在里面，后面一个放在里面,
    bool operator==(const RB_Self&x)
    {
        return size()==x.size()&&
            std::equal(begin(),end(),x.begin());
    }

};

//类外定义函数：：：：方法
template<typename Key,typename Value,typename KeyOfValue,typename Compare>
typename Rb_tree<Key,Value,KeyOfValue,Compare>::RB_Self&
Rb_tree<Key,Value,KeyOfValue,Compare>
    ::operator=(const RB_Self&x)
{
        if(this!=&x)
        {
            clear();
            M_node_count=0;
            M_key_compare=x.M_key_compare;

            if(x.M_root()==nullptr)
            {
                M_root()=nullptr;
                M_leftmost()=this->M_header;
                M_rightmost()=this->M_header;
            }
            else
            {
                M_root()=M_copy(x.M_root(),this->M_header);
                M_leftmost()=S_minimum(M_root());
                M_rightmost()=S_maximum(M_root());
                M_node_count=x.M_node_count;
            }
        }

        return *this;
}


template<typename Key,typename Value,typename KeyOfValue,typename Compare>
typename Rb_tree<Key,Value,KeyOfValue,Compare>::iterator
Rb_tree<Key,Value,KeyOfValue,Compare>::
M_insert(Base_ptr a,Base_ptr b,const value_type & v)
{
    //x是新值插入点，y是x的父节点，v是插入值,z是新节点。
    Link_type x=(Link_type)a,y=(Link_type)b,z=nullptr;

    ///TODO:这里if语句应当总为ture
    //v总小于y的value？

    if(y==this->M_header||x!=nullptr||
        M_key_compare(KeyOfValue()(v),S_key(y)))
    {
        z=M_create_node(v);
        S_left(y)=z;

        if(y==this->M_header)
        {
            M_root()=z;
            M_rightmost()=z;
        }
        else if(y==M_leftmost())
        {
            M_leftmost()=z;
        }
    }
    else
    {
        z=M_create_node(v);
        S_right(y)=z;
        if(y==M_rightmost())
            M_rightmost()=z;
    }
    
    S_parent(z)=y;
    S_left(z)=S_right(z)=nullptr;
    rb_tree_rebalance_for_insert(z,this->M_header->parent);
    ++M_node_count;
    return iterator(z);
}

template<typename Key,typename Value,typename KeyOfValue,typename Compare>
void
Rb_tree<Key,Value,KeyOfValue,Compare>::
M_erase(Link_type x)
//删除子树，这是没有平衡的直接删除，应当只在clear函数中调用。
{
    //后序遍历，
    while(x!=nullptr)
    {
        M_erase(S_right(x));
        Link_type y=S_left(x);
        destory_node(x);
        x=y;
    }
}

template<typename Key,typename Value,typename KeyOfValue,typename Compare>
typename Rb_tree<Key,Value,KeyOfValue,Compare>::iterator
Rb_tree<Key,Value,KeyOfValue,Compare>::
insert_equal(const Value&v)
//我怎么记得新版本这里是直接用的lower_bound
{
    Link_type y=this->M_header,x=M_root();

    while(x!=nullptr)
    {
        y=x;
        x=M_key_compare(KeyOfValue()(v),S_key(x))?
            S_left(x):S_right(x);
    }

    return M_insert(x,y,v);
}

template<typename Key,typename Value,typename KeyOfValue,typename Compare>
std::pair<typename Rb_tree<Key,Value,KeyOfValue,Compare>::iterator,bool>
Rb_tree<Key,Value,KeyOfValue,Compare>::
insert_unique(const Value&v)
{
    Link_type y=this->M_header,x=M_root();
    bool comp=true;

    while(x!=nullptr)
    {
        y=x;
        comp=M_key_compare(KeyOfValue()(v),S_key(x));
        x=comp?S_left(x):S_right(x);
    }

    iterator j=iterator(y);//j为插入节点的父节点

    //true表示插入父亲节点的左边。
    if(comp)
    {
        //如果j是begin，那么应该直接插入，不能在减--j
        if(j==begin())
            return std::pair<iterator,bool>(M_insert(x,y,v),true);
        else
            --j;
    }

    //分析一下：
    //1.M_key_compare重载的应该是小于号
    //2.x指向要么等于j，要么在j的右节点。
    //3.这个if语句继续进行比较的是j和和x
    
    //综上
    //1.如果if通过，要么x和j指向相同同时j小于x，要么x在j的右节点同时j小于x
    //2.显然前者排除，所以得出结论，如果执行if，必然是x在j的右节点，同时两者值不同。

    if(M_key_compare(KeyOfValue()(*j),KeyOfValue()(v)))
        return std::pair<iterator,bool>(M_insert(x,y,v),true);
    
    //上面两个if都没有通过，说明存在相同的节点，返回j(相同的节点),false
    return std::pair<iterator,bool>(j,false);
}  

template<typename Key,typename Value,typename KeyOfValue,typename Compare>
typename Rb_tree<Key,Value,KeyOfValue,Compare>::iterator
Rb_tree<Key,Value,KeyOfValue,Compare>::
insert_unique(iterator position,const Value&v)
{
    if(position.M_node==this->M_header->left)//begin（）
    {
        if(size()>0&&
            M_key_compare(KeyOfValue()(v),S_key(position.M_node)))
        {
            return M_insert(position.M_node,position.M_node,v);
        }
        else
            return insert_unique(v).first;
    }
    else if(position.M_node==this->M_header)
    {
        if(M_key_compare(S_key(M_rightmost()),KeyOfValue()(v)))
        {
            return M_insert(nullptr,M_rightmost(),v);
        }
        else
            return insert_unique(v).first;
    }
    else
    {
        iterator before=position;
        --before;

        //在before和position之间
        if(M_key_compare(S_key(before.M_node),KeyOfValue()(v))&&
            M_key_compare(KeyOfValue()(v),S_key(position.M_node)))
        {
            if(S_right(before.M_node)==nullptr)
                return M_insert(nullptr,before.M_node,v);
            else
                return M_insert(position.M_node,position.M_node,v);
        }
        else
            return insert_unique(v).first;
    }
}

template<typename Key,typename Value,typename KeyOfValue,typename Compare>
typename Rb_tree<Key,Value,KeyOfValue,Compare>::iterator
Rb_tree<Key,Value,KeyOfValue,Compare>::
insert_equal(iterator position,const Value&v)
{
    if(position.M_node==this->M_header->left)
    {
        if(size()>0&&//position不大于v
            !M_key_compare(S_key(position.M_node),KeyOfValue()(v)))
            return M_insert(position.M_node,position.M_node,v);
        else
            return insert_equal(v);
    }
    else if(position.M_node==this->M_header)
    {
        if(!M_key_compare(KeyOfValue()(v),S_key(M_rightmost())))
            return M_insert(nullptr,M_rightmost(),v);
        else
            return insert_equal(v);
    }
    else
    {
        iterator before=position;
        --before;

        if(!M_key_compare(KeyOfValue()(v),S_key(before.M_node))&&
            !M_key_compare(S_key(position.M_node),KeyOfValue()(v)))
            if(S_right(before.M_node)==nullptr)
                return M_insert(nullptr,before.M_node,v);
            else
                return M_insert(position.M_node,position.M_node,v);
        else
            return insert_equal(v);
    }
}

template<typename Key,typename Value,typename KeyOfValue,typename Compare>
typename Rb_tree<Key,Value,KeyOfValue,Compare>::iterator
Rb_tree<Key,Value,KeyOfValue,Compare>::
erase(iterator position)
{
    if(position==end())return end();

    iterator successor=position;
    ++successor;
    rb_tree_node_base* y=rb_tree_rebalance_for_erase(
                                            get_M_node(position),
                                            this->M_header->parent,
                                            this->M_header->left,
                                            this->M_header->right
                                                );
    destory_node((Link_type)y);
    --M_node_count;
    return successor;
}

template<typename Key,typename Value,typename KeyOfValue,typename Compare>
typename Rb_tree<Key,Value,KeyOfValue,Compare>::size_type
Rb_tree<Key,Value,KeyOfValue,Compare>::
erase(const Key&x)
{
    std::pair<iterator,iterator> p=equal_range(x);
    size_type n=std::distance(p.first,p.second);
    erase(p.first,p.second);
    return n;
}

template<typename Key,typename Value,typename KeyOfValue,typename Compare>
typename Rb_tree<Key,Value,KeyOfValue,Compare>::Link_type
Rb_tree<Key,Value,KeyOfValue,Compare>::
M_copy(Link_type x,Link_type p)//拷贝一个子树。使用递归算法。
{
    Link_type top=M_clone_node(x);
    top->parent=p;

    try
    {
        if(x->M_right!=nullptr)
            top->M_right=M_copy(S_right(x),top);//递归
        p=top;
        x=S_left(x);

        while(x!=nullptr)
        {
            Link_type y=M_clone_node(x);
            p->M_left=y;
            y->M_parent=p;
            if(x->M_right!=nullptr)
                y->M_right=M_copy(S_right(x),y);

            p=y;
            x=S_left(x);
        }
    }
    catch(...)
    {
        M_erase(top);
        throw;
    }
    
    return top;
}

template<typename Key,typename Value,typename KeyOfValue,typename Compare>
typename Rb_tree<Key,Value,KeyOfValue,Compare>::iterator
Rb_tree<Key,Value,KeyOfValue,Compare>::
erase(iterator first,iterator last)
{
    if(first==begin()&&last==end())
    {
        clear();
        return end();
    }
    else
    {
        while(first!=last)
            erase(first++);
        return last;
    }
}

template<typename Key,typename Value,typename KeyOfValue,typename Compare>
typename Rb_tree<Key,Value,KeyOfValue,Compare>::iterator
Rb_tree<Key,Value,KeyOfValue,Compare>::
find(const key_type&k)
{
    Link_type y=this->M_header,x=M_root();//y是last node while is not less than k

    //y指向x的下一个迭代器
    while(x!=nullptr)
        //如果x>=k就向左，同时为了保持y是x下一个迭代器，y刷新
        //为什么不M_key_compare(k,x)?因为那样的话是 > 而我们需要的是 >=
        if(!M_key_compare(S_key(x),k))
            y=x,x=S_left(x);
        else
            x=S_right(x);

    iterator j=iterator(y);

    //j如果是end，显然直接返回end，
    //所求j应该>=k,如果k<j取真，说明 j>k 不存在k这个节点，
    return (j==end()||M_key_compare(k,KeyOfValue()(*j)))?
        end():j;
}

template<typename Key,typename Value,typename KeyOfValue,typename Compare>
typename Rb_tree<Key,Value,KeyOfValue,Compare>::size_type
Rb_tree<Key,Value,KeyOfValue,Compare>::
count(const Key&k)const
{
    std::pair<iterator,iterator> p=equal_range(k);
    size_type n=0;
    std::distance(p.first,p.second,n);
    return n;
}

template<typename Key,typename Value,typename KeyOfValue,typename Compare>
typename Rb_tree<Key,Value,KeyOfValue,Compare>::iterator
Rb_tree<Key,Value,KeyOfValue,Compare>::
lower_bound(const Key&k)
{
    Link_type y=this->M_header,x=M_root();

    //这部分和find一致
    while(x!=nullptr)
        if(!M_key_compare(S_key(x),k))
            y=x,x=S_left(x);
        else
            x=S_right(x);
    
    return iterator(y);
}

template<typename Key,typename Value,typename KeyOfValue,typename Compare>
typename Rb_tree<Key,Value,KeyOfValue,Compare>::iterator
Rb_tree<Key,Value,KeyOfValue,Compare>::
upper_bound(const Key&k)
{
    Link_type y=this->M_header,x=M_root();

    //改成了M_key_compare(k,S_key(x))而已
    while(x!=nullptr)
        if(M_key_compare(k,S_key(x)))
            y=x,x=S_left(x);
        else
            x=S_right(x);
    
    return iterator(y);
}

template<typename Key,typename Value,typename KeyOfValue,typename Compare>
typename Rb_tree<Key,Value,KeyOfValue,Compare>::iterator
Rb_tree<Key,Value,KeyOfValue,Compare>::
get_val(size_t x)
{
    Link_type y=M_root();

    while (y!=nullptr)
    {
        if( (y->left==nullptr?0:y->left->node_count)+1 == x)
            break;
        else if( (y->left==nullptr?0:y->left->node_count) >= x)
            y=S_left(y);
        else
        {
            x-= (y->left==nullptr?0:y->left->node_count) +1;
            y=S_right(y);
        }
    }
    
    return y==nullptr?end():iterator(y);
}

template<typename Key,typename Value,typename KeyOfValue,typename Compare>
typename Rb_tree<Key,Value,KeyOfValue,Compare>::size_type
Rb_tree<Key,Value,KeyOfValue,Compare>::
get_rank(const key_type&x)
{
    Link_type y=M_root();
    size_type rank=1;

    while(y!=nullptr)
    {
        if(!M_key_compare(S_key(y),x))//x<=S_key(y)
            y=S_left(y);
        else
        {
            rank+=(y->left==nullptr?0:y->left->node_count)+1;
            y=S_right(y);
        }
    }

    return rank;
}

template<typename Key,typename Value,typename KeyOfValue,typename Compare>
std::pair<typename Rb_tree<Key,Value,KeyOfValue,Compare>::iterator,typename Rb_tree<Key,Value,KeyOfValue,Compare>::iterator>
Rb_tree<Key,Value,KeyOfValue,Compare>::
equal_range(const Key&k)
{
    return std::pair<iterator,iterator>(lower_bound(k),upper_bound(k));
}

inline int black_count(rb_tree_node_base*node,rb_tree_node_base*root)
{
    if(node==0)
        return 0;
    else
    {
        int bc=node->color==BLACK?1:0;
        if(node==root)
            return bc;
        else
            return bc+black_count(node->parent,root);
    }
}


template<typename Key,typename Value,typename KeyOfValue,typename Compare>
bool
Rb_tree<Key,Value,KeyOfValue,Compare>::
__rb_verify()
{
    if(M_node_count==0||begin()==end())
        return M_node_count==0&&begin()==end()&&
            this->M_header->M_left==this->M_header&&this->M_header->M_right==this->M_header;
    
    int len=black_count(M_leftmost(),M_root());

    for(iterator it=begin();it!=end();++it)
    {
        Link_type x=(Link_type)it.M_node;
        Link_type L=S_left(x);
        Link_type R=S_right(x);

        if(x->color==RED&&((L!=nullptr&&L->color==RED)||
        (R!=nullptr&&R->color==RED)))
            return false;
        
        if(L!=nullptr&&M_key_compare(S_key(x),S_key(L)))
            return false;
        
        if(R!=nullptr&&M_key_compare(S_key(R),S_key(x)))
            return false;

        if(L==nullptr&&R==nullptr&&black_count(x,M_root())!=len)
            return false;
    }

    if(M_leftmost()!=rb_tree_node_base::get_min(M_root()))
        return false;
    
    if(M_rightmost()!=rb_tree_node_base::get_max(M_root()))
        return false;
    
    return true;
}

template<typename Key,typename Value,typename KeyofValue,typename Compare>
struct rb_tree:public Rb_tree<Key,Value,KeyofValue,Compare>
{
    typedef Rb_tree<Key,Value,KeyofValue,Compare> Base;
    
    rb_tree(const Compare&comp=Compare()) :Base(comp){}

    ~rb_tree(){}
};

}