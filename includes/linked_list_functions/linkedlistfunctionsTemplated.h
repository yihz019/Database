#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include "../node/node.h"
using namespace std;

//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head);

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head);

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key);

template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this);

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this);

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this);

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>*& head, node<T>* prev_to_this);

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this);

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head);

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);

//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head);

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos);

// Last Node in the list
template <typename T>
node<T> *_last_node(node<T> *head);



//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//                              DEFINITIONS
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head){
    node<T> *walker = head; // point walker to start of the head
    cout << "Head->";
    while (walker != nullptr) //while not end of link_list
    {
        cout << *walker; //print item
        walker = walker->_next; //move walker towards
    }
    cout << "|||" << endl;
}

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head){
    node<T> *walker = head; 
    walker = _last_node(head); // point walker to end of list
    while (walker != head) //while not end of link_list
    {
        cout << *walker; //print item
        walker = _previous_node(head, walker); //move walker backwards
    }
    cout << *walker; //print node that head is pointing to
    cout << "|||" << endl;

}

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key){
    node <T>* found = head;
    if(head != nullptr){ //if list is not empty 
        while(found != nullptr){
            if (found->_item == key){
                return found;
            }
            found = found->_next; // if node's item is not = key, move forward
        }
        return nullptr; //nothing found
    }
    return nullptr; //empty found 

}

template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this){
    node<T> *temp = new node<T>(insert_this, head);// 1. create new node [temp]
    if (head == nullptr) //empty list 
    {        
        head = temp;
        return head;
    }
    // not empty 
    // temp->_next = head;    // 2. temp's next points to headptr (where the headptr is pointing to)
    // temp->_prev = nullptr; // 3. temp's prev point to null
    head->_prev = temp;     // 4. point first node to new node 
    head = temp;           // 5. headptr points to where temp is pointing to:
    return head;
}

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this)
{    
    if (head == nullptr) // check if head is not null [if list is not empty]
    {
        return _insert_head(head, insert_this);
    }
    else if (after_this->_next == nullptr) { //insert after the last node
        node<T>*temp = new node<T>(insert_this);
        temp->_next = nullptr;
        temp->_prev = after_this;
        after_this->_next = temp;
        return temp;
    }
    else {
        node<T>*temp = new node<T>(insert_this); //create new node
        node<T>*walker = after_this->_next;
        temp->_next = after_this->_next;
        temp->_prev = after_this;
        after_this->_next = temp;
        walker->_prev = temp;
        return temp;
    }
    return nullptr;
}

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this)
{
    if (_previous_node(head, before_this) == nullptr) //if before first node
    {
        return _insert_head(head, insert_this);
    }
    else {
        node<T>*temp = new node<T>(insert_this);
        node<T>*walker = _previous_node(head, before_this);
        
        temp->_next = before_this;
        temp->_prev = walker;
        before_this->_prev = temp;
        walker->_next = temp;
        return temp;
    }
    return nullptr;
}

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>*& head,node<T>* prev_to_this){
    
    node<T> *walker = head; // point walker to search for prev_to_this [pos]

    while (walker != nullptr && head != prev_to_this) // search rest of list if it's not first node
    {
        if (walker->_next == prev_to_this) // if next of me is prev_this
        {
            return walker; // return me
        }
        walker = walker->_next; // else keep going
    }
    return nullptr; // if node not in the list or is first node of the list
}

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this){
    T temp; // to save deleted item 
    node<T> *walker = head;

    if (walker == nullptr){  //empty list  
        return T();
    }

    else 
    {
        while (walker != nullptr)
        {   
            if (walker == delete_this)
            { //if first node 
                if (walker->_prev == nullptr && walker->_next != nullptr) 
                {
                    node<T>* next = delete_this->_next;
                    next->_prev = nullptr;
                    head = next;
                    temp = walker->_item;
                    delete walker;
                    return temp;
                }
                //one node
                else if(walker->_prev == nullptr && walker->_next == nullptr) 
                {   
                    temp = walker->_item;                
                    head = nullptr;
                    delete walker;
                    return temp;
                }
                else if(walker->_prev != nullptr &&  walker->_next == nullptr ) 
                {  //last node
                    node<T>* prev = _previous_node(head, delete_this);
                    prev->_next = nullptr;
                    temp = walker->_item;
                    delete walker;
                    return temp;
                }
                //normal deleting 
                node<T>* prev = _previous_node(head, walker);
                node<T>* next = walker->_next;
                prev->_next = next;
                next->_prev = prev;
                temp = walker->_item;
                delete walker;
                return temp;
            }
            walker = walker->_next;
        }
    }
    return temp;
}

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head){
    node<T>*temp = nullptr;
    if(head != nullptr)
    {
        node<T>*walker = head;
        _insert_head(temp, walker->_item);
        walker = walker->_next;
        node<T>*walker2 = temp;
        while(walker != nullptr)
        {
            walker2 = _insert_after(temp, walker2, walker->_item);
            walker = walker->_next;
        }
        return temp;
    }
    return nullptr;
}

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src){
    dest = _copy_list(src);
    return _last_node(dest);
}

//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head){
    node<T> *walker = head;
    node<T> *temp = head;

    if (head != nullptr)
    {
        while (walker->_next != nullptr){
            temp = temp->_next;
            _delete_node(head,walker);
            walker = temp;
        }
        _delete_node(head,walker);
        temp = nullptr;
        head = nullptr;
    }
}

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos){
    node<T> *walker = head;
    int count = 0; // counter
    if (pos == 0){
        return head->_item;
    }
    else{
        while (walker != nullptr)
        {
            if (count == pos){ // when counter matches pos
                return walker->_item; // return item at that pos
            }
            walker = walker->_next; // else keep going (searching)
            count++;
        }
    }
    assert(pos > count); //pos not in list
    return head->_item;
}

// Last Node in the list
template <typename T>
node<T> *_last_node(node<T> *head){
    node<T> *walker = head;
    if (head != nullptr)
    {
        while (walker->_next != nullptr) // move till the end of list
        {
            walker = walker->_next; // walker hits null
        }
        return walker;
    }
    return nullptr;
}


#endif // LINKED_LIST_FUNCTIONS_H