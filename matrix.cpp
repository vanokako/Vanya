#include <iostream>
#define standart_sqares 3

using namespace std;

class Matrix
{
    private:
        int **Matr;
        int m;
        int squares;

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
        Matrix(int i): m(i), squares(4){
            Create();
        }

         Matrix(const Matrix& N){
            m = N.m;
            squares = N.squares;
            Matr = new int*[m];
            for (int i = 0; i < m; i++)
                Matr[i] = new int[m];

            for (int i = 0; i < m; i++){
                for (int j = 0; j < m; j++){
                    Matr[i][j] = N.Matr[i][j];
                }
            }
        }

        Matrix &operator = (Matrix const & origin){
            if(this != &origin){
                Matrix temp(origin);
                m = temp.m;
                squares = temp.squares;
                for (int i = 0; i < m; i++){
                    for (int j = 0; j < m; j++){
                        Matr[i][j] = origin.Matr[i][j];
                    }
                }
            }
            return *this;
        }




        ~Matrix(){
            for (int i = 0; i < m; i++)
                delete[] Matr[i];
            delete[] Matr;
        }

        int get_squares(){
            return squares;
        }


        void begin(int k){
            for (int i = m-k; i < m; i++){
                for (int j = m-k; j < m; j++){
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

        bool find_space(int& x, int& y){
            for (int i = 0; i < m; ++i){
                for (int j = 0; j < m; ++j){
                    if (Matr[i][j] == 0){
                        x = j;
                        y = i;
                        return true;
                    }
                }
            }
            return false;
        }

        bool enough_space (int x, int y, int size){
            if ((x + size) > m || (y + size) > m)
                return false;
            for (int i = y; i < y + size; ++i){
                for (int j = x; j < x + size; ++j){
                    if (Matr[i][j] != 0)
                        return false;
                }

            }
            return true;
        }



        bool insert_square(int x, int y, int size){
            if(!enough_space(x,y,size))
                return false;
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    Matr[i + y][j + x] = squares;
            return true;
        }

        void clear_board(int x, int y, int size){
            for (int i = y; (i < size) && (Matr[i][x] == squares); i++)
                    for (int j = x; (j < size) && (Matr[i][j] == squares); j++)
                        Matr[i][j] = 0;

        }


        void backtracking (Matrix& best, int size,int x, int y, int& best_numbers){
            if (squares >= best_numbers)
                return;
            for (int i = size; i > 0; --i){
                if (insert_square(x, y, i)){
                    squares++;
                    int x1 = x;
                    int y1 = y;
                    if(find_space(x1,y1))
                        backtracking(best, size, x1, y1, best_numbers);
                    else{
                        squares--;
                        if(squares < best_numbers){
                            best_numbers = squares;
                            best = *this;
                        }
                        clear_board(x, y, size);
                        return;
                    }
                    squares--;
                    clear_board(x, y, size);
                }
            }
        }

};








int main(){
    int size, k;
    cin >> size;

    int best_numbers = size*size;
    if (size % 2 == 0){
        k = size/2;
        cout << "4" << endl;
        cout << "1 1 " << k << endl;
        cout << k+1 << " 1 " << k << endl;
        cout << "1 " << k+1 << " " << k << endl;
        cout << k+1 << " " << k+1 << " "<< k << endl;
        return 0;
    }
   else if ( size % 3 == 0)
        k = size*2/3;

    else if (size % 5 == 0)
        k = size*3/5;
    else
        k = (size+1)/2;
    Matrix matr(size);
    Matrix best(size);
    matr.begin(k);
    matr.backtracking(best, (size+1)/2, 0, 0, best_numbers);
    cout<<endl;
    //best.Display();
    cout<<best_numbers<<endl;
    return 0;
}
