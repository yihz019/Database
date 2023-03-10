#ifndef RPN_H
#define RPN_H
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include "../token/token.h"
#include "../token/logical.h"
#include "../token/relational.h"
#include "../token/tk_string.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../table/index.h"
#include "../bplustree/btree_array_funcs.h"

using namespace std;

class RPN
{
public:
    RPN();
    RPN(const Queue<Token*>& q); //CTOR
    
    vector<long> eval();
    vector<long> operator()(const Index& indices, Map<string,int> fields);

    void get_index(const string field);

    void set_input(Queue<Token*> & token);
    void print(ostream &outs) const;

private:
    Index mmap;
    Queue<Token*> post; // Postfix     
    Map<string,int> map;
    int _pos;
};




#endif // RPN_H