#ifndef TOKENS_H
#define TOKENS_H
#include <iostream>
#include <cstring>
#include "constants.h"

using namespace std;

class Tokens
{
public:
    Tokens();
    Tokens(string str, int type);
    friend ostream& operator <<(ostream& outs, const Tokens& t);
    int type() const;
    string type_string() const;
    string token_str() const;
private:
    string _token;
    int _type;
};

#endif // TOKEN_H