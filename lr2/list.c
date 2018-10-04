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
