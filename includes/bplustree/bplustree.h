#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include "btree_array_funcs.h"
using namespace std;


template <class T>
class BPlusTree
{
public:
    class Iterator{
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0):
                            it(_it), key_ptr(_key_ptr){}

        T operator *()
        {
            return it->data[key_ptr];
        }

        Iterator operator++(int un_used)
        {
            assert(it != NULL);
            Iterator hold;
            hold = it;
            if (key_ptr >= it->data_count-1)
            {
                it = it->next;
                key_ptr = 0;
                return hold;
            }
            key_ptr++;
            return *this;
        }
        Iterator operator++()
        {
            if (key_ptr >= it->data_count-1)
            {            
                it = it->next;
                key_ptr = 0;
            }
            else 
            {
                key_ptr++;
            }
            return *this;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs.it == rhs.it;
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs.it != rhs.it;
        }
        void print_Iterator(){
            if (it){
                cout<<"iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else{
                cout<<"iterator: NULL, key_ptr: "<<key_ptr<<endl;
            }
        }
        bool is_null(){return !it;}
        void info(){
            cout<<endl<<"Iterator info:"<<endl;
            cout<<"key_ptr: "<<key_ptr<<endl;
            cout<<"it: "<<*it<<endl;
        }

    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    BPlusTree(bool dups = false);
    BPlusTree(T *a, int size, bool dups = false);

    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    void copy_tree(const BPlusTree<T>& other);  //copy other into this object
    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node);

    void insert(const T& entry);   //insert entry into the tree
    void remove(const T& entry);   //remove entry from the tree
    void clear_tree();             //clear this object (delete all nodes etc.)

    bool contains(const T& entry) const; //true if entry can be found
    T& get(const T& entry);              //return a reference to entry
    const T& get(const T& entry)const;   //return a reference to entry
    T& get_existing(const T& entry);     //return a reference to entry
    Iterator find(const T& key);         //return an iterator to this key.
                                         //     NULL if not there.
    Iterator lower_bound(const T& key);  //return first that goes NOT BEFORE
                                         // key entry or next if does not
                                         // exist: >= entry
    Iterator upper_bound(const T& key);  //return first that goes AFTER key
                                         //exist or not, the next entry  >entry

    int size() const;                    //count the number of elements

    bool empty() const;                  //true if the tree is empty

    void print_tree(int level = 0,
                    ostream &outs=cout) const;
    friend ostream& operator<<(ostream& outs,
                               const BPlusTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid();
    string in_order();
    string pre_order();
    string post_order();

    Iterator begin();
    Iterator end();
    ostream& list_keys(Iterator from = NULL, Iterator to = NULL){
        if (from == NULL) from = begin();
        if (to == NULL) to = end();
        for (Iterator it = from; it != to; it++)
            cout<<*it<<" ";
        return cout;
    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                        //true if duplicate keys are allowed
    int data_count;                      //number of data elements
    T data[MAXIMUM + 1];                 //holds the keys
    int child_count;                     //number of children
    BPlusTree* subset[MAXIMUM + 2];      //subtrees
    BPlusTree* next;
    bool is_leaf() const
    {return child_count==0;}             //true if this is a leaf node

    T* find_ptr(const T& entry);         //return a pointer to this key.
                                         // NULL if not there.

    //insert element functions
    void loose_insert(const T& entry);   //allows MAXIMUM+1 data elements in
                                         //   the root
    void fix_excess(int i);              //fix excess in child i

    //remove element functions:
    void loose_remove(const T& entry);  //allows MINIMUM-1 data elements
                                        //  in the root

    BPlusTree<T>* fix_shortage(int i);  //fix shortage in child i
    // and return the smallest key in this subtree
    BPlusTree<T>* get_smallest_node();

    void get_smallest(T& entry);      //entry := leftmost leaf
    void get_biggest(T& entry);       //entry := rightmost leaf
    void remove_smallest(T& entry);    //remove the biggest child of tree->entry
    void transfer_left(int i);        //transfer one element LEFT from child i
    void transfer_right(int i);       //transfer one element RIGHT from child i
    BPlusTree<T> *merge_with_next_subset(int i); //merge subset i with  i+1

};




// =========================================================

template <class T>
BPlusTree<T>::BPlusTree(bool dups)
{
    data_count = 0;
    child_count = 0;
    dups_ok = dups;
    next = NULL;
    for (int i = 0; i < MAXIMUM + 2 ; i++)
    { 
        subset[i] = NULL;
    }   
}

template <class T>
BPlusTree<T>::BPlusTree(T *a, int size, bool dups )
{
    data_count = 0;
    child_count = 0;
    dups_ok = dups;
    next = NULL;

    for (int i = 0; i < size; i++)
    {
        insert(a[i]);
    }
}

//big three:
template <class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& other)
{   
    data_count = 0;
    child_count = 0;
    next = NULL;
    copy_tree(other); 
}

