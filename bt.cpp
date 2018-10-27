#include "BT.hpp"

void BinaryTree::readBT(const string &string, int &i) {
    if (string[i] == '(') {
        i++;
        read_root(string, i);
        readUnder(string, i, LEFT);
        readUnder(string, i, RIGHT);
        if (string[i] == ')')
            i++;
        else {
            error(2);
        }
    }
    else {
        error(1);
    }
}

void BinaryTree::read_root(const string &string, int &i) {
    if (isdigit(string[i]) || isalfa(string[i])) {
        element = string[i];
        i++;
    }
    else {
        error(3);
    }
}

void BinaryTree::readUnder(const string &string, int &i, int side) {
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

BinaryTree::BinaryTree() {
    left = NULL;
    parent = NULL;
    right = NULL;
}

BinaryTree::~BinaryTree() {
    if (left)
        delete left;
    if (right)
        delete right;
}



void error(short code) {
    cout << "ERROR CODE " << error_code;
    switch (error_code) {
    case 1:
        cout << "'(' expected";
        break;
    case 2:
        cout << "')' expected";
        break;
    case 3:
        cout << "['0'-'9'] or ['A'..'z'] expected";
        break;
    case 4:
        cout << "excess symbols";
        break;
    }
    cout << std::endl;
}

int BinaryTree::nodes(){
	int res = 1;
	if(left != NULL)
	    res += left->nodes();
	if(right != NULL)
	    res += right->nodes();
	return res;
    }

 void BinaryTree::print_leafs(){
	if(left == NULL && right == NULL)
	    cout << element << " ";
	if(left != NULL)
	    left->print_leafs();
	if(right != NULL)
	    right->print_leafs();
    }

int BinaryTree::nodesLvl(int n){
	if (n<=0){
		cout<<"Expected positive number and not zero"<<endl;
		exit(1);
	}
	else if (n == 1)
		return 1;
	else{
		int result = 0;
		if(left)
			result += left->nodesLvl(n-1);
		if(right)
			result += right->nodesLvl(n-1);
		return result;
	}
}
		

int BinaryTree::height() {
    int height_left = 0;
    if (left)
        height_left = left->height();
    int height_right = 0;
    if (right)
        height_right = right->height();
    if (height->left > height->right)
	return 1 + height->left;
     return 1 + height->right;
}

int BinaryTree::internal_lenght(){
	int lenght = 0;
	if(left)
	    lenght += left->internal_lenght() + left->nodes();
	if(right)
	    lenght += right->internal_lenght() + right->nodes();
	return lenght;
} 






