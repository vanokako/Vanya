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
        void printtree(BinaryTree* treenode, int l){
            if(treenode==NULL){
                for(int i = 0;i<l;++i)
                    cout<<"\t";
                cout<<'#'<<endl;
                return;
            }
            printtree(treenode->right, l+1);
            for(int i = 0; i < l; i++)
                cout << "\t";
            cout << treenode->element<< endl;
            printtree(treenode->left,l+1);
         }


        void readBT(const string &string, int &i) {
                if (string[i] == '(') {
                    i++;
                    read_root(string, i);
                    readUnder(string, i, LEFT);
                    readUnder(string, i, RIGHT);
                    if (string[i] == ')')
                            i++;
                    else{
                    cout << "')' expected at the index:"<<i<<endl;
                    exit(1);


                }

                }
            else{
                cout << "'(' expected at the index:"<<i<<endl;
                exit(1);
                }

        }

            void read_root(const string &string, int &i){
            if (isdigit(string[i]) || isalpha(string[i])) {
                    element = string[i];
                    i++;
                }
                else {
                     cout<<"Expected number or letter at the index"<<i<<endl;
                     exit(1);
                }
        }
            void readUnder(const string &string, int &i, int side){
            if (string[i] == '#')
                    i++;
                else if(string[i] != ')'){
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


        int nodes(){
            if (left == NULL && right == NULL)
                return 1;
            int left_nodes = 0 , right_nodes = 0;
            if (left != NULL)
                left_nodes = left->nodes();
            if (right != NULL)
                right_nodes = right->nodes();
            return left_nodes + right_nodes + 1;
        }


        void leafs(){
            if(left == NULL && right == NULL)
                    cout << element << " ";
            if(left != NULL)
                    left->leafs();
            if(right != NULL)
                    right->leafs();
            }


        int nodesLvl(int n){
            int result = 0;
            if (n<=0){
            cout<<"Expected positive number and not zero"<<endl;
            }
            else if (n == 1)
                return 1;
            else{
                if(left)
                    result += left->nodesLvl(n-1);
                if(right)
                    result += right->nodesLvl(n-1);
            }
            return result;
        }


        int internal_lenght(){
             int lenght = 0;
            if(left != nullptr)
                lenght += left->internal_lenght() + left->nodes();
            if(right != nullptr)
                lenght += right->internal_lenght() + right->nodes();
            return lenght;

        }
};

#include <fstream>


    int main(){
         void printtree(BinaryTree* treenode, int l);
        BinaryTree b;
        int i = 0, lvl;
        string string;
        char forSwitch;
        ifstream infile("BT.txt");
        while (true){
            i = 0;
            cout<<"Press 1 to read from console, press 2 to read from file, press 0 to exit."<<endl;
            cin >> forSwitch;
            switch (forSwitch) {
                case '2':{
                    getline(infile, string);
                    break;
                }
                case '1':{
                    cout<<"Enter the BT"<<endl;
                    cin>>string;
                    break;
                }
                case '0':{
                    return 0;
                }
                default:{
                    cout<<"Incorrect input"<<endl;
                    break;
                }
            }
            b.readBT(string, i);
            cout<<"Height of binary tree: "<<b.height()<<endl;
            cout<<"Enter level of tree"<<endl;
            cin>>lvl;
            cout<<"Number of nodes on the "<<lvl<<" level: "<<b.nodesLvl(lvl)<<endl;
            cout<<"Leafs: ";
            b.leafs();
            cout<<endl;
            cout<<"Internal length: "<<b.internal_lenght()<<endl;
            b.printtree(&b,0);
            b.~BinaryTree();

        }
    }




