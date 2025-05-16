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
		fprintsf(stderr, "op_table allocation failed");
		exit(EXIT_FAILURE); 
	}

	for(int i = 0; i < 16; i++) {
		result[i] = malloc(sizeof(iinf)*16); 
		if(result[i] == NULL) {
			fprintsf(stderr, "op_table row allocation failed");
			exit(EXIT_FAILURE); 
		}
	}

	//initialize values 
	//NOTE this could have been done with definitions
	//in a case statement but I feel like this is more
	//modular and reauseable as I can make one of these 
	//tables anywhere. This has to be done to make this
	//6502 module actually modular
	
	
		

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