template <class T>
BPlusTree<T>::~BPlusTree()
{   
    clear_tree();   
}

template <class T>
BPlusTree<T>& BPlusTree<T>::operator =(const BPlusTree<T>& RHS)
{
    if (this != &RHS)
    {
        clear_tree();
        data_count = 0;
        child_count = 0;
        next = nullptr;
        copy_tree(RHS);
        return *this;
    }
    return *this;
}

template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other)//copy other into this object
{
    BPlusTree<T>*last_node = NULL;
    copy_tree(other,last_node);
}  

template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node)
{
    if (!other.empty())
    {
        copy_array(data,other.data,data_count,other.data_count);  
        if(!other.is_leaf()) 
        {        
            for (int i = 0; i < other.child_count; i++)
            {              
                subset[i] = new BPlusTree<T>(false);
                child_count++;
                subset[i]->copy_tree(*other.subset[i],last_node);      
            }
        }
        else 
        {
            if (last_node != NULL)
            {                
                last_node->next = this;
            }
            last_node = this;       //leftmost leaf
        }     
    }  
}

template <class T>
void BPlusTree<T>::insert(const T& entry)//insert entry into the tree
{
    loose_insert(entry);
    if (data_count > MAXIMUM)
    {
        BPlusTree<T> *grow = new BPlusTree<T>(false);
        copy_array(grow->data,data,grow->data_count,data_count);
        if (!is_leaf())
        { copy_array(grow->subset,subset,grow->child_count,child_count);}
        data_count = 0;
        child_count = 1;
        next = NULL;
        subset[0] = grow;
        fix_excess(0);
    }
}  

template <class T>
void BPlusTree<T>::remove(const T& entry) //remove entry from the tree
{
    loose_remove(entry);
    if (data_count == 0 && !is_leaf())
    {
        BPlusTree<T> *shrink = subset[0];
        copy_array(data,shrink->data,data_count,shrink->data_count);
        copy_array(subset,shrink->subset,child_count,shrink->child_count);            
        shrink->child_count = 0;
        shrink->data_count = 0;
        delete shrink;        
    }
} 

template <class T>
void BPlusTree<T>::clear_tree()//clear this object (delete all nodes etc.)
{
    data_count = 0;     
    for (int i = 0; i < child_count; i++)
    {
        subset[i]->clear_tree();
        subset[i]->child_count = 0;
        delete subset[i];
        subset[i] = NULL;         
    }
    child_count = 0;  
}            

template <class T>
bool BPlusTree<T>::contains(const T& entry) const//true if entry can be found
{
    int i = first_ge(data, data_count, entry);
    if (data[i] == entry && i < data_count)//entry we are looking for?
    {
        if (is_leaf())
        {
            return true;
        }
        else {
            return subset[i+1]->contains(entry);
        }
    }
    else 
    {
        if (is_leaf())
        {
            return false;
        }
        else 
        {
            return subset[i]->contains(entry);
        }
    }
    return false;
} 

template <class T>
T& BPlusTree<T>::get(const T& entry)  //return a reference to entry
{
   //If entry is not in the tree, add it to the tree
    if (!contains(entry))
    {   insert(entry);  }    
    assert(contains(entry));
    return get_existing(entry);
}

template <class T>
const T& BPlusTree<T>::get(const T& entry)const //return a reference to entry
{
    assert(contains(entry));
    return get_existing(entry);
}  

template <class T>  
T& BPlusTree<T>::get_existing(const T& entry) //return a reference to entry
{
    //assert that entry is not in the tree.
    assert(contains(entry));
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count && data[i] == entry);
    if (is_leaf())
    {
        if (found){
            return data[i];
        }
        else{
            assert(found);
        }
    }
    if (found) //inner node
        return subset[i+1]->get(entry);
        //or just return true?
    else //not found yet...
        return subset[i]->get(entry);
}    

