#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "typedefs.h"
#include "../bplustree/multimap.h"
#include "../bplustree/map.h"
#include "../binary_files/file_record.h"
#include "../binary_files/utilities.h"
#include "../queue/MyQueue.h"
#include "index.h"

#include "../shunting_yard/shunting_yard.h"
#include "../rpn/rpn.h"
#include "../token/constants.h"


using namespace std;

class Table {
public:
    Table();
    Table (const string &table_name); //takes table name of existing file 
    Table (const string &table_name, const vector<string> &fields); //takes table name and vector of info

    void insert_into(vector<string> row);// takes a vector of info and write into file 
   
    Table select(vectorstr fields,const string field, const string op, const string value) ;
    Table select(vectorstr fields,const Queue<Token*> postfix) ;
    Table select(vectorstr fields,const vectorstr condition) ;
    Table select(vectorstr fields) ;

    Table vector_to_table(const vector<long>& records, vector<string> fields) ;

    void select_all() const; //print everything from the file 
    void set_fields(vector<string> field_names); 
    vector<long> select_recnos() {return record_nums;}
    void set_records(vector<long> rec) 
    { record_nums = rec;}

    //ACCESSORS
    vector<string> get_fields() const {return field_names;}
    string table_name() const { return _table_name;}
    int last_record() const { return _last_record; }
    bool empty() const { return (_last_record == 0);}
    string serial_number() const{ return to_string(serial); }


    friend ostream& operator << (ostream& outs,const Table& t) 
    {
        int rec = 0;
        if (t.last_record() > 0)
        {
            rec = t.last_record()+1;
        }
        outs << "\nTable name: " << t.table_name() << ", records: " << rec << endl;
        t.select_all();
        return outs;
    }
    void reindex() ;

private:
    string _table_name;
    Index _indices; //indices map 
    vector<string> field_names;
    long _last_record;
    static int serial;
    vector<long> record_nums; 
    vector<int> fields_to_print; 
    Map<string, int> map; //record index of mmap that represent each field
};


#endif //TABLE_H