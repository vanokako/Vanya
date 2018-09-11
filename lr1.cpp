#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
using namespace std ;
bool bracket (ifstream &infile, char s);

//void Error (short k);

int main ( ){
	bool b;
	char s;
	ifstream infile ("test.txt");
	if (infile >> s){ 
		cout << s;
		if ((s == 'A') || (s == '('))
			b = bracket (infile, s);
	}
	cout << endl;
	if (b)
		cout<<"YEAAAAAAA"<<endl;
	
return 0;
}

bool bracket (ifstream &infile, char s){ 
	bool k;
	if (s == 'A') 
		return true;
	else if ( s == '(' ){
		if (infile >> s){
			cout << s;
			if (s == 'B'){
				if (infile >> s){
					cout << s;
					k = bracket (infile,s);
				}
				else 
					return false; // pustie skobki
				if (k){ 
					if (infile >> s){
						cout << s;
						k = bracket (infile,s);
					}
				}
				else 
					return false; //neppavilnie skobki
				
				if (k) {
					if (infile >> s){ 
						cout << s;
						return (s == ')');
					}
				}
				else
					return false; //net zakrivayuschey skobki
			}
			else
				return false;// skobki bez B
		}
		else return false; //pustie skobki
	}
	else return false; //ne a i ne skobka
}
	
