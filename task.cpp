#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Matrix
{
    private:
        int **Matr;
        int m;
        int squares;
        int color;


    public:
        Matrix(int i): m(i), squares(0), color(0){
            Matr = new int*[m];
            for (int i = 0; i < m; i++)
                Matr[i] = new int[m];
            for (int i = 0; i < m; i++){
                for (int j = 0; j < m; j++){
                    Matr[i][j] = 0;
                }
             }
        }

         Matrix(const Matrix& N){
            m = N.m;
            squares = N.squares;
            color = N.color;
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
                color = temp.color;
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

          int counter(int x, int y){
              int count = 0;
              int check = Matr[y][x];
              for(int j = x; j < m; j ++){
                  if (Matr[y][j] != check)
                      return count;
                  else
                      count++;
              }
              return count;

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

        bool enough_two(int x, int y){
            if (Matr[y][x+1] == 0 && Matr[y+1][x+1] == 0 && Matr[y+1][x] == 0)
                return true;
            return false;
        }

        bool insert_square(int x, int y, int size){
            if(!enough_space(x,y,size))
                return false;
            squares++;
            color++;
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    Matr[i + y][j + x] = color;
            return true;
        }

        void clear_board(int x, int y, int size){
            for (int i = y; (i < size) && (Matr[i][x] == color); i++)
                    for (int j = x; (j < size) && (Matr[i][j] == color); j++)
                        Matr[i][j] = 0;
            squares--;
            color--;

        }


        void backtracking (Matrix& best, int size,int x, int y, int& best_numbers){
            if (squares >= best_numbers)
                return;
            for (int i = size; i >= 2; i--){
                if(Matr[y][x-1] == color)
                    color++;
                if (insert_square(x, y, i)){
                    int x1 = x;
                    int y1 = y;
                    if(find_space(x1,y1) && enough_two(x1,y1))
                        backtracking(best, size, x1, y1, best_numbers);
                    else if (!find_space(x1, y1)){
                        if(squares < best_numbers){
                            best_numbers = squares;
                            best = *this;
                        }
                        clear_board(x, y, size);
                        return;
                    }
                    clear_board(x, y, size);
                }
            }

        }

        void print_ans(){
            vector<int> check;
            int count = 0;
            for (int i = 0; i < m; i++){
                for(int j = 0; j < m; j++){
                    if (find(check.begin(),check.end(), Matr[i][j]) == check.end() ){
                        check.push_back(Matr[i][j]);
                        cout<<i+1<<' '<<j+1<<' '<<counter(j,i)<<endl;
                        count = 0;
                    }
                }
            }
        }

};





int main(){
    int size, k;
    cin >> size;
    int best_numbers = size*size;
    if (size % 2 == 0)
        k = size/2;
   else if ( size % 3 == 0)
        k = size*2/3;

    else if (size % 5 == 0)
        k = size*3/5;
    else
        k = size-2;
    Matrix matr(size);
    Matrix best(size);
    matr.backtracking(best, k, 0, 0, best_numbers);
    int x = 0, y = 0;
    if (matr.find_space(x, y)){
        cout<<"Can't do it"<<endl;
        return 0;
    }
    cout<<best_numbers<<endl;
    best.print_ans();
    cout<<endl;
    //best.Display();
    return 0;
}
