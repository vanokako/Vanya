struct s_expr;
struct two_ptr{
    s_expr *head;
    s_expr *tail;
};

struct s_expr {
    bool tag;
    union{
        char atom;
        two_ptr pair;
    }node;
};

typedef s_expr *lisp;
using namespace std;
#include <fstream>

lisp reverse(const lisp s);

lisp rev(const lisp s,const lisp z);

lisp head (const lisp s);

lisp tail (const lisp s);

lisp cons (const lisp h, const lisp t);

lisp make_atom (const char x);

bool isAtom (const lisp s);

bool isNull (const lisp s);

void destroy (lisp s);

char getAtom (const lisp s);

void read_lisp ( lisp& y, istream &astr);

void read_s_expr (char prev, lisp& y, istream &astr);

void read_seq ( lisp& y, istream &astr);

void write_lisp (const lisp x);

void write_seq (const lisp x);


#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <cstring>

int start( lisp& s1, lisp& s2, istream &astr){
    char ch;
    read_lisp (s1, astr);
    cout << "введен list1: " << endl;
    write_lisp (s1);
    cout << endl;
    if(astr >> ch){
        cout<<"! Лишние символы !"<<endl;
        return 0;
    }
    cout << "Список перевернут: " << endl;
    s2 = rev (s1, NULL);
    write_lisp (s2);
    cout << endl;
    delete(s2);
    delete (s1);
    return 0;


}


int main ( ){
    char forSwitch;
    stringbuf exp;
    string list;
    char ch;
    lisp s1, s2;
    while (1){
        cin>>forSwitch;
        cin.ignore();
        switch(forSwitch){
            case '1':{
                cout << "введите list1:" << endl;
                getline(cin, list);
                istream str(&exp);
                exp.str(list);
                start(s1,s2,str);
                break;
            }
             case '2':{
                ifstream infile("a.txt");
                 getline(infile, list);
                istream str(&exp);
                exp.str(list);
                start(s1,s2,str);
                break;
            }
            case '0':{
                cout<<"Bye!"<<endl;
                return 0;
            }
            default:{
                cout<<"НЕВЕРНЫЙ ВВОД!"<<endl;
                break;
            }
       }

    }


}



lisp head (const lisp s){
        if (s != NULL)
            if (!isAtom(s))
                return s->node.pair.head;
            else {
                cerr << "Error: Head(atom) \n";
                exit(1);
            }
        else {
            cerr << "Error: Head(nil) \n";
            exit(1);
        }
}

bool isAtom (const lisp s){
        if(s == NULL)
            return false;
        else
            return (s -> tag);
}


bool isNull (const lisp s){
        return s==NULL;
    }


lisp tail (const lisp s){
    if (s != NULL){
            if (!isAtom(s))
                return s->node.pair.tail;
            else {
                cerr << "Error: Tail(atom) \n";
                exit(1);
            }
    }
        else {
            cerr << "Error: Tail(nil) \n";
            exit(1);
        }
}

lisp cons (const lisp h, const lisp t){
        lisp p;
        if (isAtom(t)) {
            cerr << "Error: Cons(*, atom)\n";
            exit(1);
        }
        else {
            p = new s_expr;
            if ( p == NULL) {
                cerr << "Memory not enough\n";
                exit(1);
            }
            else {
                p->tag = false;
                p->node.pair.head = h;
                p->node.pair.tail = t;
                return p;
            }
        }
}


lisp make_atom (const char x){
        lisp s;
        s = new s_expr;
        s -> tag = true;
        s->node.atom = x;
        return s;
    }


void destroy (lisp s){
        if ( s != NULL) {
            if (!isAtom(s)){
                destroy ( head (s));
                destroy ( tail(s));
            }
        delete s;

        }
    }




void read_lisp ( lisp& y, istream &astr){
        char x;
        do{
            astr >> x;
        }while (x==' ');
        read_s_expr ( x, y, astr);
}


void read_s_expr (char prev, lisp& y, istream &astr){
        if ( prev == ')' ) {
            cerr << " ! Закрывающая скобка перед открывающей ! " << endl;
            exit(1);
        }
        else if ( prev != '(' )
            y = make_atom (prev);
        else
            read_seq (y, astr);
}



void read_seq ( lisp& y, istream &astr){
        char x;
        lisp p1, p2;
        if (!(astr >> x)) {
            cerr << " ! Не хватает символов ! " << endl;
            exit(1);
        }
        else {
            while ( x==' ' ){
                astr >> x;
            }

            if ( x == ')' )
                y = NULL;
            else {
                read_s_expr ( x, p1, astr);
                read_seq ( p2, astr);
                y = cons (p1, p2);
            }
        }
}


void write_lisp (const lisp x){
        if (isNull(x))
            cout << " ()";
        else if (isAtom(x))
            cout << ' ' << x->node.atom;
        else {
            cout << " (" ;
            write_seq(x);
            cout << " )";
        }
}

void write_seq (const lisp x){
        if (!isNull(x)) {
            write_lisp(head (x));
            write_seq(tail (x));
        }
}

lisp rev(const lisp s,const lisp z){
    if(isNull(s))
        return(z);
   else if(isAtom(head(s))){
       return(rev(tail(s), cons(head(s),z)));

    }
    else
        return(rev(tail(s), cons(rev(head(s), NULL),z)));

}
