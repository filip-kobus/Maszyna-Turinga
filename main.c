#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void opis();

void konwerter(int, int, int, char*);

void dodajStan(char*, int, int, char*);

void maszyna(char*, int*, char*, char*, char*);

void wniosek(char *, int, int);

int main() {
	int m;
	int n;
	opis();
	printf("Wprowadz m: ");
	scanf("%d", &m);
	printf("Wprowadz n: ");
	scanf("%d", &n);
	int len = m + n + 1;  //dlugosc wejscia
    char* input = (char*)calloc(len + 1, sizeof(char));
	konwerter(m, n, len, input);
	printf("\nRoznica zapisana unarnie: %s\n\n", input);
	char currStan[] = "q0"; // stan poczatkowy MT
	char value = 'x'; //wartosc do zmiany
	int indeks = 0; //indeks analizowanej wartosci przez MT	
	char kierunek = 'N';

	while (kierunek != 'n') {
		dodajStan(input, indeks, len + 2, currStan);
		maszyna(input, &indeks, currStan, &value, &kierunek);
		if (kierunek != 'n') {
			printf(" %c ", 195);
			input[indeks] = value;
		}
		switch (kierunek) {
		case 'L':
			indeks--;
			break;
		case 'P':
			indeks++;
			break;
		}
		if (indeks == len) {
			len++;
			input = (char*)realloc(input, len+1);
			input[len - 1] = 'B';
			input[len] = '\0';
		}
	}
	wniosek(input, m, n);
	return 0;
}

void opis() {
	printf("Emulator MT obliczna roznice wlasciwa: \n\n");
	printf("	    /\n");
	printf("	   | m - n dla m >= n\n");
	printf("   m - n  <\n");
	printf("	   | 0     dla m < n\n");
	printf("	    \\\n\n");
}

void konwerter(int m, int n, int len, char* wynik)
{
	for (int i = 0; i < len; i++) {
		if (i != m) wynik[i] = '0';
		else wynik[i] = '1';
	}
}


void dodajStan(char* input, int indeks, int len, char* stan) {
	int p = 0;
	for (int i = 0; i < len; i++) {
		if (i < indeks) {
			printf("%c", input[i]);
		}
		if (i == indeks || i == (indeks + 1)) {
			printf("\033[1;32m%c\033[0m", stan[p]);
			p++;
		}
		if (i > indeks + 1 && input[i - 2] != 'B') {
			printf("%c", input[i - 2]);
		}
	}
}

void maszyna(char* input, int* indeks, char* stan, char* nowa, char *wart) {
	char instr[][3][5] = { {"q1BP", "q5BP", "nnnn"},
						{"q10P", "q21P", "nnnn"},
						{"q31L", "q21P", "q4BL"},
						{"q30L", "q31L", "q0BP"},
						{"q40L", "q4BL", "q60P"},
						{"q5BP", "q5BP", "q6BP"},
						{"nnnn", "nnnn", "nnnn"} };

	int wiersz = stan[1] - '0';
	int kolumna;

	switch (input[*indeks]) {
	case '0':
		kolumna = 0;
		break;
	case '1':
		kolumna = 1;
		break;
	case 'B':
		kolumna = 2;
		break;
	}

	char* operacja = instr[wiersz][kolumna];
	stan[1] = operacja[1];
	*nowa = operacja[2];

	*wart = operacja[3];
}

void wniosek(char* wejscie, int a, int b) {
	int p = 0;
	int suma = 0;
	printf("\n");
	while (wejscie[p] != '\0') {
		if (wejscie[p] == '0') suma++;
		p++;
	}
	if (suma != 0) {
		printf("\nRoznica wlasciwa liczb %d i %d wynosi %d\n", a, b, suma);
	}
	else {
		printf("\nRoznica wlasciwa liczb %d i %d wynosi %d\n", a, b, 0);
	}
}