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
        Matrix(int i): m(i), squares(0){ 
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

		int get_sqares(){
			return squares;
		}
		
		
        void begin(int k){
	    squares++;
            for (int i = m-k; i < m; i++){
                for (int j = m-k; j < m; j++){
                    Matr[i][j] = squares;
                }
             }
	     	 sqares++;
             for (int i = k; i < m; i++){
                for (int j = 0; j < m-k; j++){
                    Matr[i][j] = squares;
                }
             }
			 squares++;
             for (int i = 0; i < m-k; i++){
                for (int j = k; j < m; j++){
                    Matr[i][j] = squares;
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

		void insert_square (int x, int y, int size){
			squares++;
			for (int i = y; i < y + size; ++i){
				for (int j = x; j < x + size; ++j){
					Matr[i][j] = squares;
				}

 			}
		}   

		void clear_board(){
			for (int i = 0; i < m; i++){
                for (int j = 0; j < m; j++){
					if (Matr[i][j] > standart_sqares)
                    	Matr[i][j] = 0;
                }
             } 
			 sqares = standart_sqares;
		}

		
   
            
};



	void backtracking (Matrix& matr, Matrix& best, int size, int& best_numbers){
		int x = 0, y = 0;
		for (int i = size; i > 0; --i){
			if(!matr.find_space(x, y)){
				x = 0;
				y = 0;
				if (best_numbers > matr.get_sqares()){
					best_numbers = matr.get_sqares();
					best = matr;
				}
				matr.clear_board();
			}
			if(matr.find_space(x, y)){
				if (matr.enough_space(x, y, i)){
					matr.insert_square(x, y, i);
					if (matr.find_space(x, y))
						backtracking(matr,best,i, best_numbers);
				}
			}
	

		}
				
	}
		
		 
	


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
	else if ( size % 3 == 0){
		k = size*2/3;
	}
	else if (size % 5 == 0)
		k = size*3/5;
    else
        k = (size+1)/2;
    Matrix matr(size);
	Matrix best(size);
    matr.begin(k);
	backtracking(matr,best, k-1, best_numbers);
	//matr.Display();
	cout<<endl;
	//best.Display();
	cout<<best_numbers<<endl;
    return 0;
}
