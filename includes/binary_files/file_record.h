#ifndef FILE_RECORD_H
#define FILE_RECORD_H

#include <iostream>
#include <iomanip>
#include <string.h>
#include <vector>
#include <string>
#include "utilities.h"

using namespace std;

class FileRecord{
public:
    //when you construct a FileRecord, it's either empty or it
    //  contains a word
    FileRecord(){
        for (int i = 0; i < MAX+1; i++)
        {
            for (int j = 0; j < MAX+1; j++)
            {
               _record[i][j] = '\0';
            }
        }
        recno = -1;
        //['\0'|  | G | a | r | b | a   |  g  |  e |    ]
    }

    FileRecord(vector<string> str)
    {   //strncpy(_record, str, MAX);
        for (int i = 0; i < str.size(); i++)
        {
            strncpy(&_record[i][0],str[i].c_str(),str[i].length());
            _record[i][str[i].length()]='\0';
        }  
    }


    FileRecord(string s)
    {  // strncpy(_record, s.c_str(), MAX);
        // int j = 0;
        // for (int i = 0; i < s.length(); i++)
        // {
        //     while (j != ',')
        //     {
        //         _record[i][j] = s[j];
        //         j++;
        //     }
        //     _record[i][j]='\0';
        // }
        strncpy(&_record[0][0],s.c_str(),MAX+1);
        // _record[i][str[i].length()]='\0';
    }

    long write(fstream& outs);              //returns the record number
    long read(fstream& ins, long recno);    //returns the number of bytes
                                            //      read = MAX, or zero if
                                            //      read passed the end of file


    friend ostream& operator<<(ostream& outs, const FileRecord& r);

    friend vector<string> get_values(const FileRecord& r, vector<int> fields_to_print) 
    {
        vector<string> values;
        int j = 0;
        // for (int i = 0; i < r.MAX+1 && r._record[i][0] !='\0'; i++)
        {
            for (int i = 0; i < fields_to_print.size(); i++)
            // {if (fields_to_print[j] == i)
            {
                values.push_back(r._record[fields_to_print[i]]);
                // j++;
            }
        }
        // for (int i = 0; i < values.size() ; i++)
        // {
        //    cout <<  values[i] << endl;
        // }
        return values;
    }    
    static const int MAX = 300;
    char _record[MAX+1][MAX+1]; //NULL char    
    
private:
    int recno;
    vector<string> field_vals;
};

#endif