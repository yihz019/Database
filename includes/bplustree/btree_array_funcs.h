#ifndef BTREE_ARRAY_FUNCS_H
#define BTREE_ARRAY_FUNCS_H

#include <iomanip>
#include <vector>
#include "../array_functions/array_functions.h"
#include <algorithm>
using namespace std;

template <class T>
T maximal(const T& a, const T& b);                      //return the larger of the two items

template <class T>
void swap(T& a, T& b);  //swap the two items

template <class T>
int index_of_maximal(T data[ ], int n);                 //return index of the largest item in data

template <class T>
void ordered_insert(T data[ ], int& n, T entry);        //insert entry into the sorted array
                                                        //data with length n

template <class T>
int first_ge(const T data[ ], int n, const T& entry);   //return the first element in data that is
                                                        //not less than entry

template <class T>
void attach_item(T data[ ], int& n, const T& entry);    //append entry to the right of data

template <class T>
void insert_item(T data[ ], int i, int& n, T entry);    //insert entry at index i in data

template <class T>
void detach_item(T data[ ], int& n, T& entry);          //remove the last element in data and place
                                                        //it in entry

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry);   //delete item at index i and place it in entry

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2);   //append data2 to the right of data1

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2);   //move n/2 elements from the right of data1
                                                        //and move to data2

template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size);              //copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos = -1);  //print array data

template <class T>
bool is_gt(const T data[], int n, const T& item);       //item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item);       //item <= all data[i]

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator<<(ostream& outs, const vector<T>& list); //print vector list

template <typename T, typename U >
vector<T>& operator+=(vector<T>& list, const U& addme); //list.push_back addme

template <typename T>
vector<T>& operator+=(vector<T>& list, const vector<T>& addme); //list.push_back another list

template <typename T>
vector<T> intersection(vector<T>& list,const vector<T>& list2); //elements that the 2 list has in common

template <typename T>
vector<T> vector_union(vector<T>& list, const vector<T>& list2); //add both lists

//================================= DEFINITONS ======================================

template <class T>
T maximal(const T& a, const T& b)  //return the larger of the two items
{ return max(a,b); }

template <class T>
void swap(T& a, T& b)  //swap the two items
{
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
int index_of_maximal(T data[ ], int n)              //return index of the largest item in data
{
    T max ;
    int big ;
    for (int i = 0; i < n; i++)
    {
        big = i;
        max = data[i];
        if (max < data[i+1] && i+1 < n)    
        {
            big = i+1;
            max = data[i+1];
        }
    }
    return big;
}

template <class T>
void ordered_insert(T data[ ], int& n, T entry)     //insert entry into the sorted array data with length n
{
    int i = first_ge(data,n,entry);
    insert_item(data,i,n,entry);
}

template <class T>
int first_ge(const T data[ ], int n, const T& entry)   //return the first element in data that is not less than entry
{
    for(int i = 0; i < n; i++)
    {
        if (entry <= data[i])
        {
            return i;
        }
    }
    return n;
}


template <class T>
void attach_item(T data[ ], int& n, const T& entry)    //append entry to the right of data
{
    data[n] = entry;
    n++;
}

template <class T>
void insert_item(T data[ ], int i, int& n, T entry)   //insert entry at index i in data
{
    shift_right(data,n,i);
    data[i] = entry;
}

template <class T>
void detach_item(T data[ ], int& n, T& entry)  //remove the last element in data and place it in entry
{
    if (n > 0)
    { 
        entry = data[n-1];
        n--;
    }
}

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry)   //delete item at index i and place it in entry
{
    if (n > 0)
    {
        entry = data[i];
        shift_left(data,n,i); 
    }
}

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2)   //append data2 to the right of data1
{
    for (int i = 0; i < n2; i++)
    {
        data1[n1] = data2[i];
        n1++;
    }   
    n2 = 0;
}

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2)   //move n/2 elements from the right of data1  //and move to data2
{
    int mid = n1/2;
    n2 = 0;
    if (n1%2 == 0) //even
    {
        for (int i = mid; i < n1; i++)
        {
            data2[n2] = data1[i]; 
            n2++;       
        }
        n1 = mid;
    }
    else //odd
    {
        for (int i = mid+1; i < n1; i++)
        {
            data2[n2] = data1[i]; 
            n2++;       
        }
        n1 = mid+1;
    }
}

