#include <stdlib.h>
#define BUFFER_LENGTH 20
//FIFO Ringpuffer 

typedef struct {
    char buffer[BUFFER_LENGTH];
	int head;          // Index des ersten Elements
	int tail;          // Index des letzten Elements
	int count;         // Anzahl der Elemente im Ringpuffer
} ringbuf_t;

ringbuf_t stack;

void createRingBuffer() {
    stack.head = 0;          // Kopf des Ringpuffers auf 0 setzen
    stack.tail = 0;          // Schwanz des Ringpuffers auf 0 setzen
}
void enqueue(int value) {
    if (stack.count < BUFFER_LENGTH) { // Prüfen, ob der Ringpuffer voll ist
        stack.buffer[stack.tail] = value; // Wert am Ende des Puffers hinzufügen
        stack.tail = (stack.tail + 1) % BUFFER_LENGTH; // Tail weiterbewegen
        stack.count++; // Anzahl der Elemente erhöhen
    } else {
        printf("Ringpuffer ist voll!\n"); // Fehlerausgabe, wenn der Puffer voll ist
	}
}
int dequeue() {
    if (stack.count > 0) { // Prüfen, ob der Ringpuffer leer ist
        int value = stack.buffer[stack.head]; // Wert am Anfang des Puffers lesen
        stack.head = (stack.head + 1) % BUFFER_LENGTH; // Head weiterbewegen
        stack.count--; // Anzahl der Elemente verringern
        return value; // Wert zurückgeben
    } else {
        printf("Ringpuffer ist leer!\n"); // Fehlerausgabe, wenn der Puffer leer ist
        return -1; // Fehlerwert zurückgeben
    }
}
void deleteFIFO() {
    stack.head = 0; // Kopf des Ringpuffers auf 0 setzen
    stack.tail = 0; // Schwanz des Ringpuffers auf 0 setzen
    stack.count = 0; // Anzahl der Elemente auf 0 setzen
}
int freeFIFO() {
    return BUFFER_LENGTH - stack.count; // Verfügbare Kapazität des Ringpuffers zurückgeben
}
void deleteAllElements() {
	while (stack.count > 0) {
        dequeue(); // Elemente nacheinander entfernen
	}
}