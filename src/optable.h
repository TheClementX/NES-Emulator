#ifndef INSTR_TABLE_HH
#ifndef INSTR_TABLE_HH

#include "cpu6502.h"

/****start interface****/

//struct to house an instructions information
//does not containn name of instruction as this is done
//by the instruction table
struct instruction_info {
	cpu_func inst; 
	cpu_func mem_mode; 
	uint8_t cycles; 
};
typedef struct instruction_info iinf; 

struct op_table_header {
	iinf** table; 
}; 
typedef struct op_table_header* op_table_t; 

op_table_t op_table_new(); 

void op_table_free(op_table_t op_table); 

iinf* op_table_get(op_table_t op_table); 

/****end interface****/

/****start implementation****/

typedef struct op_table_header op_table; 

op_table* op_table_new() {
	//allocate memory
	iinf** result = malloc(sizeof(iinf*) * 16); 
	if(result == NULL) {
		fprintf(stderr, "op_table allocation failed");
		exit(EXIT_FAILURE); 
	}

	for(int i = 0; i < 16; i++) {
		result[i] = malloc(sizeof(iinf)*16); 
		if(result[i] == NULL) {
			fprintf(stderr, "op_table row allocation failed");
			exit(EXIT_FAILURE); 
		}
	}

	//initialize values 
	//NOTE this could have been done with definitions
	//in a case statement but I feel like this is more
	//modular and reauseable as I can make one of these 
	//tables anywhere. This has to be done to make this
	//6502 module actually modular
	//NOTE each entry includes the base clock cycles
	//the base clock cycle is checked and edited in the 
	//body of the function if more time is needed 
	
	/**************************************************/
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][1]->inst = &ORA; result[0][1]->mem_mode = &IZX; result[0][1]->cycles = 6;
	result[0][2]->inst = &EMP; result[0][2]->mem_mode = &EMP; result[0][2]->cycles = 2;
	result[0][3]->inst = &EMP; result[0][3]->mem_mode = &EMP; result[0][3]->cycles = 2;

	result[0][4]->inst = &EMP; result[0][4]->mem_mode = &EMP; result[0][4]->cycles = 2;
	result[0][5]->inst = &ORA; result[0][5]->mem_mode = &ZPZ; result[0][5]->cycles = 3;
	result[0][6]->inst = &ASL; result[0][6]->mem_mode = &ZPZ; result[0][6]->cycles = 5;
	result[0][7]->inst = &EMP; result[0][7]->mem_mode = &EMP; result[0][7]->cycles = 2;
	
	result[0][8]->inst = &PHP; result[0][8]->mem_mode = &IMP; result[0][8]->cycles = 3;
	result[0][9]->inst = &ORA; result[0][9]->mem_mode = &IMD; result[0][9]->cycles = 2;
	result[0][10]->inst = &ASL; result[0][10]->mem_mode = &IMP; result[0][10]->cycles = 2;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	/**************************************************/

	/**************************************************/
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	/**************************************************/

	/**************************************************/
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	/**************************************************/

	/**************************************************/
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	/**************************************************/

	/**************************************************/
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	/**************************************************/

	/**************************************************/
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	/**************************************************/

	/**************************************************/
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	/**************************************************/

	/**************************************************/
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	/**************************************************/

	/**************************************************/
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	/**************************************************/

	/**************************************************/
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	/**************************************************/

	/**************************************************/
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	/**************************************************/

	/**************************************************/
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	/**************************************************/

	/**************************************************/
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	/**************************************************/

	/**************************************************/
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	/**************************************************/

	/**************************************************/
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	/**************************************************/

	/**************************************************/
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	/**************************************************/

	/**************************************************/
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;
	result[0][0]->inst = &BRK; result[0][0]->mem_mode = &IMP; result[0][0]->cycles = 7;

	/**************************************************/

	return result; 
}

void op_table_free(iinf** table) {
	REQUIRES(table != NULL)

	for(int i = 0; i < 16; i++)
		free(table[i]); 
	
	free(table); 
}

iinf* op_table_get(uint8_t ind) {

}

/****end implementation****/

#endif 