template <class T>
void copy_array(T dest[], const T src[], int& dest_size, int src_size)              //copy src[] into dest[]
{
    for(int i = 0; i < src_size; i++)
    {
        dest[i] = src[i];
    }    
    dest_size = src_size;
}

template <class T>
void print_array(const T data[], int n, int pos)  //print array data
{
    for (int i = 0; i < n; i++)
    {
        cout << data[i] << " ";
    }
    cout << endl;
}

template <class T>
bool is_gt(const T data[], int n, const T& item)       //item > all data[i]
{
    for (int i = 0 ; i < n; i++)
    {
        if (item < data[i])
        {
            return false;
        }
    }
    return true;
}

template <class T>
bool is_le(const T data[], int n, const T& item)       //item <= all data[i]
{
    for (int i = 0; i < n; i ++)
    {
        if (item >= data[i])
        {
            return false;
        }
    }
    return true; 
}

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list) //print vector list
{
    for (int i = 0; i < list.size(); i++)
    {
        outs << list.at(i) << " ";
    }
    return outs;
}

template <typename T, typename U >
vector<T>& operator +=(vector<T>& list, const U& addme) //list.push_back addme
{
    list.push_back(addme);
    return list;
}

template <typename T>
vector<T>& operator +=(vector<T>& list, const vector<T>& addme)//list.push_back another list
{
    for (int i = 0; i < addme.size(); i++)
    {
        list.push_back(addme.at(i));
    }
    return list;
}

template <typename T>
vector<T> intersection(vector<T>& list, const vector<T>& list2)//elements that the 2 list has in common
{
    vector<T> common;
    if (list.empty() && !list2.empty() || list2.empty() && !list.empty() || list2.empty() && list.empty() )
    {
        return vector<T>();
    }
    else    
    {    
        // cout << "\n\n================= INTERSECTION ===============\n\n";
        // cout << "lis1 :: " <<list <<endl;
        // cout << "list2:: " << list2 <<endl;
        for (int i = 0; i < list.size(); i++)
        {
            for (int j = 0; j < list2.size(); j++)
            {
                if (list.at(i) == list2.at(j))
                {
                    common.push_back(list.at(i));
                }
            }
        }
        sort(common.begin(), common.end());
    //    cout << "common " << common <<endl;

        return common;
    } 
    return vector<T>();
}

template <typename T>
vector<T> vector_union(vector<T>& list, const vector<T>& list2)//add both lists
{
    if (list.size() == 0 && !list2.empty())
    {
        // cout << __LINE__ <<endl;
        return list2;
    }
    else if (!list.empty() && list2.size() == 0)
    {
        // cout << __LINE__ <<endl;
        return list;
    }
    else
    {     
        // cout << "\n\n================= UNION ===============\n\n";
        // cout << "lis1 :: " <<list <<endl;
        // cout << "list2:: " << list2 <<endl;

        vector<T> u;
        u = list;   
        bool dups = false;
        for (int i = 0; i < list2.size(); i++)
        {
            for (int j = 0; j < list.size(); j++)
            {
                if (list.at(j) == list2.at(i))
                {
                    dups = true;
                }
            }
            if (!dups)
            {
                u.push_back(list2[i]);
            }
            dups = false;
        }    
        list = u;
        sort(list.begin(), list.end());
        // cout << "resul: " << list <<endl;
    }
    // cout << "lils union " <<list << endl<<endl <<endl;;
    return list;
}



#endif //BTREE_ARRAY_FUNCS_H