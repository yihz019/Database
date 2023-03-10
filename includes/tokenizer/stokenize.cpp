#include "stokenize.h"

//reintroduce the _table static
int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

//Default CTOR
STokenizer::STokenizer()
{
    _pos = 0;
    make_table(_table);
}

STokenizer::STokenizer(char str[])
{
    _pos = 0;
    set_string(str);
    make_table(_table);
}

bool STokenizer::done()            //true: there are no more tokens
{        
    // cout << "_pos  " << _pos << endl;        
    // cout << "token " << _buffer[_pos] << endl;
    if(_pos <= strlen(_buffer))
    {
        return false;
    }
    return true;
}
    
bool STokenizer::more()            //true: there are more tokens
{
    return !done();
}
    
// extract one token (very similar to the way cin >> works)
STokenizer& operator >> (STokenizer& s, Tokens& t)
{
    int type; 
    string token;
    s.get_token(type,token); //grab next token
    t = Tokens(token,type); //construct token and cin
    return s;
}

//set a new string as the input string
void STokenizer::set_string(char str[])
{
    strcpy(_buffer,str); //load / reload buffer 
    _pos = 0; //resert pos to begining of buffer 
}


void STokenizer::make_table(int _table[][MAX_COLUMNS])
{   
    init_table(_table);//init whole table to -1 & states 
}

bool STokenizer::get_token(int& end_state, string& token)
{
    end_state = 0;
    token = "";
    int state = 0;
    int found = 0; //check type of token 
    if (strlen(_buffer) == 0)
    {
        _pos++;
        return true;
    }
    while (_pos <= strlen(_buffer))
    { //will not stop until end of buffer or fail state 
        if (_buffer[_pos] == '\0')
        {
            _pos++;
            // cout <<__LINE__ << endl;
            return false;
        }
        found = type(_buffer[_pos]);
        if (found == 6) //quotation mark
        {
            _pos++;//skip first quotation mark
            found = type(_buffer[_pos]);
            while ((found == 2 || found == 3 || found == 5 ) && _pos <= strlen(_buffer))
            { //if alpha or space keep going 
                token += _buffer[_pos];
                end_state = 6; //save current state
                _pos++;            
                found = type(_buffer[_pos]);
            }
            _pos++; //skip last quotation mark
            return true;
        }
        if (found == 7)
        { //operators    
            // while (found == 7 && _pos <= strlen(_buffer))
            {
                token += _buffer[_pos];
                end_state = 7; //save current state
                _pos++;            
                found = type(_buffer[_pos]);
            }
            return true;
        }
        if (found == 4)
        { //operators    
            while (found == 4 && _pos <= strlen(_buffer))
            {
                token += _buffer[_pos];
                end_state = 4; //save current state
                _pos++;            
                found = type(_buffer[_pos]);
            }
            return true;
        }
        found = type(_buffer[_pos]);
        if (found == 8)
        { //unknown    
            while (found == 8 && _pos <= strlen(_buffer))
            {
                token += _buffer[_pos];
                end_state = 8; //save current state
                _pos++;            
                found = type(_buffer[_pos]);
            }
            return true;
        }        
        found = _table[state][_buffer[_pos]];
        while(found != -1) 
        { //normal token
            if (found == 1 && _pos+3 <= strlen(_buffer))
            { //doubles                                                  
                //decimal point
                if (_table[5][_buffer[_pos+1]] == 5 && _table[1][_buffer[_pos+2]] == 1) 
                {
                    end_state = 1;
                    state = end_state;
                    token += _buffer[_pos]; //add first digit 
                    _pos++;
                    token += _buffer[_pos]; //add decimal point  
                    _pos++;
                    found = type(_buffer[_pos]);
                    while (found == 1 && _pos <= strlen(_buffer))
                    {
                        token += _buffer[_pos]; //add digit   
                        _pos++;
                        found = type(_buffer[_pos]);
                    }
                    return true;
                } //else normal adding digits 
            }
            if (found == 5) 
            {//punc
                token += _buffer[_pos]; 
                _pos++; 
                end_state = 5; //NORMAL PUNC
                state = end_state;
                if (_buffer[_pos-1] == '.')//added decimal point 
                {  //DOUBLE .2      
                    if (_table[1][_buffer[_pos]] != -1 && _pos <= strlen(_buffer))
                    {
                        token += _buffer[_pos]; //add digit 
                        _pos++;                                     
                        end_state = 1; //doubles
                        state = end_state;
                    }  
                } 
                found = _table[state][_buffer[_pos]];         
            }
            else //normal adding token 
            {
                token += _buffer[_pos];
                end_state = _table[state][_buffer[_pos]];
                state = end_state;       
                _pos++;
                found = _table[state][_buffer[_pos]];         
            }
        }
        return true;
    }
    return false;
}
