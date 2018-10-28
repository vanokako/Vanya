#include <iostream>
#include <cstring>
#include <cctype>
#define LEFT 0
#define RIGHT 1

using namespace std;


class BinaryTree {
	private:
    		char element;

   		BinaryTree *left;
   		BinaryTree *parent;
   		BinaryTree *right;

	public:
		void readBT(const string &string, int &i) {
    			if (string[i] == '(') {
        			i++;
        			read_root(string, i);
        			readUnder(string, i, LEFT);
        			readUnder(string, i, RIGHT);
        			if (string[i] == ')')
            				i++;
       				else
					cout << "')' expected";
    			}
			else{
				cout << "'(' expected";
				cout<<endl<<i<<endl;
				cout<<string[i];
    			}

		}	
	
    		void read_root(const string &string, int &i){
   			if (isdigit(string[i]) || isalpha(string[i])) {
        			element = string[i];
        			i++;
    			}
    			else {
        			 cout << "['0'-'9'] or ['A'..'z'] expected";
    			}
		}
    		void readUnder(const string &string, int &i, int side){
			if (string[i] == '#')
        			i++;
    			else {
        			if (side == LEFT) {
            				left = new BinaryTree;
            				left->parent = this;
            				left->readBT(string, i);
        			}
        			else {
            				right = new BinaryTree;
            				right->parent = this;
            				right->readBT(string, i);
        			}
    			}
        
		}

		BinaryTree(){
			left = NULL;
    			parent = NULL;
    			right = NULL;
		}	

		~BinaryTree(){
			if (left)
        			delete left;
    			if (right)
        			delete right;
		}

		int height(){
   			int height_left = 0;
    			if (left != NULL)
        			height_left = left->height();
    			int height_right = 0;
    			if (right != NULL)
        			height_right = right->height();
    			if (height_left > height_right)
				return 1 + height_left;
     			return 1 + height_right;
		}

		int nodes();
		void print_leafs();
		int nodesLvl(int n);
		int internal_lenght();
};
