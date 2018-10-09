#include <stdio.h>
#include <string.h>

#define N 500

typedef struct Stack {
    char arr[N];
    int index;
}Stack;

void push(Stack* stack, char sym) {
    stack->arr[stack->index] = sym;
    stack->index++;
}

char pop(Stack* stack) {
    stack->index--;
    return stack->arr[stack->index];
}

char top(Stack* stack) {
    return stack->arr[stack->index - 1];
}

int isEmpty(Stack* stack) {
    return (!stack->index);
}

void initStack(Stack* stack) {
    stack->index = 0;
    stack->arr[0] = '\0';
}
