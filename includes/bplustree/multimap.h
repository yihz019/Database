#ifndef MULTIMAP_H
#define MULTIMAP_H

#include <iostream>
#include <iomanip>
#include "mpair.h"
#include "bplustree.h"
#include "btree_array_funcs.h"
using namespace std;

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it=NULL)
        {
            _it = it;
        }
        Iterator operator ++(int unused)
        {
            assert(_it != NULL);
            Iterator hold = _it;
            _it++;
            return hold;
        }
        Iterator operator ++()
        {
            _it++;
            return *this;
        }
        MPair<K, V> operator *()
        {
            return *_it;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs._it == rhs._it;
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs._it != rhs._it;
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap();

//  Iterators
    Iterator begin();
    Iterator end();

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
    const vector<V>& operator[](const K& key) const;
    vector<V>& operator[](const K& key);
    vector<V>& at(const K& key);

//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();

//  Operations:
    bool contains(const K& key) const ;
    vector<V> &get(const K& key);

    Iterator find(const K& key);
    int count(const K& key);
    Iterator lower_bound(const K& key);
    Iterator upper_bound(const K& key);
    Iterator equal_range(const K& key);

    bool is_valid();
    void print_lookup() const;

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

private:
    BPlusTree<MPair<K, V> > mmap;
};

//============================== DEFINITIONS =============================
template <typename K, typename V>
MMap<K,V>::MMap()
{}

//  Iterators
template <typename K, typename V>
typename MMap<K,V>:: Iterator MMap<K,V>::begin()
{
    return mmap.begin();
}

template <typename K, typename V>
typename MMap<K,V>:: Iterator MMap<K,V>::end()
{
    return mmap.end();
}

//  Capacity
template <typename K, typename V>
int MMap<K,V>::size() const
{
    return mmap.size();
}

template <typename K, typename V>
bool MMap<K,V>::empty() const
{
    return mmap.empty();
}

//  Element Access
template <typename K, typename V>
const vector<V>& MMap<K,V>::operator[](const K& key) const
{
    assert(mmap.contains(key));
    return mmap.get_existing(key).value_list;;
}

template <typename K, typename V>
vector<V>& MMap<K,V>::operator[](const K& key)
{
    return at(key);
}

template <typename K, typename V>
vector<V>& MMap<K,V>::at(const K& key) 
{
    return get(key);
}

//  Modifiers
template <typename K, typename V>
void MMap<K,V>::insert(const K& k, const V& v)
{
    mmap.insert(MPair<K,V>(k,v));
}

template <typename K, typename V>
void MMap<K,V>::erase(const K& key)
{
    mmap.remove(key);
}

template <typename K, typename V>
void MMap<K,V>::clear()
{
    mmap.clear_tree();
}

//  Operations:
template <typename K, typename V>
bool MMap<K,V>::contains(const K& key) const 
{
    return mmap.contains(key);
}

template <typename K, typename V>
vector<V>& MMap<K,V>::get(const K& key)
{
    return mmap.get(key).value_list;
}

template <typename K, typename V>
typename MMap<K,V>:: Iterator MMap<K,V>::find(const K& key)
{
    return mmap.find(key);
}

template <typename K, typename V>
int MMap<K,V>::count(const K& key)
{}

template <typename K, typename V>
typename MMap<K,V>:: Iterator MMap<K,V>::lower_bound(const K& key)
{
    return mmap.lower_bound(key);
}

template <typename K, typename V>
typename MMap<K,V>:: Iterator MMap<K,V>::upper_bound(const K& key)
{
    return mmap.upper_bound(key);
}

template <typename K, typename V>
typename MMap<K,V>:: Iterator MMap<K,V>::equal_range(const K& key)
{}

template <typename K, typename V>
bool MMap<K,V>::is_valid()
{
    return mmap.is_valid();
}

template <typename K, typename V>
void MMap<K,V>::print_lookup() const
{    
    BPlusTree<MPair<K, V> > temp = mmap;
    MMap<K, V>::Iterator it = temp.begin();
    for (; it != temp.end(); it++)
    {
        cout << setw(15) << *it << endl;
    }
}


#endif //MULTIMAP_H