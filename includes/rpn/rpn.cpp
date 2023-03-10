#include "rpn.h"

RPN::RPN()
{
    _pos = 0;
}

RPN::RPN(const Queue<Token*>& q) //CTOR
{
    post = q;
}

vector<long> RPN::operator()(const Index& indices, Map<string,int> pos)
{
    mmap = indices;
    map = pos;
    return eval();
}


vector<long> RPN::eval()//return a vector of record numbers 
{
    Stack<string> out; // output stack
    Queue<Token *> temp(post); // copy postfix queue into local queue
    vector<long> records;
    vector<long> r;
    Stack<vector<long>> recns;
    int prec; // precedence
    string value = "";
        // cout << "MMAP " << mmap.indices[_pos] << endl << endl; 

    while (!temp.empty())
    {      
        // Looping through the queue and getting the type
        //==============================
        Token *t = temp.pop(); // token pointe
        // cout << *t <<endl;
        // cout << "t ";t->Print();
        // cout << t->TypeOf() << endl;
        //===============================
        switch (t->TypeOf()) // check type
        {
            case TK_STRING:
                value = static_cast<TokenStr*>(t)->get_tkstr();
                out.push(value); // push into stack
                break;
            case RELATIONAL:
                value = out.pop(); // pop out last symbol
                if(!out.empty())
                {
                    get_index(out.pop()); //get which mmap to look for
                }
                prec = static_cast<Relational *>(t)->get_prec(); // get precendence of operator
                switch (prec)  // check for precedence of operators and do the math
                {
                    case GREAT: // > upper bound
                    {
                        vector<long> r;
                        MMap<string, long>::Iterator find, it;
                        it = mmap.indices[_pos].begin();
                        for (; it != mmap.indices[_pos].end(); it++)
                        {                    
                            if (*it > value)
                            {
                                r += mmap.indices[_pos].at((*it).key);
                            }  
                        }                           
                        recns.push(r);
                    }
                    break;
                    case GREATEQ: // >= Lower bound
                    {
                        vector<long> r;
                        MMap<string, long>::Iterator it;
                        it = mmap.indices[_pos].begin();
                        for (; it != mmap.indices[_pos].end(); it++)
                        {
                            if (value <= *it)
                            {
                                r += mmap.indices[_pos].at((*it).key);
                            } 
                        }                          
                        recns.push(r);
                    }
                    break;
                    case EQUAL: // find
                    { 
                        vector<long> r;
                        MMap<string, long>::Iterator it;
                        it = mmap.indices[_pos].begin();
                        for (; it != mmap.indices[_pos].end(); it++)
                        {
                            if (value == *it)
                            {
                                r += mmap.indices[_pos].at((*it).key);
                            } 
                        }                     
                        recns.push(r);
                    }
                    break;
                    case LESSEQ:
                    {          
                        vector<long> r;
                        MMap<string, long>::Iterator it;
                        it = mmap.indices[_pos].begin();
                        for (; it != mmap.indices[_pos].end(); it++)
                        {
                            if (*it <= value) 
                            {
                                r += mmap.indices[_pos].at((*it).key);
                            } 
                        }                         
                        recns.push(r);
                    }
                    break;
                    case LESS:
                    {
                        vector<long> r ;
                        MMap<string, long>::Iterator it;
                        it = mmap.indices[_pos].begin();
                        for (; it != mmap.indices[_pos].end(); it++)
                        {                                
                            if (*it < value)
                            {
                                r += mmap.indices[_pos].at((*it).key);
                            } 
                        }                           
                        recns.push(r);
                        // cout << "LESS " << r <<endl;
                    }
                    break;
                }
                break;
            case LOGICAL:
                prec = static_cast<Logical *>(t)->get_prec(); // get precendence of operator
                switch (prec)  // check for precedence of operators and do the math
                {
                    case AND:
                        r = recns.pop();
                        r = intersection(r,recns.pop());
                        recns.push(r);
                        break;
                    case OR:
                        r = recns.pop();
                        r = vector_union(r,recns.pop());
                        recns.push(r);
                        break;
                }
                break;
            case L_PAREN:
            case R_PAREN:
                break;
            case RESULT_SET:
                break;
            case TOKEN:
                break;
        }
    }
    return recns.pop();
}

void RPN::get_index(const string field) 
{
    _pos = map[field];
}


void RPN::set_input(Queue<Token*> & token)
{
    post = token;
}

void RPN::print(ostream &outs) const
{
    outs << post <<endl;
}
