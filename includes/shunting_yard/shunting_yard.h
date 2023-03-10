#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "../token/token.h"
#include "../token/logical.h"
#include "../token/relational.h"
#include "../token/tk_string.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

using namespace std;

class ShuntingYard
{
public:
    ShuntingYard(); //Default CTOR
    ShuntingYard(const vector<string> &infix); //CTOR
    ShuntingYard(const Queue<Token*> &q); //CTOR

    Queue<Token*> postfix();
    Queue<Token*> postfix(Queue<Token*> infix);

    void infix(const Queue<Token*> &q); //set_input version 
    void print(ostream &outs) const;

private:
    Queue<Token*> inf; 

};

#endif // SHUNTING_YARD_H