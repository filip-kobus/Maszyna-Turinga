#include <stdlib.h>
#include <stdio.h>
#include "struct.h"
#include "mt.h"

//display the tape with the current state, preceding analyzed element
void displayState(data* ptr) {
	int p = 0;
	int len = ptr->len + 2;
	for (int i = 0; i < len; i++) {
		if (i < ptr->index) {
			printf("%c", ptr->input[i]);
		}
		if (i == ptr->index || i == (ptr->index + 1)) {
			printf("\033[1;32m%c\033[0m", ptr->state[p]);
			p++;
		}
		//strips every B from the end of tape
		if (i > ptr->index + 1 && ptr->input[i - 2] != 'B') {
			printf("%c", ptr->input[i - 2]);
		}
	}
}

//depend on current properties, takes the next step
void runMachine(data* ptr) {
	//array of machine states - each row is following state
	//each column is respondent to the value of tape: 0 - col[0], 1 - col[1], B - col[2]
	char instr[][3][5] = { {"q1BP", "q5BP", "nnnn"},
						{"q10P", "q21P", "nnnn"},
						{"q31L", "q21P", "q4BL"},
						{"q30L", "q31L", "q0BP"},
						{"q40L", "q4BL", "q60P"},
						{"q5BP", "q5BP", "q6BP"},
						{"nnnn", "nnnn", "nnnn"} };

	int row = ptr->state[1] - '0';
	int column;

	switch (ptr->input[ptr->index]) {
	case '0':
		column = 0;
		break;
	case '1':
		column = 1;
		break;
	case 'B':
		column = 2;
		break;
	}

	char* step = instr[row][column];
	ptr->state[1] = step[1]; //next state
	ptr->direction = step[3]; //direction (L or P)

	ptr->value = step[2]; //new value
}

//print obtained result
void result(data* ptr) {
	int p = 0;
	int sum = 0;
	printf("\n");
	while (ptr->input[p] != '\0') {
		if (ptr->input[p] == '0') sum++;
		p++;
	}
	if (sum != 0) {
		printf("\nDifference between numbers: %d and %d is equal to: %d\n", ptr->m, ptr->n, sum);
	}
	else {
		printf("\nDifference between numbers: %d and %d is equal to: %d\n", ptr->m, ptr->n, 0);
	}
}