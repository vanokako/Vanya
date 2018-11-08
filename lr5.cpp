#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
using namespace std;


struct node{     // структура для представления узлов дерева
    int key;
    int size;
    node* left;
    node* right;
    node(int k) { key = k; left = right = NULL; size = 1; }
};


int getsize(node* p){ // обертка для поля size
    if( !p )
        return 0;
    return p->size;
}

void fixsize(node* p){ // установление корректного размера дерева
    p->size = getsize(p->left)+getsize(p->right)+1;
}

node* rotateright(node* p){ // правый поворот вокруг узла p
    node* q = p->left;
    if( !q )
        return p;
    p->left = q->right;
    q->right = p;
    q->size = p->size;
    fixsize(p);
    return q;
}

node* rotateleft(node* q){ // левый поворот вокруг узла q
    node* p = q->right;
    if( !p )
        return q;
    q->right = p->left;
    p->left = q;
    p->size = q->size;
    fixsize(q);
    return p;
}

node* insertroot(node* p, int k){ // вставка нового узла с ключом k в корень дерева p
    if( !p )
        return new node(k);
    if( k < p->key ){
        p->left = insertroot(p->left,k);
        return rotateright(p);
    }
    else {
        p->right = insertroot(p->right,k);
        return rotateleft(p);
    }
}

node* insert(node* p, int k){ // рандомизированная вставка нового узла с ключом k в дерево p
    if( !p ) return new node(k);
    if( rand() % (p->size+1) == 0 )
        return insertroot(p,k);
    if( p->key>k )
        p->left = insert(p->left,k);
    else
        p->right = insert(p->right,k);
    fixsize(p);
    return p;
}


node* join(node* p, node* q){ // объединение двух деревьев, пусть размер левого дерева равен n, правого — m. Тогда p выбирается новым корнем с вероятностью n/(n+m), а q — с вероятностью m/(n+m).
    if( !p )
         return q;
    if( !q )
         return p;
    if( rand()%(p->size + q->size) < p->size ) {
        p->right = join(p->right,q);
        fixsize(p);
        return p;
    }
    else {
        q->left = join(p,q->left);
        fixsize(q);
        return q;
    }
}

node* Delete(node* p){
    if (left)
        delete p->left;
    if (right)
        delete p->right;
    delete p;
    return p = NULL;
}


node* remove(node* p, int k){ // удаление из дерева p первого найденного узла с ключом k
    if( !p )
        return p;
    if( p->key == k ) {
        node* q = join(p->left,p->right);
        delete p;
        return q;
    }
    else if( k < p->key )
        p->left = remove(p->left,k);
    else
        p->right = remove(p->right,k);
    return p;
}


 void printtree(node* treenode, int l){
    if(treenode==NULL){
        for(int i = 0;i<l;++i)
            cout<<"\t";
        cout<<'#'<<endl;
        return;
    }
    printtree(treenode->right, l+1);
    for(int i = 0; i < l; i++)
        cout << "\t";
    cout << treenode->key<< endl;
    printtree(treenode->left,l+1);
}

 int main(){
     node* treap = NULL;
     int key = 0;
     string str;
     char forSwitch;
     while(1){
        cout<<"Press 1 to read from console, press 2 to read from Treap.txt file, press 0 to exit."<<endl;
        cin >> forSwitch;
        getchar();
        switch (forSwitch) {
            case '2':{
                ifstream infile("Treap.txt");
                if(!infile){
                      cout<<"There is no file"<<endl;
                      continue;
                      }
                getline(infile, str);
                break;
            }
            case '1':{
                    cout<<"Enter the keys"<<endl;
                    getline(cin, str);
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
        char* arr = new char[str.size()+1];
        strcpy(arr, str.c_str());
        char* tok;
        tok = strtok(arr, " ");
        while(tok != NULL){
            treap = insert(treap, atoi(tok));
            tok = strtok(NULL, " ");

        }
        printtree(treap,0);
        cin >> key;
        treap = remove(treap, key);
        printtree(treap,0);
        treap = Delete(treap);
    }
 }


