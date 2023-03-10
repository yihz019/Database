#ifndef INDEX_H
#define INDEX_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "../bplustree/multimap.h"
#include "../bplustree/map.h"

using namespace std;

struct Index
{
    vector<MMap<string,long>> indices;
    Index(){}
    void init_index(int fields)//creates index for every field of the record
    { // initializing
        for (int i = 0; i < fields; i++)
        {
            indices.push_back(MMap<string,long>());
        }
        //holad a struct of multimap , ana use []oper
    }
    void update(vector<string> fields_names, int record)
    {
        for (int i = 0; i < fields_names.size(); i++)
        {
            indices.at(i)[fields_names.at(i)] += record;
        }

        for (int i = 0; i < fields_names.size(); i++)
        {
            // cout << "mmap[" << fields_names[i] << "]: " << indices.at(i)[fields_names.at(i)] 
            // << endl << endl;;
        }
    }

    friend ostream& operator<<(ostream& outs, const Index& print_me)
    {
        for (int i = 0; i < print_me.indices.size(); i++)
        { 
            outs << print_me.indices.at(i) <<endl;
        }   
        return outs;
    }

};


#endif