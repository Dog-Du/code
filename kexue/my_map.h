
//封装红黑树成map

#include "E:\program\code\kexue\my_rb_tree.h"

namespace my_map {

template<typename Key,typename Tp,
        typename Compare=std::less<Key>>
class map{
public:
        typedef Key key_type;
        typedef Tp data_type;
        typedef Tp mapped_type;
        typedef std::pair<const Key,Tp> value_type;
        typedef Compare key_compare;
        
private:

        struct  value_compare//仿函数，作用KeyOfValue的值，提出比较值
        {
        friend class map<Key,Tp,Compare>;
        public:
                const key_type& operator()(const value_type&x)const{
                        return x.first;
                }
        };

private:
        //red-black tree representing map
        typedef my_rb_tree::Rb_tree<key_type,value_type,
                value_compare,key_compare> Rep_type;
        
        Rep_type M_t;

public:
        typedef typename Rep_type::pointer pointer;
        typedef typename Rep_type::reference reference;
        typedef typename Rep_type::iterator iterator;

        typedef typename Rep_type::size_type size_type;
        typedef typename Rep_type::difference_type difference_type;

        map():M_t(Compare()){}

        explicit map(const Compare&comp):
                M_t(comp){}

        map(const map<Key,Tp,Compare>&x):M_t(x.M_t){}
        map<Key,Tp,Compare>&
                operator=(const map<Key,Tp,Compare>&x)
        {
                M_t=x.M_t;
                return *this;
        }        


private:
        key_compare key_comp() const {return M_t.key_comp();}
        value_compare value_compare() const {return value_compare(M_t.key_comp());}

public:

        iterator begin() {return M_t.begin();}
        iterator end() {return M_t.end();}
        bool empty() const {return M_t.empty();}
        size_type size() const {return M_t.size();}
        size_type max_size() const {return M_t.max_size();}

        Tp& operator[](const key_type&k)
        {
                iterator i=lower_bound(k);
                if(i==end()||key_comp()(k,(*i).first))
                        i=insert(i,value_type(k,Tp()));
                return (*i).second;
        }

        void swap(map<Key,Tp,Compare>&x){M_t.swap(x.M_t);}

        std::pair<iterator,bool> insert(const value_type&x)
        {return M_t.insert_unique(x);}

        iterator insert(iterator position,const value_type&x)
        {
                return M_t.insert_unique(position,x);
        }

        iterator erase(iterator position){return M_t.erase(position);}
        size_type erase(const key_type&x){return M_t.erase(x);}
        iterator erase(iterator first,iterator second)
        {
                return M_t.erase(first,second);
        }

        void clear(){M_t.clear();}

        iterator find(const key_type&x){return M_t.find(x);}

        size_type count(const key_type&x){
                return M_t.find(x)==M_t.end()?0:1;
        }

        iterator lower_bound(const key_type&x){return M_t.lower_bound(x);}
        iterator upper_bound(const key_type&x){return M_t.upper_bound(x);}

        std::pair<iterator,iterator> equal_range(const key_type&x){
                return M_t.equal_range(x);
        }

        bool operator==(const map<Key,Tp,Compare>&x){
                return x.M_t==M_t;
        }
};

}