#include <stdlib.h>
#include <stdio.h>
#define STACK_SIZE 100

typedef struct {
    int* value;   // 
    int count;
    int capacity; // Maximale Größe des Stacks
} StackElement_t;


StackElement_t stack;
void createEmptyStack() {
    stack.value = (int*)malloc(STACK_SIZE * sizeof(int));
    stack.count = 0;
    stack.capacity = STACK_SIZE;
}
void push(int value) {
	if (stack.count < stack.capacity - 1) {             //Wenn anzahl der Elemente < der stack_SIZE ist
        stack.count++;
		stack.value[stack.count] = value;               //neues Element hinzufügen
        printf("Wert %d wurde auf dem Stack abgelegt.\n", value);
    }
}
int pop() {	
    if (stack.count >= 1) {
        int value = stack.value[stack.count];
        stack.count--;
        return value;
    }
    return -1; // Fehler wenn versucht wird, von leerem Stack zu lesen
}
void deleteStack() {
    free(stack.value);              
	stack.value = NULL;             //nicht initialisierte Wert setzen
    stack.count = 0;
    stack.capacity = 0;
}
void deleteAllStackElements() {
    while (stack.count >= 1) {
        int value = pop(); // Entfernt alle Elemente aus dem Stack
        printf("Element %d mit dem Wert %d wurde geloescht\n", stack.count, value);
	}
}
void countStackElements() {
	printf("Anzahl der Elemente im Stack: %d\n", stack.count);
}