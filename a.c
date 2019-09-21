#include <stdio.h>
#define N 100



	int findMax(int* arr){
		int max = 0;
		for(int i = 0; i < N; i++)
			if (arr[i] > max)
				max = arr[i];
		printf("%d\n", max);
		return (max);
	}

	int findMin(int* arr){
		int min = arr[0];
		int index = 0;
			for(int i = 0; i < N; i++)
				if (arr[i] < min) {
					min = arr[i];
					index = i;
				}
		printf("%d\n", min);
		return index;
		
	}

	int sum(int* arr) {
		int sum = 0;		
		int index = findMin(arr);
		for(int i = 0; i < index; i++) {
			sum += arr[i];
		}
		printf("%d\n", sum);

}




int main(){
	int arr[N];
	for( int i = 0; i < N; i++){
		scanf("%d", &arr[i]);
	}
	int a;
	scanf("%d", &a);
	switch(a){
		case 0:
			findMax(arr);
			break;
		case 1:
			findMin(arr);
			break;
		case 2:
			printf("%d\n", findMax(arr) - findMin(arr));
			break;
		case 3:
			printf("%d\n", sum(arr));
			
			
	}

}


