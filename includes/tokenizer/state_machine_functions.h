#ifndef STATE_MACHINE_FUNCTIONS_H
#define STATE_MACHINE_FUNCTIONS_H
#include <iostream>
#include <cstring>
#include "constants.h"

using namespace std;

int type(char s);


void init_table(int _table[][MAX_COLUMNS]);        //Fill all cells of the array with -1

//Mark this state (row) with a 1 (success)
void mark_success(int _table[][MAX_COLUMNS], int state);

//Mark this state (row) with a 0 (fail)
void mark_fail(int _table[][MAX_COLUMNS], int state);

//true if state is a success state
bool is_success(int _table[][MAX_COLUMNS], int state);

//Mark a range of cells in the array. 
void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state);

//Mark columns represented by the string columns[] for this row
void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state);

//Mark this row and column
void mark_cell(int row, int table[][MAX_COLUMNS], int column, int state);

//This can realistically be used on a small table
void print_table(int _table[][MAX_COLUMNS]);

//show string s and mark this position on the string:
//hello world   pos: 7
//       ^
void show_string(char s[], int _pos);

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


#endif // STATE_MACHINE_FUNCTIONS_H