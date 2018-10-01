#include <cstdio>
#include <cstdlib>
#include "list.h"
#include <iostream>

using namespace std;



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


char getAtom (const lisp s){
        if (!isAtom(s)) {
            cerr << "Error: getAtom(s) for !isAtom(s) \n";
            exit(1);
        }
        else
            return (s->node.atom);
    }


void read_lisp ( lisp& y){
        char x;
        do{
            cin >> x;
        }while (x==' ');
        read_s_expr ( x, y);
    }
  
void read_s_expr (char prev, lisp& y){ 
        if ( prev == ')' ) {
            cerr << " ! List.Error 1 " << endl;
            exit(1);
        }
        else if ( prev != '(' ){
            y = make_atom (prev);
		}
        else
            read_seq (y);
} 
  

void read_seq ( lisp& y){
        char x;
        lisp p1, p2;
        if (!(cin >> x)) {
            cerr << " ! List.Error 2 " << endl;
            exit(1);
        }
        else {
            while ( x==' ' )
                cin >> x;

            if ( x == ')' )
                y = NULL;
            else {
                read_s_expr ( x, p1);
                read_seq ( p2);
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
	else if(isAtom(head(s))) 
		return(rev(tail(s), cons(head(s),z)));
	else 
		return(rev(tail(s), cons(rev(head(s), NULL),z)));
}

    
 
 
