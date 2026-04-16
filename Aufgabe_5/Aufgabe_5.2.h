#pragma once
#define STACK_SIZE 100
typedef struct  {
	int value[STACK_SIZE];
	int count;
} StackElement_t;
void createEmptyStack();
void push(int value);
int  pop();
void deleteStack();
void deleteAllStackElements();
void countStackElements();