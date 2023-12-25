#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct e {
    int m, n, len, indeks;
    char* input;
    char currStan[2];
    char value, kierunek;
}dane;

void opis();

void konwerter(dane *);

void wypiszStan(dane *);

void maszyna(dane *);

void wniosek(dane *);

int main() {
	dane stan;

	opis();

	printf("Wprowadz m: ");
	scanf("%d", &stan.m);
	printf("Wprowadz n: ");
	scanf("%d", &stan.n);

	stan.len = stan.m + stan.n + 1;  //dlugosc wejscia
    stan.input = (char*)calloc(stan.len + 1, sizeof(char)); //wejscie
	konwerter(&stan);
	printf("\nRoznica zapisana unarnie: %s\n\n", stan.input);
	
    stan.currStan[0] = 'q'; // stan poczatkowy MT
    stan.currStan[1] = '0';
	stan.value = '0'; //wartosc do zmiany
	stan.indeks = 0; //indeks analizowanej wartosci przez MT	
	stan.kierunek = 'L'; //kierunek w ktora posunie sie MT w nastepnej iteracji

	while (stan.kierunek != 'n') {
		wypiszStan(&stan);
		maszyna(&stan);
		if (stan.kierunek != 'n') {
			printf(" %c ", 195);
			stan.input[stan.indeks] = stan.value;
		}
		switch (stan.kierunek) {
		case 'L':
			stan.indeks--;
			break;
		case 'P':
			stan.indeks++;
			break;
		}
		if (stan.indeks == stan.len) {
			stan.len++;
			stan.input = (char*)realloc(stan.input, stan.len+1);
			stan.input[stan.len - 1] = 'B';
			stan.input[stan.len] = '\0';
		}
	}
	wniosek(&stan);
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

void konwerter(dane *ptr) {
    for (int i = 0; i < ptr->len; i++) {
        if (i != ptr->m) ptr->input[i] = '0';
        else ptr->input[i] = '1';
    }
}

void wypiszStan(dane *ptr) {
	int p = 0;
    int len = ptr -> len + 2;
	for (int i = 0; i < len; i++) {
		if (i < ptr->indeks) {
			printf("%c", ptr->input[i]);
		}
		if (i == ptr->indeks || i == (ptr->indeks + 1)) {
			printf("\033[1;32m%c\033[0m", ptr->currStan[p]);
			p++;
		}
		if (i > ptr->indeks + 1 && ptr->input[i - 2] != 'B') {
			printf("%c", ptr->input[i - 2]);
		}
	}
}

void maszyna(dane *ptr) {
	char instr[][3][5] = { {"q1BP", "q5BP", "nnnn"},
						{"q10P", "q21P", "nnnn"},
						{"q31L", "q21P", "q4BL"},
						{"q30L", "q31L", "q0BP"},
						{"q40L", "q4BL", "q60P"},
						{"q5BP", "q5BP", "q6BP"},
						{"nnnn", "nnnn", "nnnn"} };

	int wiersz = ptr->currStan[1] - '0';
	int kolumna;

	switch (ptr->input[ptr->indeks]) {
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
	ptr->currStan[1] = operacja[1];
	ptr->kierunek = operacja[3];

	ptr->value = operacja[2];
}

void wniosek(dane *ptr) {
	int p = 0;
	int suma = 0;
	printf("\n");
	while (ptr->input[p] != '\0') {
		if (ptr->input[p] == '0') suma++;
		p++;
	}
	if (suma != 0) {
		printf("\nRoznica wlasciwa liczb %d i %d wynosi %d\n", ptr->m, ptr->n, suma);
	}
	else {
		printf("\nRoznica wlasciwa liczb %d i %d wynosi %d\n", ptr->m, ptr->n, 0);
	}
}