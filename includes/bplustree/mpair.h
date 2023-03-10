#ifndef MPAIR_H
#define MPAIR_H

#include <iostream>
#include <iomanip>
#include <vector>
#include "../../includes/bplustree/btree_array_funcs.h"
using namespace std;

template <typename K, typename V>
struct MPair{
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------
    MPair(const K& k=K())
    {
        key = k;
    }
    MPair(const K& k, const V& v)
    {
        key = k;
        value_list += v;
    }
    MPair(const K& k, const vector<V>& vlist)
    {
       value_list = vlist; 
    }
    //--------------------------------------------------------------------------------

    //You'll need to overlod << for your vector:
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me)
    {
        outs << print_me.key << ": ["<<  print_me.value_list << "]";
        return outs;
    }
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs.key == rhs.key);
    }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs.key < rhs.key );
    }
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    { 
        return (lhs.key <= rhs.key);
    }
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs.key > rhs.key);
    }
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        MPair<K, V> left;
        left.value_list = lhs.value_list;
        left.key = lhs.key;
        vector<V> right = rhs.value_list;
        for (int i = 0; i < right.size(); i++)
        {
            left.value_list.push_back(right.at(i));
        }
        return left;
    }
};


#endif //MPAIR_H