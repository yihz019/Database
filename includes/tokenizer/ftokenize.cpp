#include "ftokenize.h"

FTokenizer::FTokenizer(char* fname)
{   
    _pos = 0;
    _blockPos = 0;
    _f.open(fname);
    if (!_f.fail())
    { 
        get_new_block();
        _more = true; 
    }
    else 
    {
        _more = false;
        cout << "FAILED to open file\n";
        exit(1);
    }
}

Tokens FTokenizer::next_token()
{    
    Tokens t;
    if (_stk.done())
    {               
        if(get_new_block())
        {
            _stk >> t;
            return t;
        }
        return Tokens();
    }
    _stk >> t;
    return t;   
}

bool FTokenizer::more()        //returns the current value of _more
{
    return _more;
}
    
int FTokenizer::pos()        //returns the value of _pos
{
    return _pos;
}
    
int FTokenizer::block_pos()    //returns the value of _blockPos
{
    return _blockPos;
}

FTokenizer& operator >> (FTokenizer& f, Tokens& t)
{
    t = Tokens();
    t = f.next_token();
    return f;
}

bool FTokenizer::get_new_block() //gets the new block from the file
{
    char block[MAX_BUFFER] ; //save block of text

    if (!_f.eof()) // not empty file or end of file
    {
        _f.read(block,MAX_BLOCK-1);
        // cout << "BLOCK\n" << block << endl;
        cout << "----- New Block ---------------------" << "["<<_f.gcount()<<"]" << " bytes\n";
        block[_f.gcount()] = '\0';
        _stk.set_string(block);
        _more = true; 
        return true;
    }
    cout << "*** END OF FILE ***\n";
    _more = false;
    return false; 
}