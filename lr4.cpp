#include "BT.hpp"

int main(){
	BinaryTree b;
	int i =0;
	string string;
	cin>>string;
	b.readBT(string, i);
	int h = b.height();
	cout<<h<<endl;
}
