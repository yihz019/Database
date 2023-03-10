#include "tokens.h"

Tokens::Tokens()
{
    _token = "";
    _type = 0;
}

Tokens::Tokens(string str, int type)
{
    _token = str;
    _type = type;
}

ostream& operator <<(ostream& outs, const Tokens& t)
{
    outs << "      |" << t._token << "|\n";
    return outs;
}

int Tokens::type() const
{
    return _type;
}

string Tokens::type_string() const
{
    switch (_type)
    {
        case -2:
            return "TOKEN_END"; 
            break;
        case 0:
            return "EMPTY";
            break;
        case 1:
            return "NUMBERS";
            break;
        case 2:
            return "ALPHA";
            break;
        case 3:
            return "SPACES";
            break;
        case 4:
            return "OPERATORS";
            break;
        case 5:
            return "PUNC";
            break;
        case 6:
            return "QUOTE";
            break;
        case 7:
            return "PAR";
            break;
        case 8:
            return "UNKNOWN";
            break;
    }
    return nullptr;
}

string Tokens::token_str() const
{
    return _token;
}