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
    stack.head = 0;                                     // Kopf des Ringpuffers auf 0 setzen
    stack.tail = 0;                                     // Schwanz des Ringpuffers auf 0 setzen
}
void enqueueChar(char value) {
    if (stack.count < BUFFER_LENGTH) {                  // Prüfen, ob der Ringpuffer voll ist
        stack.buffer[stack.tail] = value;               // Wert am Ende des Puffers hinzufügen
        stack.tail = (stack.tail + 1) % BUFFER_LENGTH;  // Tail weiterbewegen
        stack.count++;                                  // Anzahl der Elemente erhöhen
        printf("Hinzugefuegtes Element: %c\n", value); 
    } else {
        // Überschreiben des ältesten Elements
        stack.buffer[stack.tail] = value;
        stack.tail = (stack.tail + 1) % BUFFER_LENGTH;
        stack.head = (stack.head + 1) % BUFFER_LENGTH;  // Head nachziehen, da ältestes Element überschrieben wird
        printf("Ringpuffer voll, ältestes Element überschrieben: %c\n", value);
    }
}
char* dequeueString() {
    // Maximal so viele Zeichen wie im Puffer groß ist + 1 für binäre Null '\0'
    char* string = (char*)malloc(stack.count + 1);
    if (!string) return NULL;
	int i = 0;                                          // Hilfsvariable für String
	//String zusammenbauen
    char c;
    do {
        c = stack.buffer[stack.head];
        stack.head = (stack.head + 1) % BUFFER_LENGTH;
        stack.count--;
        string[i++] = c;
    } while (c != '\0' && stack.count > 0);

    string[i] = '\0';
	printf("Entferntes Element: %s\n", string);         // Ausgabe des entfernten Strings
    return string;
}
char readFIFO() {
    if (stack.count > 0) {                              // Prüfen, ob was im Ringpuffer ist
        return stack.buffer[stack.head];                // Wert am Anfang des Puffers zurückgeben
    } else {
        printf("Ringpuffer ist leer!\n");               // Fehlerausgabe, wenn der Puffer leer ist
        return -1;                                      // Fehlerwert zurückgeben
    }
}
void deleteFIFO() {
    stack.head = 0; 
    stack.tail = 0; 
    stack.count = 0; 
}
int freeFIFO() {
    return BUFFER_LENGTH - stack.count; // Verfügbare Kapazität des Ringpuffers zurückgeben
}
void deleteAllFIFOElements() {
	while (stack.count > 0) {
        dequeueString(); // Elemente nacheinander entfernen
	}
}