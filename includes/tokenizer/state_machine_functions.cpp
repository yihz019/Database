#include "state_machine_functions.h"

int type (char s)
{
    for (int i = 0; i < strlen(DIGITS); i++)
    {
        if (DIGITS[i] == s)
        {
            return 1;
        }
    }
    for (int i = 0; i < strlen(ALFA); i++)
    {
        if (ALFA[i] == s)
        {
            return 2;
        }
    }
    for (int i = 0; i < strlen(SPACES); i++)
    {
        if (SPACES[i] == s)
        {
            return 3;
        }
    }
    for (int i = 0; i < strlen(OPERATORS); i++)
    {
        if (OPERATORS[i] == s)
        {
            return 4;
        }
    }
    for (int i = 0; i < strlen(PUNC); i++)
    {
        if (PUNC[i] == s)
        {
            return 5;
        }
    }
    if (QUOTE == s) 
    {
        return 6;
    }
    
    for (int i = 0; i < strlen(PAR); i++)
    {
        if (PAR[i] == s)
        {
            return 7;
        }
    }
    return 8; //unknown
}

void init_table(int _table[][MAX_COLUMNS])
{
    for (int i = 0 ; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            _table[i][j] = -1;
        }
    }
    //DIGITS
    mark_cells(0,_table,'0','9', 1);
    mark_cells(1,_table,'0','9', 1);

    //ALPHA
    mark_cells(0,_table,'a','z', 2);
    mark_cells(2,_table,'a','z', 2);
    mark_cells(0,_table,'A','Z', 2);
    mark_cells(2,_table,'A','Z', 2);
    //SPACES
    mark_cell(0,_table,' ', 3);
    mark_cell(0,_table,'\t', 3);
    mark_cell(0,_table,'\n', 3);
    mark_cell(0,_table,'\0', 3);
    mark_cell(3,_table,' ', 3);
    mark_cell(3,_table,'\t', 3);
    mark_cell(3,_table,'\n', 3);
    mark_cell(3,_table,'\0', 3);

    //OPERATORS
    mark_cell(0,_table,'>', 4);
    mark_cell(0,_table,'<', 4);
    mark_cell(0,_table,'=', 4);
    mark_cell(0,_table,'+', 4);
    mark_cell(0,_table,'-', 4);
    mark_cell(0,_table,'%', 4);
    mark_cell(0,_table,'&', 4);
    mark_cell(0,_table,'|', 4);
    mark_cell(0,_table,'*', 4);
    mark_cell(4,_table,'>', 4);
    mark_cell(4,_table,'<', 4);
    mark_cell(4,_table,'=', 4);
    mark_cell(4,_table,'+', 4);
    mark_cell(4,_table,'-', 4);
    mark_cell(4,_table,'%', 4);
    mark_cell(4,_table,'&', 4);
    mark_cell(4,_table,'|', 4);
    mark_cell(4,_table,'*', 4);
   
    //PUNC
    mark_cell(0,_table,'?', 5);
    mark_cell(0,_table,'.', 5);
    mark_cell(0,_table,',', 5);
    mark_cell(0,_table,':', 5);
    mark_cell(0,_table,';', 5);
    mark_cell(0,_table,'\'',5);
    mark_cell(0,_table,'`', 5);
    mark_cell(0,_table,'~', 5);
    mark_cell(0,_table,'!', 5);
    mark_cell(5,_table,'?', 5);
    mark_cell(5,_table,'.', 5);
    mark_cell(5,_table,',', 5);
    mark_cell(5,_table,':', 5);
    mark_cell(5,_table,';', 5);
    mark_cell(5,_table,'\'',5);
    mark_cell(5,_table,'`', 5);
    mark_cell(5,_table,'~', 5);
    mark_cell(5,_table,'!', 5);

    mark_cell(0,_table,'\"', 6);
    mark_cell(6,_table,'\"', 6);


    mark_cell(0,_table,'(', 7);
    mark_cell(7,_table,'(', 7);
    mark_cell(0,_table,')', 7);
    mark_cell(7,_table,')', 7);

    //TOKEN_UNKNOWN
    // mark_cell(0,_table,255,6);
}



//Mark this state (row) with a 1 (success)
void mark_success(int _table[][MAX_COLUMNS], int state)
{
    _table[state][0] = 1;
}

    //Mark this state (row) with a 0 (fail)
void mark_fail(int _table[][MAX_COLUMNS], int state)
{
    _table[state][0] = 0;

}

    //true if state is a success state
bool is_success(int _table[][MAX_COLUMNS], int state)
{
    if(_table[state][0] == 1)
    {
        return true; //success
    }
    return false; //fail 
}

    //Mark a range of cells in the array. 
void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state)
{
    for (int i = from; i <= to; i++)
    {
        _table[row][i] = state; 
    }
}

    //Mark columns represented by the string columns[] for this row
void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state)
{

}

    //Mark this row and column
void mark_cell(int row, int table[][MAX_COLUMNS], int column, int state)
{
    table[row][column] = state; 
}


    //This can realistically be used on a small table
void print_table(int _table[][MAX_COLUMNS])
{
    for (int i = 0 ; i < MAX_ROWS; i ++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            cout << _table[i][j] << " ";
        }
        cout << endl;
    }
}

    //show string s and mark this position on the string:
    //hello world   pos: 7
    //       ^
void show_string(char s[], int _pos)
{   // s[_pos];
    for (int i = 0; i <_pos; i++)
    {
        cout << s[i];
    }
}


    //doubles:
    // mark_fail(table, 0);            //Mark states 0 and 2 as fail states
    // mark_success(table, 1);         //Mark states 1 and 3 as success states
    // mark_fail(table, 2);
    // mark_success(table, 3);

    // mark_cells(0, table, DIGITS, 1);    //state [0] --- DIGITS ---> [1]
    // mark_cells(0, table, '.', '.', 2);  //state [0] --- '.' ------> [2] 
    // mark_cells(1, table, DIGITS, 1);    //state [1] --- DIGITS ---> [1]
    // mark_cells(1, table, '.', '.', 2);  //state [1] --- '.' ------> [2] 
    // mark_cells(2, table, DIGITS, 3);    //state [2] --- DIGITS ---> [3]
    // mark_cells(3, table, DIGITS, 3);    //state [3] --- DIGITS ---> [3]