#ifndef MY_STACK_H
#define MY_STACK_H

#include <iostream>
#include <iomanip>
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"

using namespace std;

template <typename T>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                     //give access to list to access _ptr
        Iterator(){_ptr = NULL;}                //default ctor
        Iterator(node<T>* p){_ptr =p;}          //Point Iterator to where
                                                //  p is pointing to

        operator bool()      // casting operator: true if _ptr not NULL
        {                    //       this turned out to be a pain!
            if (_ptr != nullptr)
                {return true;}
            return false;
        }

        T& operator*(){  // dereference operator
            return _ptr->_item;}

        const T& operator*() const{  // dereference operator
            return _ptr->_item;}

        T* operator->(){ // member access operator
            return &_ptr->_item; }

        const T* operator->() const{ // member access operator
            return &_ptr->_item; }

        bool is_null() // true if _ptr is NULL
        {
            if (_ptr == nullptr)
            {
                return true;
            }
            return false;
        }
        friend bool operator!=(const Iterator &left, const Iterator &right) // true if left != right
        {
            return left._ptr != right._ptr;
        }

        friend bool operator==(const Iterator &left, const Iterator &right) // true if left == right
        {
            return left._ptr == right._ptr;
        }

        Iterator &operator++() // member operator: ++it; or ++it = new_value
        {
            _ptr = _ptr->_next;             // i = 1,   j = ++i
            return *this;                  // j = 2, i = 2
        }
        friend Iterator operator++(Iterator &it, int unused) // friend operator: it++
        {
            assert(it._ptr !=NULL);
            Iterator hold;   // i = 1;   j = i++
            hold = it;       // j = 1, i = 2
            it = it._ptr->_next; 
            return hold;
        }

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<T>& copyMe);
    ~Stack();
    Stack<T>& operator=(const Stack<T>& RHS);
    T top();
    bool empty();
    void push(T item);
    T pop();
    template<typename TT>
    friend ostream& operator<<(ostream& outs, const Stack<TT>& printMe);
    Iterator begin() const;                   //Iterator to the head node
    Iterator end() const;                     //Iterator to NULL
    int size() const { return _size; }

private:
    node<T>* _top;
    int _size;
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//                            DEFINITIONS 
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
template <typename T>
Stack<T>::Stack(){ //defoulf CTOR
    _size = 0;
    _top = nullptr;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//                              BIG 3
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename T> 
Stack<T>::Stack(const Stack<T>& copyMe){
    _top = nullptr;
    _top = _copy_list(copyMe._top);
    _size = copyMe._size;
}

template <typename T> //Destructor
Stack<T>::~Stack(){
    _clear_list(_top);
    // delete [] _top;
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T>& RHS){
    if (this != &RHS)//check for self-reference 
    {
        _top = nullptr;
        _size = RHS._size;            // copy non-dynamic member variables.
        _top = _copy_list(RHS._top);   // copy node from rhs to this[object]
        return *this;
    }
    return *this;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename T>
T Stack<T>::top(){
    return _top->_item;
}

template <typename T>
bool Stack<T>::empty(){
    if (_top == nullptr){
        return true;
    }
    return false;
}
    
template <typename T>
void Stack<T>::push(T item){
    _size += 1; 
    _top = _insert_head(_top, item);
}
    
template <typename T>
T Stack<T>::pop(){
    if (_top != nullptr){
        _size -= 1; 
        return (_delete_node(_top, _top)); 
    }
    return T();
}

template<typename TT>
ostream& operator<<(ostream& outs, const Stack<TT>& printMe)
{
    outs << "Stack:";
    _print_list(printMe._top);
    return outs;
}
 
template <typename T>
typename Stack<T>::Iterator Stack<T>::begin() const //Iterator to the head node
{
    return Iterator(_top);
}
    
template <typename T>
typename Stack<T>::Iterator Stack<T>::end() const  //Iterator to NULL
{
    return Iterator(nullptr);
}



#endif // MY_STACK_H