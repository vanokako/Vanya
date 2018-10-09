#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 500

typedef struct Queue {
    char* arr;
    int start,end, size;
}Queue;

void push(Queue* queue, char sym) {
    if (queue->size == N)
		queue->arr = realloc(queue->arr, 2*queue->size);
	queue->end++;
	queue->arr[queue->end] = sym;		
}

char pop(Queue* queue) {
	char x;
	int h;
	x = queue->arr[queue->start];
	for(h = queue->start; h < queue->end; h++) {
		queue->arr[h] = queue->arr[h+1];
	}
	queue->end--;
	queue->size--;
	return(x);
}

char top(Queue* queue) {
    return queue->arr[queue -> start];
}

int isEmpty(Queue* queue) {
	return queue->size;
}

void initQ(Queue* queue) {
    	queue->start = 0;
	queue->end = -1;
	queue->size = 0;
    	queue->arr = (char*)calloc(N,sizeof(char));
}
