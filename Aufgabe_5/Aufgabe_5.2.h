#pragma once
typedef struct  {
	int value;
	int count;
} StackElement_t;
void createEmptyStack();
void push(int value);
void pop();
void deleteStack();
void deleteAllElements();
void countElements();