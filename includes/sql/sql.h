#ifndef SQL_H
#define SQL_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "../parser/parser.h"
#include "../table/table.h"

using namespace std;

class SQL{
public:
    SQL();
    SQL(string filename);
    void run();
    // Table batch(string filename);
    vectorlong select_recnos();
    Table command(string command_list);

private:
    Parser parser;
    vectorstr name;
    vectorstr _command;
    vectorlong records;
};

#endif