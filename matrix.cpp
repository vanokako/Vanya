#include <iostream>

using namespace std;
 
class Matrix
{
    private:
        int **Matr;
        int m;
 
        void Create(){
            Matr = new int*[m];
            for (int i = 0; i < m; i++)
                Matr[i] = new int[m];
            for (int i = 0; i < m; i++){
                for (int j = 0; j < m; j++){
                    Matr[i][j] = 0;
                }
             }
        }
 
    public:
        Matrix(int i): m(i){ 
            Create(); 
        }
        ~Matrix(){
            for (int i = 0; i < m; i++)
                delete[] Matr[i];
            delete[] Matr;
        }
 
        void begin(int k){
            for (int i = 0; i < k; i++){
                for (int j = 0; j < k; j++){
                    Matr[i][j] = 1;
                }
             }
             for (int i = k; i < m; i++){
                for (int j = 0; j < m-k; j++){
                    Matr[i][j] = 2;
                }
             }
             for (int i = 0; i < m-k; i++){
                for (int j = k; j < m; j++){
                    Matr[i][j] = 3;
                }
             }
          }
          void Display(){
            for(int i = 0; i < m; i++){
                for(int j = 0; j < m; j++){
                    cout << Matr[i][j];
                }
                cout << endl;
            }
        }
        
        
        void take_sqare(int k){
            
 
            
};



int main(){
    int size, k;
    cin >> size;
    if (size % 2 == 0)
        k = size/2;
    else
        k = (size+1)/2;
    Matrix matr(size);
    matr.begin(k);
    matr.Display();
    return 0;
}


