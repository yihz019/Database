#ifndef TOKENK_STRING_H
#define TOKENK_STRING_H
#include <iostream>
#include "token.h"

using namespace std;

class TokenStr: public Token
{
public:
    TokenStr();
    TokenStr(string token_str);
    
    string get_tkstr() const {return _tkstr;}

    void Print(ostream &outs) const;

    TOKEN_TYPES TypeOf(){ //return type
        return TK_STRING;
    }

private:
    string _tkstr;
};


#endif // TK_STRING_H
