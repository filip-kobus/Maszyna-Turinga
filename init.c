#include <stdlib.h>
#include <stdio.h>
#include "struct.h"
#include "init.h"

//print short description of the machine's operation
void descript() {
	printf("Emulator MT calculates difference between numbers: \n\n");
	printf("	    /\n");
	printf("	   | m - n for m >= n\n");
	printf("   m - n  <\n");
	printf("	   | 0     for m < n\n");
	printf("	    \\\n\n");
}

//initialize properties of tape
void initialize(data *ptr) {
    printf("Insert m: ");
	scanf("%d", &ptr->m);
	printf("Insert n: ");
	scanf("%d", &ptr->n);

    ptr->len = ptr->m + ptr->n + 1;  //lenght of tape
	ptr->input = (char*)calloc(ptr->len + 1, sizeof(char)); //initialization of tape
	convert(ptr);
	printf("\nNumbers written in unary: %s\n\n", ptr->input);

	ptr->state[0] = 'q'; // initial state of TM
	ptr->state[1] = '0'; //
	ptr->value = '-'; //value that replace currently analyzed number
	ptr->index = 0; //index of currently analized number in TM
	ptr->direction = 'P'; //direction of the next step
}

//convert m and n to unary notation and ansign it to input
void convert(data* ptr) {
	for (int i = 0; i < ptr->len; i++) {
		if (i != ptr->m) ptr->input[i] = '0';
		else ptr->input[i] = '1';
	}
}