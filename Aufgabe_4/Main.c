//Libraries

#include <stdio.h>


//Hauptprogramm

int main()
{
	printf("Welche Teilaufgabe soll bearbeitet werden?\n");
	do {
		int inputTask = 0;
		scanf_s("%d", &inputTask);

		switch (inputTask) {

		case 1:
			printf("Teilaufgabe 1 \n");
			Teilaufgabe_1();
			break;
		case 2:
			printf("Teilaufgabe 2 \n");
			Teilaufgabe_2();
			break;
		case 3:
			printf("Teilaufgabe 3 \n");
			Teilaufgabe_3();
			break;
		case 4:
			printf("Teilaufgabe 4 \n");
			Teilaufgabe_4();
			break;
		default:
			printf("Ungueltige Eingabe, erneut versuchen:\n");
			break;
		}
	} while (1);

	return 0;  // Return a valid exit code
}