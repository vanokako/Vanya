#include <iostrim>
#include <cstring>
#include <cctype>
#define 0 LEFT
#define 1 RIGHT

using namespace std;


class BinaryTree {
	private:
    		char element;

   		BinaryTree *left;
   		BinaryTree *parent;
   		BinaryTree *right;

	public:
		void readBT(const string &string, int &i);
    		void read_root(const string &string, int &i);
    		void readUnder(const string &string, int &i, int side);
		BinaryTree();
		~BinaryTree();
		int height();
		int nodes();
		void print_leafs();
		int nodesLvl(int n);
		int internal_lenght();
};