template <class T> 
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T& key) //return an iterator to this key.   //     NULL if not there.
{
    int i = first_ge(data, data_count, key);
    if (data[i] == key && i < data_count)//entry we are looking for?
    {
        if (is_leaf())
        {
            return (Iterator(this, i));
        }
        else {
            return subset[i+1]->find(key);
        }
    }
    else 
    {
        if (is_leaf())
        {
            return Iterator(NULL);
        }
        else 
        {
            return subset[i]->find(key);
        }
    }
    return NULL;
}        

template <class T>                                
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T& key)  //return first that goes NOT BEFORE key entry or next if does not
{   // exist: >= entry
    BPlusTree<T> *ptr = get_smallest_node();
    while (ptr != NULL)
    {   
        for (int i = 0; i < ptr->data_count; i++)
        {
            if (key <= ptr->data[i])
            {
                return Iterator(ptr);
            }
        }
        ptr = ptr->next;
    }
    return Iterator(NULL);
}

template <class T> 
typename BPlusTree<T>::Iterator BPlusTree<T>:: upper_bound(const T& key)  //return first that goes AFTER key //exist or not, 
{// the next entry  > entry
    BPlusTree<T> *ptr = get_smallest_node();
    while (ptr != NULL)
    {   
        for (int i = 0; i < ptr->data_count; i++)
        {
            if (ptr->data[i] > key)
            {
                return Iterator(ptr);
            }
        }
        ptr = ptr->next;
    }
    return Iterator(NULL);
}


template <class T>
int BPlusTree<T>::size() const   //count the number of elements
{
    int count = 0;
    count += data_count;  
    for (int i = 0; i < child_count; i++)
    {   
        count += subset[i]->size(); 
    } 
    return count;
}

template <class T>
bool BPlusTree<T>::empty() const  //true if the tree is empty
{
    return (data_count == 0);
}

template <class T>
void BPlusTree<T>::print_tree(int level,ostream &outs) const
{
    if (!is_leaf() && child_count >= data_count)
    { //print last subtrtee
        subset[child_count-1]->print_tree(level+2);
    }         
    if (data_count > 0)
    {
        outs << setw(4*level+1) << "^\n";
        outs << setw(4*level+2) << "⎴\n";  
    }
    for (int i = data_count-1; i >= 0; i--) 
    {  //print data 
        outs << setw(4*level) << data[i] << endl;
        if (i == 0)
        { outs << setw(4*level+2) << "⎵\n";}  
        if (!is_leaf() && i < child_count)             
        { // print left subtree 
            subset[i]->print_tree(level+2);
        }       
    }
}

template <class T>
bool BPlusTree<T>::is_valid()
{ 
    //should check that every data[i] < data[i+1]
    // for (int i = 0; i < data_count; i++)
    // {
    //     if (is_le(data,data_count,data[i]))
    //     {
    //         if(is_le(subset[child_count-1]->data,subset[child_count-1]->data_count,data[data_count-1]));
    //         {
    //             if(is_gt(subset[i]->data,subset[i]->data_count,data[i]))
    //             {
                    
    //             }
    //         }
    //     }
    // }    
    //data[data_count-1] must be less than equal to 
    //  every subset[child_count-1]->data[ ]
    
    //every data[i] is greater than every subset[i]->data[ ]
    
    //B+Tree: Every data[i] is equal to subset[i+1]->smallest
    
    //Recursively validate every subset[i]

    return true; 
}

template <class T>
string BPlusTree<T>::in_order()
{
    string order = "";
    if (!is_leaf())
    { //print last subtrtee
        order += subset[0]->in_order();
    }         
    for (int i = 0; i < data_count; i++) 
    {  //print data 
        order += to_string(data[i]) + '|'; 
        if (!is_leaf() && i+1 < child_count)           
        { // print left subtree 
            order += subset[i+1]->in_order();
        }            
    }
    return order;
}

template <class T>
string BPlusTree<T>::pre_order()
{
    string order = "";
    for (int i = 0; i < data_count ; i++)
    {
        order += to_string(data[i]) + '|';
        if (!is_leaf())
        {
            order += subset[i]->pre_order();
        }
    }
    if (!is_leaf())
    {
        order += subset[data_count]->pre_order();
    }
    return order;
}

