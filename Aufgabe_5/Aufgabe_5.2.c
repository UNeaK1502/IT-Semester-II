#include <stdlib.h>
#define STACK_SIZE 100

typedef struct {
    int* value;   // 
    int count;
    int capacity; // Maximale Größe des Stacks
} StackElement_t;


StackElement_t stack;
void createEmptyStack() {
    stack.value = (int*)malloc(STACK_SIZE * sizeof(int));
    stack.count = -1;
    stack.capacity = STACK_SIZE;
}
void push(int value) {
	if (stack.count < stack.capacity - 1) {             //Wenn anzahl der Elemente < der stack_SIZE ist
        stack.count++;
		stack.value[stack.count] = value;               //neues Element hinzufügen
    }
}
int pop() {	
    if (stack.count >= 0) {
        int value = stack.value[stack.count];
        stack.count--;
        return value;
    }
    return -1; // Fehler wenn versucht wird, von leerem Stack zu lesen
}
void deleteStack() {
    free(stack.value);              
	stack.value = NULL;             //nicht initialisierte Wert setzen
    stack.count = -1;
    stack.capacity = 0;
}
void deleteAllElements() {
    while (stack.count >= 0) {
        pop(); // Entfernt alle Elemente aus dem Stack
	}
}
void countElements() {
	printf("Anzahl der Elemente im Stack: %d\n", stack.count + 1);
}