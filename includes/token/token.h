#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <iomanip>
#include "constants.h"
using namespace std;

class Token
{
public:
    Token();
    virtual TOKEN_TYPES TypeOf(){
        cout<<"You should never see me!"<<endl;
        return TOKEN;
    }
    
    virtual void Print(ostream& outs=cout) const;
    friend ostream& operator <<(ostream& outs, const Token* token);
    friend ostream& operator <<(ostream& outs, const Token& token);

};


#endif