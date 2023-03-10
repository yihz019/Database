#include "table.h"

int Table::serial;
// vector<long> Table::record_nums; 

Table::Table()
{
    _last_record = 0;
    _table_name = "";
}

Table::Table(const string &table_name, const vector<string> &fields) //takes table name and vector of info
{
    serial++;
    record_nums.clear(); 
    _last_record = 0;

    _table_name = table_name; //save table name 
    string name = table_name+ ".txt";
    // 1. writing into txt and binary files 
    fstream f_txt; // txt file
    f_txt.open((name).c_str(), std::fstream::out);
    if (f_txt.fail()){
        cout<<"file open failed: "<<_table_name<<endl;
    }
    // 2. setting vector of fields 
    for (int i = 0; i < fields.size(); i++)
    {
        map[fields.at(i)] = i;
        f_txt << fields.at(i) << endl; 
        field_names.push_back(fields.at(i));
    }
    // cout << "map " << map <<endl;
    f_txt.close();
    fstream f_bin; //for binary file
    name = table_name + ".bin";
    open_fileW(f_bin, name.c_str()); //create binary file
    // FileRecord r = FileRecord(fields); //filling the envelop
    // int recno = r.write(f_bin);
    // cout<<"wrote into record: "<<recno<<endl;
    f_bin.close();

    for (int i = 0; i < fields.size(); i++)
    {
        if (map.contains(fields[i]))
        {
            fields_to_print.push_back(map[fields[i]]);
        }
        // cout << "field " << fields_to_print.at(i);
    }


    // 3. Initialize index Struct
    _indices.init_index(fields.size());
}

Table::Table (const string &table_name)//takes table name of existing file 
{
    ifstream ins;               //declare ifstream
    string input;
    _last_record = -1;
    string name = table_name +".txt";
    _table_name = table_name;
    ins.open(name);          //open file
    if (ins.fail())           //check for fail
    {
        cout << "File opening failed.\n";
        exit(1);
    }
    int i = 0;
    while (ins >> input)   //read line by line into a vector
    { //fill up field names 
        map[input] = i;
        field_names.push_back(input);
        i++;
    }
    for (int i = 0; i < field_names.size(); i++)
    {
        fields_to_print.push_back(map[field_names[i]]);
    }

    _indices.init_index(field_names.size());
    ins.close();   
    reindex();
}

void Table::insert_into(vector<string> row)// takes a vector of info and write into file 
{
    fstream f;
    string name = table_name()+ ".bin";
    open_fileRW(f, (name).c_str()); //open existing binary file
    FileRecord r = FileRecord(row); //filling the envelop
    _last_record = r.write(f);
    record_nums.push_back(_last_record);
        // cout << "records << . " << record_nums <<endl;
// cout<<"wrote into record: "<<_last_record<<endl;
    //update index
    _indices.update(row, _last_record);
    f.close();  
}

void Table::reindex() 
{
    record_nums.clear();
    fstream f;
    FileRecord r2;
    vector<string> row;
    string name = table_name() + ".bin";
    
    open_fileRW(f, name.c_str());    //open existing file for reading.

    int i = 0;
    long bytes = r2.read(f, i); //empty envelop to be filled by the FileRecord object
    while (bytes>0)
    {
    //   cout<<"record "<<i<<": "<<r2<<endl;
        row = get_values(r2,fields_to_print);
        _indices.update(row, i);
        record_nums.push_back(i);
        i++,  _last_record++;
        bytes = r2.read(f, i);
    }
    f.close();  
}

Table Table::select(vectorstr fields,const string field, const string op, const string value) 
{
    // cout << "index " << map[field] <<endl;
    Queue<Token *> pos;
    pos.push(new TokenStr(field));
    pos.push(new TokenStr(value));    
    pos.push(new Relational(op));

    RPN rpn(pos);
    // cout << "posfix:  " << pos <<endl;
    // cout << "vector " << rpn(_indices, map) << endl;
    record_nums = rpn(_indices, map);//_indices.indices[index][value];
    sort(record_nums.begin(),record_nums.end());
    return vector_to_table(record_nums, fields);
}

Table Table::select(vectorstr fields, const Queue<Token*> postfix) 
{
    field_names = fields;
    RPN rpn(postfix);
    // cout << "posfix:  " << postfix <<endl;
    // cout << "vector " << rpn(_indices, map[field]) << endl;

    record_nums = rpn(_indices, map);//_indices.indices[index][value];
    sort(record_nums.begin(),record_nums.end());
    return vector_to_table(record_nums, fields);
}

Table Table::select(vectorstr fields,const vectorstr condition) 
{
    field_names = fields;
    ShuntingYard sy(condition); //infix

    Queue<Token*> postfix = sy.postfix();
    RPN rpn(postfix);
    cout << "posfix:  " << postfix <<endl;
    // cout << "vector " << rpn(_indices, map) << endl;

    record_nums = rpn(_indices, map);//_indices.indices[index][value];
    // sort(record_nums.begin(),record_nums.end());
    return vector_to_table(record_nums, fields);
}

Table Table::select(vectorstr fields) 
{
    return vector_to_table(record_nums,fields);
}


Table Table::vector_to_table(const vector<long>& records, vector<string> fields) 
{
    fstream f;
    FileRecord r2;
    string name = table_name()+serial_number();
    Table temp(name,fields); //add serial number to name 
    //open existing file for reading.
    name = table_name()+".bin";
    open_fileRW(f, name.c_str());

    // temp.set_records(records);
    field_names = fields;
    fields_to_print.clear();
    for (int i = 0; i < fields.size(); i++)
    {
        if (map.contains(fields[i]))
        {
            fields_to_print.push_back(map[fields[i]]);
        }
        // cout << "field " << fields_to_print.at(i);
    }


    for (int j = 0; j < records.size(); j++)
    {
        int i = records[j];        
        long bytes = r2.read(f, i); //empty envelop to be filled by the FileRecord object
        // cout<<"record "<<i<<": "<<r2<<endl;
        vector<string> values = get_values(r2,fields_to_print);        
        temp.insert_into(values);    
    }
    f.close();  
    // cout << "=====================================\n\n";
    return temp;
}

void Table::select_all() const  //print everything from the file 
{
    fstream f;
    FileRecord r2;
    const string name = table_name()+ ".bin";
    open_fileRW(f, name.c_str());
    cout << setw(25) << "records" ;
    int j = 0;
    for (int i  = 0 ; i < field_names.size(); i++)
    {
        if (fields_to_print.at(j) == i)
        {
            cout << setw(25) << field_names.at(i) ;
            j++;
        }
    }
    cout << endl<<endl;;
    int i = 0;
    long bytes = r2.read(f, i); //empty envelop to be filled by the FileRecord object
    while (bytes>0){
        cout<< setw(25)<<i << r2 <<endl;
        i++; 
        bytes = r2.read(f, i);
    }
    f.close();  
}
