/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Spring 2017                              *
 *  Author: Ulrich Kremer                    *
 *  Student Version                          *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

typedef struct node {
	int val;
	struct node *next;
} node_t;

int numberOfRegisters(Instruction *head) {

	/* Traverse through instructions and find 
	count based off of largest numbered register*/

	Instruction *ptr = head;
	int count = 0;

	while (ptr){
		switch (ptr -> opcode) {
			case LOADI:
				if (count < ptr -> field2)
					count = ptr -> field2;					
			case LOADAI:
				if (count < ptr -> field3)
					count = ptr -> field3;
			case STOREAI:
				if (count < ptr -> field1)
					count = ptr -> field1;
			case ADD: case SUB: case MUL: case DIV:
				if (count < ptr -> field3)
					count = ptr -> field3;
			case OUTPUTAI:
		}

		ptr = ptr -> next;
	}

	return count;
}

void criticalRegisters(Instruction *head, int *listOfRegisters, int num) {
	
	Instruction *ptr;
	ptr = head;
	
	/*Initialize first node of list of critical registers*/
	node_t *listOfCriticalRegisters = malloc(sizeof(node_t));
	listOfCriticalRegisters -> val = 0;
	listOfCriticalRegisters -> next = NULL;

	/*Ptr is pointing to the last instruction*/
	while (ptr -> next){
		ptr = ptr -> next;
	}

	/*Traverse the instruction list from the end to the 
	front. Add registers to listOfCriticalRegisters if
	the registers are in the field. */

	node_t *temp; 
	while (ptr -> prev) {

		temp = listOfCriticalRegisters;

		switch(ptr -> opcode) {
			case LOADI: 
				break;
			case LOADAI:
			case STOREAI:
			case ADD:
			case SUB:
			case MUL:
			case DIV:

				/*If the register in the third field is a critical register,
				all registers in the instruction are added to the 
				listOfCriticalRegisters*/

				int critInstruction = 0;

				while (temp) {
					if (ptr -> field3 == temp -> val) {
						critInstruction = 1;
					}

					temp = temp -> next;
				}

				if (!critInstruction)
					break;

				temp = malloc(sizeof(node_t));
				temp -> val = ptr -> field1;
				temp -> next = malloc(sizeof(node_t));
				temp -> next -> val = ptr -> field2;
				temp -> next -> next = NULL;

			case OUTPUTAI:

				/*Add any register used in OUTPUTAI* to 
				listOfCriticalRegisters */

				while (temp -> next) {
					temp = temp -> next;
				}

				temp -> next = malloc(sizeof(node_t));
				temp -> next -> val = ptr -> field1;
				temp -> next -> next = NULL;
		}

		ptr = ptr -> prev;
	}
	



	return;
}

void deleteInstructions(Instruction *head, int *listOfregisters)
int main()
{
	Instruction *head;

	head = ReadInstructionList(stdin);
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}

	/* YOUR CODE GOES HERE */

	/*Find out number of registers and malloc an array 
	of ints*/
	int	num = numberOfRegisters(head);
	int *listOfRegisters = malloc(sizeof(int) * num);

	/*Initialize array of registers to 0*/
	int i;
	for (i = 0; i < num; i++){
		regs[i] = 0;
	}



	if (head) 
		PrintInstructionList(stdout, head);
	
	return EXIT_SUCCESS;
}

