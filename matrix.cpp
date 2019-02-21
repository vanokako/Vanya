#include <iostream>
#define standart_sqares 3 

using namespace std;
 
class Matrix
{
    private:
        int **Matr;
        int m;
	int sqares;
 
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
        Matrix(int i): m(i), sqares(0){ 
            Create(); 
        }
	
		 Matrix(const Matrix& N){
         	m = N.m;
			sqares = N.sqares;
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
        		Matr = new int*[m];
        		for (int i = 0; i < m; i++)
            		Matr[i] = new int[m];
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
			return sqares;
		}
		
		
        void begin(int k){
	    sqares++;
            for (int i = m-k; i < m; i++){
                for (int j = m-k; j < m; j++){
                    Matr[i][j] = sqares;
                }
             }
	     	 sqares++;
             for (int i = k; i < m; i++){
                for (int j = 0; j < m-k; j++){
                    Matr[i][j] = sqares;
                }
             }
			 sqares++;
             for (int i = 0; i < m-k; i++){
                for (int j = k; j < m; j++){
                    Matr[i][j] = sqares;
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

		void insert_sqare (int x, int y, int size){
			sqares++;
			for (int i = y; i < y + size; ++i){
				for (int j = x; j < x + size; ++j){
					Matr[i][j] = sqares;
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



	void backtracking (Matrix& matr, int size, int& worth_numbers){
		int x = 0, y = 0;
		for (int i = size; i > 0; --i){
			//matr.Display();
			//cout<<endl<<"==============="<<endl;
			if(!matr.find_space(x, y)){
				x = 0;
				y = 0;
				if (worth_numbers > matr.get_sqares())
					worth_numbers = matr.get_sqares();
				matr.clear_board();
			}
			if(matr.find_space(x, y)){
				if (matr.enough_space(x, y, i)){
					matr.insert_sqare(x, y, i);
					if (matr.find_space(x, y))
						backtracking(matr,i, worth_numbers);
				}
			}
	

		}
					
	}
		
		 
	


int main(){
    int size, k;
    cin >> size;

	int worth_numbers = size*size;
    if (size % 2 == 0){
        k = size/2;
	}
	else if ( size % 3 == 0){
		k = size*2/3;
	}
	else if (size % 5 == 0)
		k = size*3/5;
    else
        k = (size+1)/2;
    Matrix matr(size);
    matr.begin(k);
	matr.Display();
	backtracking(matr, k-1, worth_numbers);
	matr.Display();
	cout<<worth_numbers<<endl;
    return 0;
}