template <class T>
string BPlusTree<T>::post_order()
{
    string order = "";
    for (int i = 0; i < child_count; i++)
    {                  
        order += subset[i]->post_order();         
        if (i > 0)
        {
            order += to_string(data[i-1]) + '|';       
        }
    }
    if (is_leaf())
    {   
        for (int i = 0; i < data_count; i++)
        {
            order += to_string(data[i]) + '|';       
        }
    }
    return order;
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin()
{
    return Iterator(get_smallest_node());
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end()
{
    return Iterator(NULL);
}


///================ PRIVATE ===================
 //insert element functions
template <class T>
T* BPlusTree<T>::find_ptr(const T& entry) //return a pointer to this key.
{
    int i = first_ge(data, data_count, entry);
    if (data[i] == entry && i < data_count)//entry we are looking for?
    {
        if (is_leaf())
        {
            return &data[i];
        }
        else {
            return subset[i+1]->find_ptr(entry);
        }
    }
    else 
    {
        if (is_leaf())
        {
            return NULL;
        }
        else 
        {
            return subset[i]->find_ptr(entry);
        }
    }
    return NULL;
}


template <class T>
void BPlusTree<T>::loose_insert(const T& entry)   //allows MAXIMUM+1 data elements in  the root
{
    if (empty())
    {
        data[0] = entry;
        next = NULL;
        data_count++;
    }
    else {     
        int i = first_ge(data, data_count, entry);
        bool found = (data[i] == entry && i < data_count); //entry we are looking for?
        if (found && is_leaf() && !dups_ok)
        {
            data[i] = entry;
        }
        else if (found && is_leaf() && dups_ok)
        {
            data[i] = data[i] + entry;
        }
        else if (!found && is_leaf())
        {
            if (i == data_count)
            { attach_item(data,data_count,entry); }
            else {
                insert_item(data,i,data_count,entry);
            }

        }
        else if (found && !is_leaf()) {
            subset[i+1]->loose_insert(entry);
            if(subset[i+1]->data_count > MAXIMUM) 
            {
                fix_excess(i);
            }
        } 
        else if (!found && !is_leaf())
        {
            subset[i]->loose_insert(entry);
            if(subset[i]->data_count > MAXIMUM) 
            {
                fix_excess(i);
            }
        }
    }
}

template <class T>
void BPlusTree<T>::fix_excess(int i) //fix excess in child i //remove element functions:
{
    insert_item(subset,i+1,child_count, new BPlusTree<T>(false)); //create new branch
    subset[i+1]->next = NULL;
    split(subset[i]->data,subset[i]->data_count,subset[i+1]->data,subset[i+1]->data_count);
    if (!subset[i]->is_leaf())
    {
        split(subset[i]->subset,subset[i]->child_count,subset[i+1]->subset,subset[i+1]->child_count);
    }
    T removed;
    detach_item(subset[i]->data,subset[i]->data_count,removed);
    insert_item(data,i,data_count,removed);
    if (subset[i]->is_leaf())
    {
        insert_item(subset[i+1]->data,0,subset[i+1]->data_count,removed);        
        BPlusTree <T>* hold = subset[i]->next;
        subset[i]->next = subset[i+1];
        subset[i+1]->next = hold;
    }        
}

template <class T>
void BPlusTree<T>::loose_remove(const T& entry)  //allows MINIMUM-1 data elements//  in the root
{
    int i = first_ge(data, data_count, entry);
    bool found = (data[i] == entry && i < data_count);
    T deleted;
    if (is_leaf())
    {
        if(found)
        {
            delete_item(data,i,data_count,deleted);  
        }
    }
    else //not leaf
    {     
        if (!found)//not found yet. search in the next level:
        {
            subset[i]->loose_remove(entry);  
            if(subset[i]->data_count < MINIMUM) 
            { 
                fix_shortage(i); 
            } 
        }
        else // found key in an inner node
        {
            subset[i+1]->remove_smallest(data[i]);
            if (data[i] == entry && !subset[i+1]->is_leaf())
            {
                subset[i+1]->get_smallest(data[i]);   
            }
            if(subset[i+1]->data_count < MINIMUM) 
            { 
                fix_shortage(i+1); 
            } 
            // 1. shortage: find entry in data or subset[i+1]->data 
            //              and replace it with subset[i+1]->smallest
            // 2. no shortage: replace data[i] with subset[i+1]->smallest
            // assert(i < child_count-1);
        }
    }
}

template <class T>
BPlusTree<T>* BPlusTree<T>::fix_shortage(int i)  //fix shortage in child i// and return the smallest key in this subtree
{
    if (i < data_count && subset[i+1]->data_count > MINIMUM)
    {
        transfer_left(i+1);
        return subset[i];
    }
    else if (i > 0 && subset[i-1]->data_count > MINIMUM)
    {
        transfer_right(i-1);
        return subset[i-1];
    }
    else if (i < data_count) //there is left sibling 
    {
        merge_with_next_subset(i);
        return subset[i];
    }
    else 
    {
        merge_with_next_subset(i-1);
        return subset[i-1];
    }
    return subset[i];
}

template <class T>
BPlusTree<T>* BPlusTree<T>::get_smallest_node()
{
    if (!is_leaf())
    {
        return subset[0]->get_smallest_node();
    }
    return this;
}

template <class T>
void BPlusTree<T>::get_smallest(T& entry) //entry := leftmost leaf
{
    if (!is_leaf())
    {
        return subset[0]->get_smallest(entry);
    }
    entry = data[0];
}

template <class T>
void BPlusTree<T>::get_biggest(T& entry)     //entry := rightmost leaf
{
    if (!is_leaf())
    {
        return subset[data_count-1]->get_biggest(entry);
    }
    entry = data[data_count-1];
}

template <class T>
void BPlusTree<T>::remove_smallest(T& entry)   //remove the biggest child of tree->entry
{
    if (!is_leaf())
    {
        subset[0]->remove_smallest(entry);
        if(subset[0]->data_count < MINIMUM) 
        {
            fix_shortage(0); 
        }
    }       
    else{
        delete_item(data,0,data_count,entry);
    } 
}

template <class T>
void BPlusTree<T>::transfer_left(int i)       //transfer one element LEFT from child i
{
    if (0 < i && i < child_count && subset[i]->data_count > MINIMUM)
    {
        T sibling;
        T par;
        delete_item(data,i-1,data_count,par);
        
        delete_item(subset[i]->data,0,subset[i]->data_count,sibling);

        if (subset[i]->is_leaf())
        {
            attach_item(subset[i-1]->data,subset[i-1]->data_count,sibling); 
            insert_item(data,i-1,data_count,subset[i]->data[0]);
        }
        else 
        {
            attach_item(subset[i-1]->data,subset[i-1]->data_count,par);         
            insert_item(data,i-1,data_count,sibling);
        }

        if (!subset[i]->is_leaf())
        {    
            BPlusTree<T> *temp = subset[i];
            attach_item(subset[i-1]->subset,subset[i-1]->child_count,temp->subset[0]);    
            delete_item(subset[i]->subset,0,subset[i]->child_count,temp);
        }
    }
}

template <class T>
void BPlusTree<T>::transfer_right(int i)     //transfer one element RIGHT from child i
{
    if (i < child_count-1 && (subset[i]->data_count > MINIMUM))
    {    
        T sibling;
        T par;
        delete_item(data,i,data_count,par);
        detach_item(subset[i]->data,subset[i]->data_count,sibling);

        if (subset[i]->is_leaf())
        {
            insert_item(subset[i+1]->data,0,subset[i+1]->data_count,sibling);   
        }
        else 
        {
            insert_item(subset[i+1]->data,0,subset[i+1]->data_count,par);   
        }    
        
        insert_item(data,i,data_count,sibling);

        if (!subset[i]->is_leaf())
        {
            BPlusTree<T> *temp = subset[i];
            insert_item(subset[i+1]->subset,0,subset[i+1]->child_count,temp->subset[temp->child_count-1]);
            detach_item(subset[i]->subset,subset[i]->child_count,temp);
        }
    }
}

template <class T>
BPlusTree<T>* BPlusTree<T>::merge_with_next_subset(int i) //merge subset i with  i+1
{
    T key;
    delete_item(data,i,data_count,key);
    if (!subset[i]->is_leaf())
    {
        attach_item(subset[i]->data,subset[i]->data_count,key); 
    }
    if (subset[i+1]->data_count > 0)
    {   
        merge(subset[i]->data,subset[i]->data_count,subset[i+1]->data,subset[i+1]->data_count);  
        subset[i+1]->data_count = 0;    
    }    
    if (!subset[i+1]->is_leaf()){        
        merge(subset[i]->subset,subset[i]->child_count,subset[i+1]->subset,subset[i+1]->child_count);    
        subset[i+1]->child_count = 0;    
    }         
    BPlusTree<T> *temp = NULL;
    subset[i]->next = subset[i+1]->next;
    delete subset[i+1];
    delete_item(subset,i+1,child_count,temp); 
    return subset[i];
}




#endif //BPLUSTREE_H