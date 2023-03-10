#include "shunting_yard.h"

ShuntingYard::ShuntingYard() //Default CTOR
{}

ShuntingYard::ShuntingYard(const vector<string> &infix) //CTOR
{
    vector<string> temp = infix;
    string t;
    for (int i = 0; i < temp.size(); i++)
    {
        t = temp.at(i);

        if(t.compare("(") == 0)
        {
            inf.push(new LeftParen(t));
        }
        else if (t.compare(")") == 0)
        {
            inf.push(new RightParen(t));
        }
        else if(t.compare("=") == 0 ||t.compare("<") == 0 || t.compare(">") == 0
          || t.compare("<=") == 0 || t.compare(">=") == 0)
        {
            inf.push(new Relational(t));
        }
        else if (t.compare("and") == 0 || t.compare("or") == 0)
        {
            inf.push(new Logical(t));
        }
        else 
        {
            inf.push(new TokenStr(t));
        }
    }
    
}

ShuntingYard::ShuntingYard(const Queue<Token*> &q) //CTOR
{
    inf = q;
}

void ShuntingYard::infix(const Queue<Token*> &q) //set_input version 
{
    inf = q;
}

Queue<Token*> ShuntingYard::postfix()
{
    Queue<Token *> q; // output queue
    Stack<Token *> s; // operators stack
    int prec = 0;
    int top = 0;
    
    // cout << "infix " << inf << endl;
    while (!inf.empty())
    {
        Token *t = inf.pop(); // token pointer
        // cout << endl;
        // t->Print();
        // cout << endl << t->TypeOf() << endl;
        // ===============================
        switch (t->TypeOf()) // check type
        {
            case TK_STRING:
                q.push(t);
                break;
            case LOGICAL:
                // cout << "logical\n";
                // cout << "s " << s << endl;
                if (!s.empty()) // if stack not empty
                {    
                    prec = static_cast<Logical *>(t)->get_prec(); // get prec of coming operator       
                    do{ 
                        if (s.top()->TypeOf() == LOGICAL)                    
                            top = static_cast<Logical *>(s.top())->get_prec(); // get prec of operator in the top of stack
                        else if (s.top()->TypeOf() == RELATIONAL)
                            top = static_cast<Relational *>(s.top())->get_prec(); // get prec of operator in the top of stack
                        else
                            top = ZERO_PRE;
                        if (top >= prec) // if sitting on operator >=
                        {
                            q.push(s.pop()); // pop from stack & push into queue
                        }
                        else  //sitting on operator < than me
                        {
                            s.push(t); // just push 
                            break;
                        }
                    } while (!s.empty() && top >= prec) ; //keep checking till stack empty or find operator < than one entering 
                    if (s.empty()){ //if stack empty after popping
                        s.push(t); // push coming operator
                    }
                    break;
                }   
                s.push(t); // if empty stack just push the operator
                break; 
            case RELATIONAL:
                // cout << "s " << s << endl;
                if (!s.empty()) // if stack not empty
                {
                    prec = static_cast<Relational *>(t)->get_prec(); // get prec of coming operator         
                    do{ 
                        if (s.top()->TypeOf() == LOGICAL)                    
                            top = static_cast<Logical *>(s.top())->get_prec(); // get prec of operator in the top of stack
                        else if (s.top()->TypeOf() == RELATIONAL)
                            top = static_cast<Relational *>(s.top())->get_prec(); // get prec of operator in the top of stack
                        else
                            top = ZERO_PRE;
                        if (top >= prec) // if sitting on operator >=
                        {
                            q.push(s.pop()); // pop from stack & push into queue
                        }
                        else  //sitting on operator < than me
                        {
                            s.push(t); // just push 
                            break;
                        }
                    } while (!s.empty() && top >= prec) ; //keep checking till stack empty or find operator < than one entering 
                    if (s.empty()){ //if stack empty after popping
                        s.push(t); // push coming operator
                    }
                    break;    
                }    
                s.push(t); // if empty stack just push the operator            
                break;
            case L_PAREN:
                s.push(t);
                break;
            case R_PAREN:
                {           
                    Token *oper = s.pop();
                    while (oper->TypeOf() != L_PAREN && !s.empty())
                    {
                        q.push(oper); // pop from stack & push into queue
                        oper = s.pop();
                        // oper->Print() ;
                    }
                }
                break;
            case RESULT_SET:
                break;
            case TOKEN:
                break;
        }
        
    }
    // cout << "s " << s <<endl << endl;; 
    while (!s.empty()){
        q.push(s.pop()); //@ end pop last operator into queue
    }
    return q;
}

Queue<Token*> ShuntingYard::postfix(Queue<Token*> infix)
{
    inf = infix;
    return postfix();
}



void ShuntingYard::print(ostream &outs) const
{
    outs << inf << endl;
}