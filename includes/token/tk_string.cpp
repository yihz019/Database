#include "tk_string.h"

TokenStr::TokenStr()
{
    _tkstr = "";
}

TokenStr::TokenStr(string token_str)
{
    _tkstr = token_str;
}
    
void TokenStr::Print(ostream &outs) const
{
    outs << _tkstr;
}