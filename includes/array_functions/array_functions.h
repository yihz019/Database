#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H 
#include <iostream>
#include <iomanip>
using namespace std;

// Signatures  
template<class T>
T* allocate(int capacity=3);                           //allocate 'capacity' / elements. / return array

template<class T>
T* reallocate(T* a, int size, int capacity);             //take array, resize it / return new array. / delete old array

template<class T>
void print_array(T* a, int size);    //prints (size/capacity) for debugging
                                                        
template <class T>
void print(T* a, unsigned int how_many);               //print array

template<class T>
T* search_entry(T* a, int size, const T& find_me);           //search for 'key' and returns address or pointer

template <class T>
int search(T* a, int size, const T& find_me);              //search for 'key' and returns index 

template <class T>
void shift_left(T* a, int& size, int shift_here);       //shift left take integer

template <class T>
void shift_left(T* a, int& size, T* shift_here);        //shift left, takes pointer

template <class T>
void shift_right(T *a, int &size, int shift_here);      //shift right that takes integer

template <class T>
void shift_right(T *a, int &size, T *shift_here);       //shift right that takes a pointer

template<class T>
void copy_array(T *dest, const T* src, int size);      //copy from src to dest

template<class T>
T* copy_array(const T *src, int size);                 // returns address of the copy of src 
 
template <class T>
string array_string(const T *a, int size);              //return array as a string

// -------------------------Definitions---------------------------

template<class T>
T* allocate(int capacity){
    T *p;
    p = new T[capacity];
    return p;
}  
  
template<class T>
T* reallocate(T* a, int size, int capacity){
    T *p = new T[capacity];
    copy_array(p, a, size);
    delete a;
    return p;
}        

template<class T>
void print_array(T* a, int size)
{   
    cout << " (" << setw(2) << size <<")" << " [";
    print(a,size);
    cout << " ]" << endl;
}

template <class T>
void print(T* a, unsigned int how_many){ //print array
    for (int i=0; i < how_many; i++, a++){
        cout <<setw(4) << *a;
    }
} 

template<typename T>
T* search_entry(T* a, int size, const T& find_me){ // returns the address of the item found, nullptr if not found.
    T index = search(a, size, find_me);
    T *ptr = a+index;
    if (*ptr == find_me)
    {
        return ptr;
    }
    else if (index < 0)
    {
        return nullptr;
    }
}

template <class T>
int search(T* a, int size, const T& find_me){ // returns the index of the item found or -1 if not found.
    T *walker = a;
    for (int i=0; i < size; i++, walker++){
        if (*walker == find_me){
            return i;
        }
    }
    return -1;
}

template <class T>
void shift_left(T* a, int &size, int shift_here){   
    T *here = a+shift_here;
    T *walker = a+shift_here+1;
    T *end = a+size-1;
    while(here != end)
    {
        *here = *walker;
        here++, walker++;             
    }
    size--;
}


template <class T>
void shift_left(T* a, int &size, T* shift_here){      //shift left from pointer pos
    T here = shift_here-a; 
    shift_left(a, size, here);
}

template <class T>
void shift_right(T *a, int &size, int shift_here){    
    T *walker = a+size-1;
    T *end = a+size;
    T *stop = a+shift_here;
    while (end != stop){
        *end = *walker;
        end--, walker--;
    }
    size++;
}


template <class T>
void shift_right(T *a, int &size, T* shift_here){  // get ptr, turn to index, shift
    T here = shift_here-a; 
    shift_right(a, size, here);
}

template<class T>
void copy_array(T *dest, const T* src, int size){
    for (int i=0 ; i < size; i++){
        *dest = *src;
        dest++, src++; 
    }
}

template <class T>
T* copy_array(const T *src, int size){
    T *walker = allocate<int>(size);
    copy_array(walker, src, size);
    return walker;
}

template <class T>
string array_string(const T *a, int size){
    string val;
    val = "          [";
    for (int i=0; i<size; i++){
        val += "   ";
        val += to_string(*a);
        a++;
    }
    val += "] [";
    val += to_string(size);
    val += "]";
    return val;
}


#endif // ARRAY_FUNCTIONS_H