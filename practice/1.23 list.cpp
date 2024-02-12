#include <iostream>
#include <algorithm>

#define ll long long

using namespace std;

template<typename T>
struct list_node{

typedef list_node<T>* ptr;
typedef list_node<T> Self;
typedef list_node<T>& reference;

    T key;
    ptr prior,next;
    list_node():prior(nullptr),next(nullptr){}
    list_node(const T& key):key(key),prior(nullptr),next(nullptr){}
};

template<typename T>
class list{

typedef list_node<T>* ptr;
typedef list_node<T> Self;
typedef list_node<T>& reference;

public:
    ptr header;//priori指尾，next指头

    list():header(new list_node<T>){
        header->prior = header->next = header;
    }

    ~list()
    {
        clear();
        delete header;
    }

    void clear()
    {
        while(header->next!= header)
        {
            ptr p = header->next;
            header->next = p->next;
            delete p;
        }
        header->prior = header->next = header;
    }

    template<typename Y>
    struct iteraor{
        ptr p;
        explicit iteraor(ptr x):p(p){}
        reference operator*()const{return p->key;}
        ptr operator->()const{return p;}
        bool operator==(const iteraor& rhs)const{return p == rhs.p;}
        bool operator!=(const iteraor& rhs)const{return p!= rhs.p;}

        iteraor<Y>& operator++(){
            p = p->next;
            return *this;
        }
        iteraor<Y> operator++(int){
            iteraor tmp = *this;
            p = p->next;
            return tmp;
        }
        
        iterator<Y>& operator--(){
            p=p->prior;
            return *this;
        }

        iterator<Y> operator--(int){
            iteraor tmp = *this;
            p = p->prior;
            return tmp;
        }

        iterator<Y>& operator+=(int n)
        {
            while(n--)
            {
                p = p->next;
            }
            return *this;
        }

        iterator<Y>& operator-=(int n)
        {
            while(n--)
            {
                p = ptr->prior;
            }
            return *this;
        }

        iterator<Y> opertator+(int n)
        {
            iterator tmp = *this;
            return tmp += n;
        }

        iterator<Y> operator-(int n)
        {
            iterator tmp = *this;
            return tmp -= n;
        }

        int operator-(iterator<Y> rhs)
        {
            iterator tmp=begin();
            int a=std::distance(tmp,rhs);
            tmp=begin();
            int b=std::distance(tmp,this->ptr);
            return b-a;
        }
    };

    iterator begin()const{return iterator(header->next);}
    iterator end()const{return iterator(header);}

    void push_back(const T& key)
    {
        ptr p=new list_node<T>(key);
        p->prior = header->prior;
        p->next = header;
        header->prior->next = p;
        header->prior = p;
    }

    void push_front(const T& key)
    {
        ptr p=new list_node<T>(key);
        p->prior = header;
        p->next = header->next;
        header->next->prior = p;
        header->next = p;
    }

    void pop_back()
    {
        ptr p=header->prior;
        p->prior->next = header;
        header->prior = p->prior;
        delete p;
    }

    void pop_front()
    {
        ptr p=header->next;
        p->next->prior = header;
        header->next = p->next;
        delete p;
    }
};
               

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

#ifdef LOCAL
    clock_t c1 = clock();
#endif

//-------------------------------------------------

    list<int> mylist;

    int n;
    cin>>n;

    for(int i=1;i<=n;++i)
    {
        int x;
        cin>>x;
        mylist.push_back(x);
    }

    sort(mylist.begin(),mylist.end());

    for(auto it=mylist.begin();it!=mylist.end();++it)
        cout<<*it<<' ';
//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
