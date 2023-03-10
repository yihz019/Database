#include "sql.h"

SQL::SQL()
{}

void SQL::run()
{
    SQL sql;
    // Parser p;
    string input = "";
    string instructions {"create/make, insert or select table with or without conditions"};
    do {               
        input.clear();
        cout << "E[x]it program" << endl;
        cout << "INSERT a command \n > " ;
        getline(cin, input);        
        cout << "\n\n---------------------------------------------------------------------------------\n\n" << endl;


        if (!sql.parser.fail())
        {
            // cout << t <<endl;          
            cout << sql.command(input);
            cout << "record numbers: " << sql.select_recnos() << endl;        
            cout << "DONE!\n\n";
        }
        // else 
        // {
        //     cout << "Not complete command\n";

        // }

    } while (input != "x" || input != "X");
}


 SQL::SQL(string filename)
{
    SQL sql;
    ifstream ins;              
    string input;
    Table t;
    vectorstr command;
    ins.open((filename+".txt").c_str());          //open file
    if (ins.fail())           //check for fail
    {
        cout << "File opening failed.\n";
        exit(1);
    }
    int i = 0;
    while(getline(ins,input)) //read line by line into a vector
    { 

        if (input.find("make") == 0 )
        {

            cout<< "[" << i << "] "<<  input << endl;
            cout << "sql::run_command: make" << endl<<endl; 
            command.push_back(input);
            t = sql.command(input);
            cout << "\n\nSQL: DONE. \n\n";
            i++;
            // cout << "\n\n\n command " << command <<endl <<endl;;;
        }
        else if (input.find("insert") == 0 )
        {
            cout<< "[" << i << "] "<<  input << endl;
            cout << "sql::run: inserted." << endl<<endl;
            t = sql.command(input);
            cout << "\n\nSQL: DONE. \n\n";
            i++;
            // cout << "\n\nSQL: DONE.\n\n";
        }
        else if (input.find("select") == 0)
        {
            cout<< "[" << i << "] "<<  input << endl;
            t = sql.command(input);
            // cout << "recs  " << t.select_recnos() <<endl;

            cout << "\n\nSQL: DONE. \n\n";
            i++;
        }
        else 
            cout<<  input << endl;
    }
    ins.close();
    // cout<< t;
}


Table SQL::command(string command_list)
{
    char s[300];
    strcpy(s, command_list.c_str());
    // parser.set_string(s);
    // Parser parser(s);
    parser.set_string(s);
    mmap_ss ptree;
    ptree= parser.parse_tree(); 
    if (parser.fail())
    {
        cout << "NOT complete command\n\n";
    }
    // cout<<"input: ["<<s<<"]"<<endl<<endl;
    // ptree.print_lookup();   //multimap function to print mmap as a table
    // cout << endl<<endl;
    else 
    {    
        _command = ptree["command"];
        name = ptree["table_name"];

        if (_command[0] == "make" || _command[0] == "create")
        {    
            return Table(name[0],ptree["fields"]);
        }
        if (_command[0] == "insert")
        {
            Table tab(name[0]);
            tab.insert_into(ptree["values"]);
            records = tab.select_recnos();               
            // cout << "table here " << t <<endl;
            return tab;
        }
        if (_command[0] == "select")
        {            
            Table t(name[0]);
            if (ptree["fields"][0] != "*" && ptree.contains("condition"))
            {
                cout << t.select(ptree["fields"],ptree["condition"]);
                records = t.select_recnos();
                return t ;
            }
            if (!ptree.contains("condition") && ptree["fields"][0] != "*")
            {
                cout << t.select(ptree["fields"]);
                records = t.select_recnos();
                return t;
            }
            if (!ptree.contains("condition") && ptree["fields"][0] == "*")
            {
                cout << "There is no condition \n";
                t.select_all();       
                records = t.select_recnos();
                return t;              

            }
            if (ptree["fields"][0] == "*" && ptree.contains("condition"))
            {
                cout << t.select(t.get_fields(),ptree["condition"]);
                records = t.select_recnos();
                return t;
            }
            if (ptree["fields"][0] == "*")
            {
                t.select_all();   
                records = t.select_recnos();
                return t;              
            }
        }
    }
    return Table();
}

vectorlong SQL::select_recnos(){
    return records;
}