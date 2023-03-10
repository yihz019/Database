#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <iostream>
#include "../tokenizer/state_machine_functions.h"

using namespace std;


enum keys {
    ZERO,
    CREATE ,
    MAKE,
    DROP,
    TABLE, // SYM
    INSERT,
    SELECT,
    FIELDS, //SYM
    VALUES, //SYM
    STAR,    //SYM
    FROM,
    WHERE,
    INTO, 
    SYM, //SYM for conditions
    
};  


#endif // CONSTANTS_H
