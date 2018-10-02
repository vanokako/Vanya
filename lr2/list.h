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

void read_lisp ( lisp& y, ifstream &infile); 

void read_s_expr (char prev, lisp& y, ifstream &infile);

void read_seq ( lisp& y, ifstream &infile);

void write_lisp (const lisp x); 

void write_seq (const lisp x);


