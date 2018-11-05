#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct treap{
        int value;
        int key;
        treap *left = NULL;
        treap *right = NULL;
} Treap;



        void printtree(Treap* treenode, int l){
                   if(treenode==NULL){
                       for(int i = 0;i<l;++i)
                           cout<<"\t";
                       cout<<'#'<<endl;
                       return;
                   }
                   printtree(treenode->right, l+1);
                   for(int i = 0; i < l; i++)
                       cout << "\t";
                   cout << '('<<treenode->key<<','<<treenode->value<<')'<< endl;
                   printtree(treenode->left,l+1);
                }


       void newBinTree(int val, int key, Treap** Tree) {
            if ((*Tree) == NULL)
            {
                (*Tree) = new Treap; //Выделить память
                (*Tree)->value = val;  //Поместить в выделенное место аргумент
                (*Tree)->key = key;
                (*Tree)->left = (*Tree)->right = NULL;
                return;
            }
            if (key > (*Tree)->key)
                newBinTree(val, key, &(*Tree)->right);//Если аргумент больше чем текущий элемент, поместить его вправо
            else
                newBinTree(val,key, &(*Tree)->left);//Иначе поместить его влево
        }

       void merge(Treap*& treapEl,Treap* leftTreapEl,Treap* rightTreapEl){
         if (leftTreapEl == NULL){
             treapEl = rightTreapEl;
           }
         else if (rightTreapEl == NULL){
             treapEl = leftTreapEl;
           }
         else if (leftTreapEl->key < rightTreapEl->key){
             merge(rightTreapEl->left,leftTreapEl,rightTreapEl->left);
             treapEl = rightTreapEl;
           }
         else{
             merge(leftTreapEl->right,leftTreapEl->right,rightTreapEl);
             treapEl = leftTreapEl;
           }
       }

       bool isExistInTreap(Treap* treapEl, Treap* findEl){
         if (treapEl == NULL){
             return false;
           }
         else if(findEl->key < treapEl->key){
                 isExistInTreap(treapEl->left,findEl);
           }
         else if(findEl->key > treapEl->key){
                 isExistInTreap(treapEl->right,findEl);
           }
         else{
             if (findEl->value == treapEl->value)
               return true;
             else return false;
           }
       }



int main(){
    Treap* tree = NULL;
    int i = 0, x, y;
    string str;
    while (i != 5){
       cin>>x;
       cin>>y;
       newBinTree(x,y, &tree);
       i++;
    }
    printtree(tree,0);

     return 0;
}
