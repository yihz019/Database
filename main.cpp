#include <iostream>
#include <iomanip>
#include "includes/sql/sql.h"


using namespace std;

int main(int argv, char** argc) {
    cout << "\n\n"
         << endl;

SQL sql;
    // string filename = "_!sample";
    // string filename = "_!select-1";

    // sql.batch(filename);
    // SQL sql(filename);

    sql.run();


    cout << "\n\n\n=====================" << endl;
    return 0;
}
