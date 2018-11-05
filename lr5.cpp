#include <iostream>
#include <cstdlib>

using namespace std;

void print_tabs(size_t tabs_count) {
    for (size_t i = 0; i < tabs_count; ++i)
        std::cout << '\t';
}

class BinTree {
    private:
        int value;
        BinTree *left;
        BinTree *right;


    public:
        void printtree(BinTree* treenode, int l){
                   if(treenode==NULL){
                       for(int i = 0;i<l;++i)
                           cout<<"\t";
                       cout<<'#'<<endl;
                       return;
                   }
                   printtree(treenode->right, l+1);
                   for(int i = 0; i < l; i++)
                       cout << "\t";
                   cout << treenode->value<< endl;
                   printtree(treenode->left,l+1);
                }

        BinTree(){
            left = NULL;
            right = NULL;
        }

        friend void newBinTree(int val, BinTree** Tree) {
            if ((*Tree) == NULL)
            {
                (*Tree) = new BinTree; //Выделить память
                (*Tree)->value = val;  //Поместить в выделенное место аргумент
                (*Tree)->left = (*Tree)->right = NULL;
                return;
            }
            if (val > (*Tree)->value)
                newBinTree(val, &(*Tree)->right);//Если аргумент больше чем текущий элемент, поместить его вправо
            else
                newBinTree(val, &(*Tree)->left);//Иначе поместить его влево
        }


};

int main(){
    BinTree* tree = NULL;
    int i = 0, x;
    string str;
    while (i != 5){
       cin>>x;
       newBinTree(x, &tree);
       i++;
    }
    tree->printtree(tree,0);

     return 0;
}
