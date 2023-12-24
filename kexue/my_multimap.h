//封装成multimap，可以通过洛谷P3369普通平衡树
#include "E:\program\code\kexue\my_rb_treev2.0.h"

namespace my_multimap {

template<typename Key,typename Tp,
        typename Compare=std::less<Key>>
class multimap{
public:
        typedef Key key_type;
        typedef Tp data_type;
        typedef Tp mapped_type;
        typedef std::pair<const Key,Tp> value_type;
        typedef Compare key_compare;
        
private:

        //仿函数，左右KeyOfValue,用来提取key，
        struct  value_compare
        {
        friend class multimap<Key,Tp,Compare>;
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

        multimap():M_t(Compare()){}

        explicit multimap(const Compare&comp):
                M_t(comp){}

        multimap(const multimap<Key,Tp,Compare>&x):M_t(x.M_t){}
        multimap<Key,Tp,Compare>&
                operator=(const multimap<Key,Tp,Compare>&x)
        {
                M_t=x.M_t;
                return *this;
        }        


private:
        key_compare key_comp() const {return M_t.key_comp();}
        value_compare value_compare() const {return value_compare(M_t.key_comp());}

public:
       // bool verify(){return M_t.__rb_verify();}
        iterator begin() {return M_t.begin();}
        iterator end() {return M_t.end();}
        bool empty() const {return M_t.empty();}
        size_type size() const {return M_t.size();}
        size_type max_size() const {return M_t.max_size();}

        void swap(multimap<Key,Tp,Compare>&x){M_t.swap(x.M_t);}

        std::pair<iterator,bool> insert_unique(const value_type&x)
        {return M_t.insert_unique(x);}

        iterator insert_unique(iterator position,const value_type&x)
        {return M_t.insert_unique(position,x);}

        iterator insert_equal(const value_type&x)
        {return M_t.insert_equal(x);}
        
        iterator insert_equal(iterator position,const value_type&x)
        {return M_t.insert_equal(position,x);}

        iterator erase(iterator position){return M_t.erase(position);}
        size_type erase(const key_type&x){return M_t.erase(x);}
        iterator erase(iterator first,iterator second)
        {return  M_t.erase(first,second);}
        void clear(){M_t.clear();}

        iterator find(const key_type&x){return M_t.find(x);}

        size_type count(const key_type&x)
        {
            if(find(x)==end())return 0;
            iterator upper=upper_bound(x);
            //没有和stl一样使用distance的原因：不能保证效率，这么做可以稳定获得logn的时间复杂度。
            return (upper==end()?size()+1:get_rank(upper->first) )-get_rank(x);
        }

        iterator lower_bound(const key_type&x){return M_t.lower_bound(x);}
        iterator upper_bound(const key_type&x){return M_t.upper_bound(x);}

        iterator get_val(size_t x){return M_t.get_val(x);}
        size_t get_rank(const key_type&x){return M_t.get_rank(x);}

        std::pair<iterator,iterator> equal_range(const key_type&x){
                return M_t.equal_range(x);
        }

        bool operator==(const multimap<Key,Tp,Compare>&x){
                return x.M_t==M_t;
        }
};

}