#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "../table/typedefs.h"
#include "constants.h"
#include "../bplustree/multimap.h"
#include "../tokenizer/stokenize.h"
#include "../bplustree/map.h"
#include "../queue/MyQueue.h"
#include "../bplustree/btree_array_funcs.h"
#include "../bplustree/bplustree.h"


using namespace std;

class Parser {
public:
    Parser();
    Parser(char* s);
    void set_string(char* str);
    int get_column(const string token);
    MMap<string,string> parse_tree(); 
    bool get_parse_tree(const Queue<string>& input); 
    void build_keyword_list(); //init input Queue
    bool fail() const { return _fail;}

    friend ostream& operator << (ostream& outs, const Parser p);

private:
    bool _fail;
    MMap<string,string> ptree;
    Map<string,int> keywords;
    Queue<string> input;
    int save = -1; //save state
    void make_table(); //or init table
    //---------------------------------
    // char _buffer[MAX_BUFFER];       //input string
    int _table[MAX_ROWS][MAX_COLUMNS];
};

#endif