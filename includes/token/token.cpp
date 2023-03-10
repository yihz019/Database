#include "token.h"

Token::Token()
{}

void Token::Print(ostream &outs) const{
    outs<<"TOKEN Print: DON't ^%#$# call me again!"<<endl;
    //Blank
}

ostream& operator <<(ostream& outs, const Token* token){
    outs << *token;
    return outs;
}

ostream& operator <<(ostream& outs, const Token& token)
{
    token.Print(outs);
    return outs;
}
