#include "parser.h"

Parser::Parser()
{
    _fail = true;
}
Parser::Parser(char* s)
{
    STokenizer stk(s);
    Tokens t;
    stk>>t;
    while(stk.more()){
        //process token here...
        // cout<<setw(10)<<t.type_string()<<setw(10)<<t<<endl;
        if (t.type_string() != "SPACES" && t.type_string() != "EMPTY"  && t.type_string() != "UNKNOWN" )
        { 
            input.push(t.token_str());
        }
        t = Tokens();
        stk>>t;
    }
    // cout << input << endl;
    make_table();
    build_keyword_list();
}

int Parser::get_column(const string token)
{
    if (keywords.contains(token))
    {
        if (keywords[token] == FIELDS || keywords[token] == VALUES)
        {
            save = keywords[token];
        }
        else if (keywords[token] == WHERE)
        {
            save = SYM;
        }
        else if (keywords[token] == SELECT)
        {
            save = FIELDS;
        }
        return keywords[token];
    }
    return save;
}

void Parser::set_string(char* str)
{
    ptree.clear();
    keywords.clear();
    while (!input.empty())
    {
        input.pop();
    }
    STokenizer stk(str);
    Tokens t;
    stk>>t;
    while(stk.more()){
        //process token here...
        // cout<<setw(10)<<t.type_string()<<setw(10)<<t<<endl;
        if (t.type_string() != "SPACES" && t.type_string() != "EMPTY"  && t.type_string() != "UNKNOWN" )
        { 
            input.push(t.token_str());
        }
        t = Tokens();
        stk>>t;
    }
    // cout << input << endl;
    make_table();
    build_keyword_list();
}

MMap<string,string> Parser::parse_tree()
{   
    _fail = get_parse_tree(input);
    // cout << "FAIL: " << boolalpha << fail() <<endl;
    // cout << "================================= PTREE ===========================\n";
    // parse_tree() ;//<<endl;

    return ptree;
}

bool Parser::get_parse_tree(const Queue<string> &input)
{
    Queue<string> q = input;
    int state = 0;
    int cur_state = 0;
    int end_state = -1;
    string token = "";
    bool one = true;
    int col = 0;
    int i  = 0;
    while (!q.empty())
    {         
        token = q.pop();
        col =  get_column(token);
        // cout << "col " << col <<endl ; 
        cur_state = _table[state][col];  
        // cout << "token : " << token << "  state : " << cur_state <<endl <<endl;;
        switch(cur_state)
        {
            case -1://sym
                // cout << "case -1\n";
                cur_state = end_state;
            case SYM:
                ptree["condition"] += token;
                end_state = SYM;
                break;
            case MAKE:
            case CREATE:
            case DROP:
            case INSERT: 
                ptree["command"] += token;
                break;
            case SELECT:
                ptree["command"] += token;
                end_state = FIELDS;
                break;
            case FIELDS:
                if (!q.empty() && token == "fields" || (!q.empty() && token == "," ))
                {
                    if (end_state == FIELDS)
                    {
                        one = false;
                    }
                    token = q.pop();  
                }
                ptree["fields"] += token;
                end_state = FIELDS;       
                break;                 
            case VALUES:
               if (!q.empty() && token == "values" || (!q.empty() && token == ","))
                {
                    token = q.pop();
                    if (!q.empty() && token == ",")
                    {         
                        token = q.pop();        
                        ptree["values"] += token;
                    }
                    else {
                        ptree["values"] += token;
                    }                        
                }
                else 
                {
                    ptree["values"] += token;
                }
                end_state = VALUES;      
                break;
            case STAR:
                ptree["fields"] += "*";
                break;
            case WHERE:
                ptree["where"] += "yes";
                end_state = SYM;
                break;
            case FROM:
                token = q.pop();
                ptree["table_name"] += token; //save table name
                break;
            case TABLE: //unused symbol TABLE OR INTO
                token = q.pop();
                ptree["table_name"] += token; //save table name
                break;
            case INTO: //unused symbol TABLE OR INTO
                ptree["command"] += token; //save table name
                if (!q.empty())
                {
                    token = q.pop();
                    ptree["table_name"] += token; //save table name
                }
                cout << "ends " <<end_state <<endl;
                break;
        }
    } 
    if (end_state == FIELDS || end_state == VALUES || end_state == STAR ||
        end_state == SYM)
    {
        return false;        
    }
    return true;
}

void Parser::build_keyword_list() //init keyword map 
{    
    keywords["create"] = CREATE;
    keywords["make"] = MAKE;
    keywords["drop"] = DROP;
    keywords["table"] = TABLE;
    keywords["insert"] = INSERT;
    keywords["select"] = SELECT;
    keywords["fields"] = FIELDS;
    keywords["values"] = VALUES;
    keywords["*"] = STAR;
    keywords["from"] = FROM;
    keywords["where"] = WHERE;
    keywords["into"] = INTO;
}

void Parser::make_table() //or init table
{
    for (int i = 0 ; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            _table[i][j] = -1;
        }
    }

    //STATE 1 (create)
    mark_cell(0,_table,CREATE,CREATE);
    mark_cell(CREATE,_table,CREATE,CREATE);

    //STATE 2 (make)
    mark_cell(0,_table,MAKE,MAKE);
    mark_cell(MAKE,_table,MAKE,MAKE);

    //STATE 3 (drop)
    mark_cell(0,_table,DROP,DROP);
    mark_cell(DROP,_table,DROP,DROP);

    //STATE 4 (insert/insert_into)
    mark_cell(0,_table,INSERT,INSERT);
    mark_cell(INSERT,_table,INSERT,INSERT);

    //STATE 5  select
    mark_cell(0,_table,SELECT,SELECT);
    mark_cell(SELECT,_table,SELECT,SELECT);

    //STATE 6 (star or all fields )
    mark_cell(0,_table,STAR,STAR);
    mark_cell(STAR,_table,STAR,STAR);

    //STATE 7 (specific fields)
    mark_cell(0,_table,FIELDS,FIELDS);
    mark_cell(FIELDS,_table,FIELDS,FIELDS);

    mark_cell(0,_table,VALUES,VALUES);
    mark_cell(VALUES,_table,VALUES,VALUES);

   //STATE 8 (from)
    mark_cell(0,_table,FROM,FROM);
    mark_cell(FROM,_table,FROM,FROM);

    //STATE 9: where/conditions 
    mark_cell(0,_table,WHERE,WHERE);
    mark_cell(WHERE,_table,WHERE,WHERE);

    //STATE 10: table name 
    mark_cell(0,_table,TABLE,TABLE);
    mark_cell(TABLE,_table,TABLE,TABLE);

    // STATE oper 
    mark_cell(0,_table,',',',');
    mark_cell(',',_table,',',',');

    mark_cell(0,_table,INTO,INTO);
    mark_cell(INTO,_table,INTO,INTO);
}


ostream& operator << (ostream& outs, const Parser p)
{
    p.ptree.print_lookup();
    return outs;
}



