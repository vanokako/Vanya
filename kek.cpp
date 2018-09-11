#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
using namespace std ;
bool bracket (ifstream &infile, char ch);


int main ( ){
	bool exit = true, check;
	char ch, test [100];
	int forSwitch;
	while (exit){
		cin >> forSwitch;
		switch (forSwitch){
			case 1:{
				ifstream infile ("test.txt");
				if (infile >> ch){ 
					cout << ch;
					if ((ch == 'A') || (ch == '('))
						check = bracket (infile, ch);
				}
				cout << endl;
				if (check)
					cout<<"YEAAAAAAA"<<endl;
				break;
				}
			case 2:{
				ifstream infile ("test.txt");
				
				break;
				}
			case 0:{
				exit = false;
				}
		}
	}
	
return 0;
}

bool bracket (ifstream &infile, char ch){ 
	bool forCheck;
	if (ch == 'A') 
		return true;
	else if ( ch == '(' ){
		if (infile >> ch){
			cout << ch;
			if (ch == 'B'){
				if (infile >> ch){
					cout << ch << endl;
					forCheck = bracket (infile,ch);
				}
				else 
					return false; // pustie skobki
				if (forCheck){ 
					if (infile >> ch){
						cout << ch<< endl;
						forCheck = bracket (infile,ch);
					}
				}
				else 
					return false; //neppavilnie skobki
				
				if (forCheck) {
					if (infile >> ch){ 
						cout << ch;
						return (ch == ')');
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
				
			
	
