#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Aufgabe_4.2.h"
#include "Aufgabe_4.3.h"
#include "Aufgabe_4.4.h"
#include "Aufgabe_4.1.h"
//Hier Aufruf der Methoden und Definiton der teilaufgaben

/// <summary>
/// Rekursiver MergeSort
/// </summary>
void Teilaufgabe_1() {
	int array[] = { 25, 12 , 1, 5, 2, 9, 20 };
	int size = sizeof(array) / sizeof(array[0]);

	printf("Unsortiertes Array:\n");
	for (int i = 0; i < size; i++)
		printf("%d ", array[i]);
	printf("\n");

	mergeSort(array, 0, size - 1);

	printf("Sortiertes Array:\n");
	for (int i = 0; i < size; i++)
		printf("%d ", array[i]);
	printf("\n");
}
/// <summary>
/// </summary>
void Teilaufgabe_2() {
	int array[5] = { 5, 2, 4, 1, 15 };
	int size = sizeof(array) / sizeof(array[0]);
	printf("Unsortiert: \n");
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	quicksort(array, 0, size - 1);
	printf("\nSortiert: \n");
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
}
/// <summary>
/// Schreibe ein Programm, das eine Datei mit vom Anwender interaktiv einzugebendem Dateinamen Öffnet
/// und deren gesamten Inhalt(als ASCII), sowie die DateigrÖße ausgibt
/// </summary>
void Teilaufgabe_3() {
	char dateiname[260];
	long dateigroesse;

	printf("Bitte geben Sie den Dateinamen ein: ");
	if (fscanf_s(stdin, "%259s", dateiname, (unsigned)_countof(dateiname)) != 1) {
		return 1;	//Fehler
	}
	FILE* datei = fopen(dateiname, "r");	// Datei zum Lesen öffnen	

	// Dateigröße ermitteln
	fseek(datei, 0, SEEK_END);		// Zum Ende der Datei springen
	dateigroesse = ftell(datei);	// Aktuelle Position ( = Dateigröße) ermitteln
	rewind(datei);					// Zurück zum Anfang der Datei springen

	// Inhalt ausgeben
	printf("\n--- Dateiinhalt (ASCII) ---\n\n");
	int zeichen;
	while ((zeichen = fgetc(datei)) != EOF) {
		putchar(zeichen);
		//printf("%d ", zeichen);	// ASCII-Wert ausgeben
	}
	fclose(datei);

	printf("\nDateigroesse:\t%d Byte", dateigroesse);

}
/// <summary>
/// Schreibe ein Programm, das eine Datei mit vom Anwender einzugebenden Dateinamen ¨offnet und die
/// hexadezimale Repr¨asentation des Dateiinhalts als ASCII in eine neue Datei schreibt, deren Namen aus
/// dem der Quelldatei durch Anh¨angen von.hex gebildet wird, z.B.: hallo.txt → hallo.txt.hex
/// Dabei sollen 16 Oktette je Zeile ausgegeben werden, und jede Zeile soll mit der relativen Adresse in
/// hexadezimaler Darstellung, bezogen auf den Anfang der Quelldatei, beginnen.Beispielhafte Ausgabe :
/// 00000000 63 53 72 68 69 65 65 62 65 20 6e 69 50 20 6f 72
/// 00000010 72 67 6d 61 2c 6d 64 20 73 61 65 20 6e 69 20 65
/// 00000020 61 44 65 74 20 69 69 6d 20 74 6f 76 20 6d 6e 41
/// </summary>
void Teilaufgabe_4() {
	char quellDateiname[260];		//Maximale Pfadlänge bei windoof 260 Zeichen
	char zielDateiname[260 + 4];	//+4 für ".hex" & binäre Null
	FILE* quelle = NULL;
	FILE* ziel = NULL;

	// Dateinamen abfragen
	printf("Bitte geben Sie den Dateinamen ein: ");
	if (fscanf_s(stdin, "%259s", quellDateiname, (unsigned)_countof(quellDateiname)) != 1) {
		fprintf(stderr, "Fehler beim Einlesen des Dateinamens.\n");
		return 1;
	}

	// Ziel-Dateinamen erstellen
	strcpy_s(zielDateiname, sizeof(zielDateiname), quellDateiname);		// Ziel-Dateinamen prefix erstellen
	strcat_s(zielDateiname, sizeof(zielDateiname), ".hex");				// .hex-Postfix an String anhängen

	// Quelldatei öffnen
	if (fopen_s(&quelle, quellDateiname, "rb") != 0 || quelle == NULL) {// Zum Lesen öffnen -binäre um die Dateigröße zu ermitteln
		perror("Fehler beim Öffnen der Quelldatei");
		//nix zum schließen da
		return 1;
	}

	// Zieldatei öffnen
	if (fopen_s(&ziel, zielDateiname, "w") != 0 || ziel == NULL) {		// Zum schreiben öffnen
		perror("Fehler beim Öffnen der Zieldatei");
		fclose(quelle);													// Quelle wieder freigeben
		return 1;
	}

	// Dateiinhalt lesen und hexadezimal schreiben
	unsigned char buffer[16];
	size_t bytesGelesen;
	unsigned int offset = 0;

	while ((bytesGelesen = fread(buffer, 1, sizeof(buffer), quelle)) > 0) {			//lesen bis buffer voll ist (16 Bytes)
		// Adresse schreiben
		fprintf(ziel, "%08X", offset);				//8-stellige hexadezimale Adresse

		// Hex-Werte schreiben
		for (size_t i = 0; i < bytesGelesen; i++) {
			fprintf(ziel, " %02X", buffer[i]);		//2-stellige hexadezimale Werte
		}
		fprintf(ziel, "\n");
		offset += (unsigned int)bytesGelesen;		//Offset erhöhen
	}
	printf("Hexdump wurde in Datei \"%s\" geschrieben.\n", zielDateiname);

	// Dateien schließen
	fclose(quelle);
	fclose(ziel);

	//ich habe fertig wie flasche leer
	printf("Welche Aufgabe soll bearbeitet werden?\n");
}