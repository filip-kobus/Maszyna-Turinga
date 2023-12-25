#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "init.h"
#include "mt.h"

int main() {
	data machine;

	descript();

    initialize(&machine);

	//if the direction == 'n', machine finished it work
	while (machine.direction != 'n') {
		displayState(&machine);
		runMachine(&machine);
		if (machine.direction != 'n') {
			printf(" %c ", 195);
			machine.input[machine.index] = machine.value; //current value is replaced with new one
		}
		switch (machine.direction) {
		case 'L':
			machine.index--;
			break;
		case 'P':
			machine.index++;
			break;
		}
		//if machine needs acces to element which is after initial length
		//this code extends the initial tape by 1 index
		if (machine.index == machine.len) {
			machine.len++;
			machine.input = (char*)realloc(machine.input, machine.len + 1);
			machine.input[machine.len - 1] = 'B';
			machine.input[machine.len] = '\0';
		}
	}

	result(&machine);
	
	return 0;
}