#include <stdio.h>
#include <math.h>
#include "Aufgabe_2.1.h"
#include "Aufgabe_2.2.h"
#include "Aufgabe_2.3.h"
//Hier Aufruf der Methoden und Definiton der teilaufgaben

/// <summary>
/// Schreibe eine Funktion, welche rekursiv die Fakult�t einer Zahl berechnet.
/// </summary>
void Teilaufgabe_1() {
	int number = 0;
	scanf_s("%d", &number);
	int result = rekursion(number);
	printf("Die Fakultaet von %d ist: %d", number, result);
}
/// <summary>
/// Schreibe eine Funktion, welche rekursiv die Fibonacci-Zahl n berechnet
/// </summary>
void Teilaufgabe_2(){
	int number = 0;
	printf("Geben Sie eine Zahl ein:\n");
	scanf_s("%d", &number);
	int result = fibonacci(number);
	printf("Die Fibonacci-Zahl von %d ist: %d", number, result);
}
/// <summary>
/// Schreibe eine Funktion, die rekursiv und ohne Verwendung von Schleifen das gr��te Element in
/// einem Array vom Typ int findet.Dazu bietet es sich an, das Array rekursiv als �Erstes Element� und 
/// Rest aufzufassen, wobei der Rest wiederum aus erstem Element und Rest besteht. Die Rekursion endet,
/// wenn der Rest die L�nge 0 hat
/// </summary>
void Teilaufgabe_3(){
	int array[5] = { 1, 69, 100, 420, 4711 };
	int length = sizeof(array) / sizeof(array[0]);
	int max = findMax(array, length);
	printf("Das groesste Element im Array ist: %d", max);
}
/// <summary>
/// Schreibe eine Funktion, die �berpr�ft, ob in einem Array von Typ int ein Wert doppelt vorkommt. Welche
/// Komplexit�tsklasse hat diese Funktion ?
/// </summary>
void Teilaufgabe_5() {
	int array[5] = { 1, 69, 100, 100, 4711 };
	int length = sizeof(array) / sizeof(array[0]);
	int result = checkDuplicate(array, length);
	if (result !=0) {
		printf("Es gibt ein Duplikat im Array: %d", result);
	}
	else {
		printf("Es gibt kein Duplikat im Array");
	}
}