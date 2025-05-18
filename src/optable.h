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
	
	/*0************************************************/
	
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
	result[0][11]->inst = &EMP; result[0][11]->mem_mode = &EMP; result[0][11]->cycles = 2;

	result[0][12]->inst = &EMP; result[0][12]->mem_mode = &EMP; result[0][12]->cycles = 2; 
	result[0][13]->inst = &ORA; result[0][13]->mem_mode = &ABS; result[0][13]->cycles = 4;
	result[0][14]->inst = &ASL; result[0][14]->mem_mode = &ABS; result[0][14]->cycles = 6;
	result[0][15]->inst = &EMP; result[0][15]->mem_mode = &EMP; result[0][15]->cycles = 2;

	/*0************************************************/

	/*1************************************************/
	
	result[1][0]->inst = &BPL; result[1][0]->mem_mode = &REL; result[1][0]->cycles = 2;
	result[1][1]->inst = &ORA; result[1][1]->mem_mode = &IZY; result[1][1]->cycles = 5;
	result[1][2]->inst = &EMP; result[1][2]->mem_mode = &EMP; result[1][2]->cycles = 2;
	result[1][3]->inst = &EMP; result[1][3]->mem_mode = &EMP; result[1][3]->cycles = 2;

	result[1][4]->inst = &EMP; result[1][4]->mem_mode = &EMP; result[1][4]->cycles = 2;
	result[1][5]->inst = &ORA; result[1][5]->mem_mode = &ZPX; result[1][5]->cycles = 4;
	result[1][6]->inst = &ASL; result[1][6]->mem_mode = &ZPX; result[1][6]->cycles = 6;
	result[1][7]->inst = &EMP; result[1][7]->mem_mode = &EMP; result[1][7]->cycles = 2;
	
	result[1][8]->inst = &CLC; result[1][8]->mem_mode = &IMP; result[1][8]->cycles = 2;
	result[1][9]->inst = &ORA; result[1][9]->mem_mode = &ABY; result[1][9]->cycles = 4;
	result[1][10]->inst = &EMP; result[1][10]->mem_mode = &EMP; result[1][10]->cycles = 2;
	result[1][11]->inst = &EMP; result[1][11]->mem_mode = &EMP; result[1][11]->cycles = 2;

	result[1][12]->inst = &EMP; result[1][12]->mem_mode = &EMP; result[1][12]->cycles = 2; 
	result[1][13]->inst = &ORA; result[1][13]->mem_mode = &ABX; result[1][13]->cycles = 4;
	result[1][14]->inst = &ASL; result[1][14]->mem_mode = &ABX; result[1][14]->cycles = 7;
	result[1][15]->inst = &EMP; result[1][15]->mem_mode = &EMP; result[1][15]->cycles = 2;

	/*1************************************************/

	/*2************************************************/
	
	result[2][0]->inst = &JSR; result[2][0]->mem_mode = &ABS; result[2][0]->cycles = 6; 
	result[2][1]->inst = &AND; result[2][1]->mem_mode = &IZX; result[2][1]->cycles = 6;
	result[2][2]->inst = &EMP; result[2][2]->mem_mode = &EMP; result[2][2]->cycles = 2;
	result[2][3]->inst = &EMP; result[2][3]->mem_mode = &EMP; result[2][3]->cycles = 2;

	result[2][4]->inst = &BIT; result[2][4]->mem_mode = &ZPZ; result[2][4]->cycles = 3;
	result[2][5]->inst = &AND; result[2][5]->mem_mode = &ZPZ; result[2][5]->cycles = 3;
	result[2][6]->inst = &ROL; result[2][6]->mem_mode = &ZPZ; result[2][6]->cycles = 5;
	result[2][7]->inst = &EMP; result[2][7]->mem_mode = &EMP; result[2][7]->cycles = 2;
	
	result[2][8]->inst = &PLP; result[2][8]->mem_mode = &IMP; result[2][8]->cycles = 3;
	result[2][9]->inst = &AND; result[2][9]->mem_mode = &IMD; result[2][9]->cycles = 2;
	result[2][10]->inst = &ROL; result[2][10]->mem_mode = &IMP; result[2][10]->cycles = 2;
	result[2][11]->inst = &EMP; result[2][11]->mem_mode = &EMP; result[2][11]->cycles = 2;

	result[2][12]->inst = &BIT; result[2][12]->mem_mode = &ABS; result[2][12]->cycles = 4; 
	result[2][13]->inst = &AND; result[2][13]->mem_mode = &ABS; result[2][13]->cycles = 4;
	result[2][14]->inst = &ROL; result[2][14]->mem_mode = &ABS; result[2][14]->cycles = 6;
	result[2][15]->inst = &EMP; result[2][15]->mem_mode = &EMP; result[2][15]->cycles = 2;

	/*2************************************************/

	/*3************************************************/
	
	result[3][0]->inst = &BMI; result[3][0]->mem_mode = &REL; result[3][0]->cycles = 2;
	result[3][1]->inst = &AND; result[3][1]->mem_mode = &IZY; result[3][1]->cycles = 5;
	result[3][2]->inst = &EMP; result[3][2]->mem_mode = &EMP; result[3][2]->cycles = 2;
	result[3][3]->inst = &EMP; result[3][3]->mem_mode = &EMP; result[3][3]->cycles = 2;

	result[3][4]->inst = &EMP; result[3][4]->mem_mode = &EMP; result[3][4]->cycles = 2;
	result[3][5]->inst = &AND; result[3][5]->mem_mode = &ZPX; result[3][5]->cycles = 4;
	result[3][6]->inst = &ROL; result[3][6]->mem_mode = &ZPX; result[3][6]->cycles = 5;
	result[3][7]->inst = &EMP; result[3][7]->mem_mode = &EMP; result[3][7]->cycles = 6;
	
	result[3][8]->inst = &SEC; result[3][8]->mem_mode = &IMP; result[3][8]->cycles = 3;
	result[3][9]->inst = &AND; result[3][9]->mem_mode = &ABY; result[3][9]->cycles = 4;
	result[3][10]->inst = &EMP; result[3][10]->mem_mode = &IMP; result[3][10]->cycles = 2;
	result[3][11]->inst = &EMP; result[3][11]->mem_mode = &EMP; result[3][11]->cycles = 2;

	result[3][12]->inst = &EMP; result[3][12]->mem_mode = &EMP; result[3][12]->cycles = 2; 
	result[3][13]->inst = &AND; result[3][13]->mem_mode = &ABX; result[3][13]->cycles = 4;
	result[3][14]->inst = &ROL; result[3][14]->mem_mode = &ABX; result[3][14]->cycles = 7;
	result[3][15]->inst = &EMP; result[3][15]->mem_mode = &EMP; result[3][15]->cycles = 2;

	/*3************************************************/

	/*4************************************************/
	
	result[4][0]->inst = &RTI; result[4][0]->mem_mode = &IMP; result[4][0]->cycles = 6;
	result[4][1]->inst = &EOR; result[4][1]->mem_mode = &IZX; result[4][1]->cycles = 6;
	result[4][2]->inst = &EMP; result[4][2]->mem_mode = &EMP; result[4][2]->cycles = 2;
	result[4][3]->inst = &EMP; result[4][3]->mem_mode = &EMP; result[4][3]->cycles = 2;

	result[4][4]->inst = &EMP; result[4][4]->mem_mode = &EMP; result[4][4]->cycles = 2;
	result[4][5]->inst = &EOR; result[4][5]->mem_mode = &ZPZ; result[4][5]->cycles = 3;
	result[4][6]->inst = &LSR; result[4][6]->mem_mode = &ZPZ; result[4][6]->cycles = 5;
	result[4][7]->inst = &EMP; result[4][7]->mem_mode = &EMP; result[4][7]->cycles = 2;
	
	result[4][8]->inst = &PHA; result[4][8]->mem_mode = &IMP; result[4][8]->cycles = 3;
	result[4][9]->inst = &EOR; result[4][9]->mem_mode = &IMD; result[4][9]->cycles = 2;
	result[4][10]->inst = &LSR; result[4][10]->mem_mode = &IMP; result[4][10]->cycles = 2;
	result[4][11]->inst = &EMP; result[4][11]->mem_mode = &EMP; result[4][11]->cycles = 2;

	result[4][12]->inst = &JMP; result[4][12]->mem_mode = &ABS; result[4][12]->cycles = 3; 
	result[4][13]->inst = &EOR; result[4][13]->mem_mode = &ABS; result[4][13]->cycles = 4;
	result[4][14]->inst = &LSR; result[4][14]->mem_mode = &ABS; result[4][14]->cycles = 6;
	result[4][15]->inst = &EMP; result[4][15]->mem_mode = &EMP; result[4][15]->cycles = 2;

	/*4************************************************/

	/*5************************************************/
	
	result[5][0]->inst = &BVC; result[5][0]->mem_mode = &REL; result[0][0]->cycles = 2;
	result[5][1]->inst = &EOR; result[5][1]->mem_mode = &IZY; result[0][1]->cycles = 5;
	result[5][2]->inst = &EMP; result[5][2]->mem_mode = &EMP; result[0][2]->cycles = 2;
	result[5][3]->inst = &EMP; result[5][3]->mem_mode = &EMP; result[0][3]->cycles = 2;

	result[5][4]->inst = &EMP; result[5][4]->mem_mode = &EMP; result[0][4]->cycles = 2;
	result[5][5]->inst = &EOR; result[5][5]->mem_mode = &ZPX; result[0][5]->cycles = 4;
	result[5][6]->inst = &LSR; result[5][6]->mem_mode = &ZPX; result[0][6]->cycles = 6;
	result[5][7]->inst = &EMP; result[5][7]->mem_mode = &EMP; result[0][7]->cycles = 2;
	
	result[5][8]->inst = &CLI; result[5][8]->mem_mode = &IMP; result[0][8]->cycles = 2;
	result[5][9]->inst = &EOR; result[5][9]->mem_mode = &ABY; result[0][9]->cycles = 4;
	result[5][10]->inst = &EMP; result[5][10]->mem_mode = &EMP; result[0][10]->cycles = 2;
	result[5][11]->inst = &EMP; result[5][11]->mem_mode = &EMP; result[0][11]->cycles = 2;

	result[5][12]->inst = &EMP; result[5][12]->mem_mode = &EMP; result[0][12]->cycles = 2; 
	result[5][13]->inst = &EOR; result[5][13]->mem_mode = &ABX; result[0][13]->cycles = 4;
	result[5][14]->inst = &LSR; result[5][14]->mem_mode = &ABX; result[0][14]->cycles = 7;
	result[5][15]->inst = &EMP; result[5][15]->mem_mode = &EMP; result[0][15]->cycles = 2;

	/*5************************************************/

	/*6************************************************/
	
	result[6][0]->inst = &RTS; result[6][0]->mem_mode = &IMP; result[6][0]->cycles = 6;
	result[6][1]->inst = &ADC; result[6][1]->mem_mode = &IZX; result[6][1]->cycles = 6;
	result[6][2]->inst = &EMP; result[6][2]->mem_mode = &EMP; result[6][2]->cycles = 2;
	result[6][3]->inst = &EMP; result[6][3]->mem_mode = &EMP; result[6][3]->cycles = 2;

	result[6][4]->inst = &EMP; result[6][4]->mem_mode = &EMP; result[6][4]->cycles = 2;
	result[6][5]->inst = &ADC; result[6][5]->mem_mode = &ZPZ; result[6][5]->cycles = 3;
	result[6][6]->inst = &ROR; result[6][6]->mem_mode = &ZPZ; result[6][6]->cycles = 5;
	result[6][7]->inst = &EMP; result[6][7]->mem_mode = &EMP; result[6][7]->cycles = 2;
	
	result[6][8]->inst = &PLA; result[6][8]->mem_mode = &IMP; result[6][8]->cycles = 4;
	result[6][9]->inst = &ADC; result[6][9]->mem_mode = &IMD; result[6][9]->cycles = 2;
	result[6][10]->inst = &ROR; result[6][10]->mem_mode = &IMP; result[6][10]->cycles = 2;
	result[6][11]->inst = &EMP; result[6][11]->mem_mode = &EMP; result[6][11]->cycles = 2;

	result[6][12]->inst = &JMP; result[6][12]->mem_mode = &IND; result[6][12]->cycles = 5; 
	result[6][13]->inst = &ADC; result[6][13]->mem_mode = &ABS; result[6][13]->cycles = 4;
	result[6][14]->inst = &ROR; result[6][14]->mem_mode = &ABS; result[6][14]->cycles = 7;
	result[6][15]->inst = &EMP; result[6][15]->mem_mode = &EMP; result[6][15]->cycles = 2;

	/*6************************************************/

	/*7************************************************/
	
	result[7][0]->inst = &BVS; result[7][0]->mem_mode = &REL; result[7][0]->cycles = 2;
	result[7][1]->inst = &ADC; result[7][1]->mem_mode = &IZY; result[7][1]->cycles = 5;
	result[7][2]->inst = &EMP; result[7][2]->mem_mode = &EMP; result[7][2]->cycles = 2;
	result[7][3]->inst = &EMP; result[7][3]->mem_mode = &EMP; result[7][3]->cycles = 2;

	result[7][4]->inst = &EMP; result[7][4]->mem_mode = &EMP; result[7][4]->cycles = 2;
	result[7][5]->inst = &ADC; result[7][5]->mem_mode = &ZPX; result[7][5]->cycles = 4;
	result[7][6]->inst = &ROR; result[7][6]->mem_mode = &ZPX; result[7][6]->cycles = 6;
	result[7][7]->inst = &EMP; result[7][7]->mem_mode = &EMP; result[7][7]->cycles = 2;
	
	result[7][8]->inst = &SEI; result[7][8]->mem_mode = &IMP; result[7][8]->cycles = 2;
	result[7][9]->inst = &ADC; result[7][9]->mem_mode = &ABY; result[7][9]->cycles = 4;
	result[7][10]->inst = &EMP; result[7][10]->mem_mode = &EMP; result[7][10]->cycles = 2;
	result[7][11]->inst = &EMP; result[7][11]->mem_mode = &EMP; result[7][11]->cycles = 2;

	result[7][12]->inst = &EMP; result[7][12]->mem_mode = &EMP; result[7][12]->cycles = 2; 
	result[7][13]->inst = &ADC; result[7][13]->mem_mode = &ABX; result[7][13]->cycles = 4;
	result[7][14]->inst = &ROR; result[7][14]->mem_mode = &ABX; result[7][14]->cycles = 7;
	result[7][15]->inst = &EMP; result[7][15]->mem_mode = &EMP; result[7][15]->cycles = 2;

	/*7************************************************/

	/*8************************************************/
	
	result[8][0]->inst = &EMP; result[8][0]->mem_mode = &EMP; result[8][0]->cycles = 2;
	result[8][1]->inst = &STA; result[8][1]->mem_mode = &IZX; result[8][1]->cycles = 6;
	result[8][2]->inst = &EMP; result[8][2]->mem_mode = &EMP; result[8][2]->cycles = 2;
	result[8][3]->inst = &EMP; result[8][3]->mem_mode = &EMP; result[8][3]->cycles = 2;

	result[8][4]->inst = &STY; result[8][4]->mem_mode = &ZPZ; result[8][4]->cycles = 3;
	result[8][5]->inst = &STA; result[8][5]->mem_mode = &ZPZ; result[8][5]->cycles = 3;
	result[8][6]->inst = &STX; result[8][6]->mem_mode = &ZPZ; result[8][6]->cycles = 3;
	result[8][7]->inst = &EMP; result[8][7]->mem_mode = &EMP; result[8][7]->cycles = 2;
	
	result[8][8]->inst = &DEY; result[8][8]->mem_mode = &IMP; result[8][8]->cycles = 2;
	result[8][9]->inst = &EMP; result[8][9]->mem_mode = &EMP; result[8][9]->cycles = 2;
	result[8][10]->inst = &TXA; result[8][10]->mem_mode = &IMP; result[8][10]->cycles = 2;
	result[8][11]->inst = &EMP; result[8][11]->mem_mode = &EMP; result[8][11]->cycles = 2;

	result[8][12]->inst = &STY; result[8][12]->mem_mode = &ABS; result[8][12]->cycles = 4; 
	result[8][13]->inst = &STA; result[8][13]->mem_mode = &ABS; result[8][13]->cycles = 4;
	result[8][14]->inst = &STX; result[8][14]->mem_mode = &ABS; result[8][14]->cycles = 4;
	result[8][15]->inst = &EMP; result[8][15]->mem_mode = &EMP; result[8][15]->cycles = 2;

	/*8************************************************/

	/*9************************************************/
	
	result[9][0]->inst = &BCC; result[9][0]->mem_mode = &REL; result[9][0]->cycles = 2;
	result[9][1]->inst = &STA; result[9][1]->mem_mode = &IZY; result[9][1]->cycles = 6;
	result[9][2]->inst = &EMP; result[9][2]->mem_mode = &EMP; result[9][2]->cycles = 2;
	result[9][3]->inst = &EMP; result[9][3]->mem_mode = &EMP; result[9][3]->cycles = 2;

	result[9][4]->inst = &STY; result[9][4]->mem_mode = &ZPX; result[9][4]->cycles = 4;
	result[9][5]->inst = &STA; result[9][5]->mem_mode = &ZPX; result[9][5]->cycles = 4;
	result[9][6]->inst = &STX; result[9][6]->mem_mode = &ZPY; result[9][6]->cycles = 4;
	result[9][7]->inst = &EMP; result[9][7]->mem_mode = &EMP; result[9][7]->cycles = 2;
	
	result[9][8]->inst = &TYA; result[9][8]->mem_mode = &IMP; result[9][8]->cycles = 2;
	result[9][9]->inst = &STA; result[9][9]->mem_mode = &ABY; result[9][9]->cycles = 5;
	result[9][10]->inst = &TXS; result[9][10]->mem_mode = &IMP; result[9][10]->cycles = 2;
	result[9][11]->inst = &EMP; result[9][11]->mem_mode = &EMP; result[9][11]->cycles = 2;

	result[9][12]->inst = &EMP; result[9][12]->mem_mode = &EMP; result[9][12]->cycles = 2; 
	result[9][13]->inst = &STA; result[9][13]->mem_mode = &ABX; result[9][13]->cycles = 5;
	result[9][14]->inst = &EMP; result[9][14]->mem_mode = &EMP; result[9][14]->cycles = 2;
	result[9][15]->inst = &EMP; result[9][15]->mem_mode = &EMP; result[9][15]->cycles = 2;

	/*9************************************************/

	/*10***********************************************/
	
	result[10][0]->inst = &LDY; result[10][0]->mem_mode = &IMD; result[10][0]->cycles = 2;
	result[10][1]->inst = &LDA; result[10][1]->mem_mode = &IZX; result[10][1]->cycles = 6;
	result[10][2]->inst = &LDX; result[10][2]->mem_mode = &IMD; result[10][2]->cycles = 2;
	result[10][3]->inst = &EMP; result[10][3]->mem_mode = &EMP; result[10][3]->cycles = 2;

	result[10][4]->inst = &LDY; result[10][4]->mem_mode = &ZPZ; result[10][4]->cycles = 3;
	result[10][5]->inst = &LDA; result[10][5]->mem_mode = &ZPZ; result[10][5]->cycles = 3;
	result[10][6]->inst = &LDX; result[10][6]->mem_mode = &ZPZ; result[10][6]->cycles = 3;
	result[10][7]->inst = &EMP; result[10][7]->mem_mode = &EMP; result[10][7]->cycles = 2;
	
	result[10][8]->inst = &TAY; result[10][8]->mem_mode = &IMP; result[10][8]->cycles = 2;
	result[10][9]->inst = &LDA; result[10][9]->mem_mode = &IMD; result[10][9]->cycles = 2;
	result[10][10]->inst = &TAX; result[10][10]->mem_mode = &IMP; result[10][10]->cycles = 2;
	result[10][11]->inst = &EMP; result[10][11]->mem_mode = &EMP; result[10][11]->cycles = 2;

	result[10][12]->inst = &LDY; result[10][12]->mem_mode = &ABX; result[10][12]->cycles = 4; 
	result[10][13]->inst = &LDA; result[10][13]->mem_mode = &ABX; result[10][13]->cycles = 4;
	result[10][14]->inst = &LDX; result[10][14]->mem_mode = &ABY; result[10][14]->cycles = 4;
	result[10][15]->inst = &EMP; result[10][15]->mem_mode = &EMP; result[10][15]->cycles = 2;

	/*10***********************************************/

	/*11***********************************************/
	
	result[11][0]->inst = &BCS; result[11][0]->mem_mode = &REL; result[11][0]->cycles = 2;
	result[11][1]->inst = &LDA; result[11][1]->mem_mode = &IZY; result[11][1]->cycles = 5;
	result[11][2]->inst = &EMP; result[11][2]->mem_mode = &EMP; result[11][2]->cycles = 2;
	result[11][3]->inst = &EMP; result[11][3]->mem_mode = &EMP; result[11][3]->cycles = 2;

	result[11][4]->inst = &LDY; result[11][4]->mem_mode = &ZPX; result[11][4]->cycles = 4;
	result[11][5]->inst = &LDA; result[11][5]->mem_mode = &ZPX; result[11][5]->cycles = 4;
	result[11][6]->inst = &LDX; result[11][6]->mem_mode = &ZPY; result[11][6]->cycles = 4;
	result[11][7]->inst = &EMP; result[11][7]->mem_mode = &EMP; result[11][7]->cycles = 2;
	
	result[11][8]->inst = &CLV; result[11][8]->mem_mode = &IMP; result[11][8]->cycles = 2;
	result[11][9]->inst = &LDA; result[11][9]->mem_mode = &ABY; result[11][9]->cycles = 4;
	result[11][10]->inst = &TSX; result[11][10]->mem_mode = &IMP; result[11][10]->cycles = 2;
	result[11][11]->inst = &EMP; result[11][11]->mem_mode = &EMP; result[11][11]->cycles = 2;

	result[11][12]->inst = &LDY; result[11][12]->mem_mode = &ABX; result[11][12]->cycles = 4; 
	result[11][13]->inst = &LDA; result[11][13]->mem_mode = &ABX; result[11][13]->cycles = 4;
	result[11][14]->inst = &LDX; result[11][14]->mem_mode = &ABY; result[11][14]->cycles = 4;
	result[11][15]->inst = &EMP; result[11][15]->mem_mode = &EMP; result[11][15]->cycles = 2;

	/*11***********************************************/

	/*12***********************************************/
	
	result[12][0]->inst = &CPY; result[12][0]->mem_mode = &IMD; result[12][0]->cycles = 2;
	result[12][1]->inst = &CMP; result[12][1]->mem_mode = &IZX; result[12][1]->cycles = 6;
	result[12][2]->inst = &EMP; result[12][2]->mem_mode = &EMP; result[12][2]->cycles = 2;
	result[12][3]->inst = &EMP; result[12][3]->mem_mode = &EMP; result[12][3]->cycles = 2;

	result[12][4]->inst = &CPY; result[12][4]->mem_mode = &ZPZ; result[12][4]->cycles = 3;
	result[12][5]->inst = &CMP; result[12][5]->mem_mode = &ZPZ; result[12][5]->cycles = 3;
	result[12][6]->inst = &DEC; result[12][6]->mem_mode = &ZPZ; result[12][6]->cycles = 5;
	result[12][7]->inst = &EMP; result[12][7]->mem_mode = &EMP; result[12][7]->cycles = 2;
	
	result[12][8]->inst = &INY; result[12][8]->mem_mode = &IMP; result[12][8]->cycles = 2;
	result[12][9]->inst = &CMP; result[12][9]->mem_mode = &IMD; result[12][9]->cycles = 2;
	result[12][10]->inst = &DEX; result[12][10]->mem_mode = &IMP; result[12][10]->cycles = 2;
	result[12][11]->inst = &EMP; result[12][11]->mem_mode = &EMP; result[12][11]->cycles = 2;

	result[12][12]->inst = &CPY; result[12][12]->mem_mode = &ABS; result[12][12]->cycles = 4; 
	result[12][13]->inst = &CMP; result[12][13]->mem_mode = &ABS; result[12][13]->cycles = 4;
	result[12][14]->inst = &DEC; result[12][14]->mem_mode = &ABS; result[12][14]->cycles = 6;
	result[12][15]->inst = &EMP; result[12][15]->mem_mode = &EMP; result[12][15]->cycles = 2;

	/*12***********************************************/

	/*13***********************************************/
	
	result[13][0]->inst = &BNE; result[13][0]->mem_mode = &REL; result[13][0]->cycles = 2;
	result[13][1]->inst = &CMP; result[13][1]->mem_mode = &IZY; result[13][1]->cycles = 5;
	result[13][2]->inst = &EMP; result[13][2]->mem_mode = &EMP; result[13][2]->cycles = 2;
	result[13][3]->inst = &EMP; result[13][3]->mem_mode = &EMP; result[13][3]->cycles = 2;

	result[13][4]->inst = &EMP; result[13][4]->mem_mode = &EMP; result[13][4]->cycles = 2;
	result[13][5]->inst = &CMP; result[13][5]->mem_mode = &ZPX; result[13][5]->cycles = 4;
	result[13][6]->inst = &DEC; result[13][6]->mem_mode = &ZPX; result[13][6]->cycles = 6;
	result[13][7]->inst = &EMP; result[13][7]->mem_mode = &EMP; result[13][7]->cycles = 2;
	
	result[13][8]->inst = &CLD; result[13][8]->mem_mode = &IMP; result[13][8]->cycles = 2;
	result[13][9]->inst = &CMP; result[13][9]->mem_mode = &ABY; result[13][9]->cycles = 4;
	result[13][10]->inst = &EMP; result[13][10]->mem_mode = &EMP; result[13][10]->cycles = 2;
	result[13][11]->inst = &EMP; result[13][11]->mem_mode = &EMP; result[13][11]->cycles = 2;

	result[13][12]->inst = &EMP; result[13][12]->mem_mode = &EMP; result[13][12]->cycles = 2; 
	result[13][13]->inst = &CMP; result[13][13]->mem_mode = &ABX; result[13][13]->cycles = 4;
	result[13][14]->inst = &DEC; result[13][14]->mem_mode = &ABX; result[13][14]->cycles = 7;
	result[13][15]->inst = &EMP; result[13][15]->mem_mode = &EMP; result[13][15]->cycles = 2;

	/*13***********************************************/

	/*14***********************************************/
	
	result[14][0]->inst = &CPX; result[14][0]->mem_mode = &IMD; result[14][0]->cycles = 2;
	result[14][1]->inst = &SBC; result[14][1]->mem_mode = &IZX; result[14][1]->cycles = 6;
	result[14][2]->inst = &EMP; result[14][2]->mem_mode = &EMP; result[14][2]->cycles = 2;
	result[14][3]->inst = &EMP; result[14][3]->mem_mode = &EMP; result[14][3]->cycles = 2;

	result[14][4]->inst = &CPX; result[14][4]->mem_mode = &ZPZ; result[14][4]->cycles = 3;
	result[14][5]->inst = &SBC; result[14][5]->mem_mode = &ZPZ; result[14][5]->cycles = 3;
	result[14][6]->inst = &INC; result[14][6]->mem_mode = &ZPZ; result[14][6]->cycles = 5;
	result[14][7]->inst = &EMP; result[14][7]->mem_mode = &EMP; result[14][7]->cycles = 2;
	
	result[14][8]->inst = &INX; result[14][8]->mem_mode = &IMP; result[14][8]->cycles = 2;
	result[14][9]->inst = &SBC; result[14][9]->mem_mode = &IMD; result[14][9]->cycles = 2;
	result[14][10]->inst = &NOP; result[14][10]->mem_mode = &IMP; result[14][10]->cycles = 2;
	result[14][11]->inst = &EMP; result[14][11]->mem_mode = &EMP; result[14][11]->cycles = 2;

	result[14][12]->inst = &CPX; result[14][12]->mem_mode = &ABS; result[14][12]->cycles = 4; 
	result[14][13]->inst = &SBC; result[14][13]->mem_mode = &ABS; result[14][13]->cycles = 4;
	result[14][14]->inst = &INC; result[14][14]->mem_mode = &ABS; result[14][14]->cycles = 6;
	result[14][15]->inst = &EMP; result[14][15]->mem_mode = &EMP; result[14][15]->cycles = 2;

	/*14***********************************************/

	/*15***********************************************/
	
	result[15][0]->inst = &BEQ; result[15][0]->mem_mode = &REL; result[15][0]->cycles = 2;
	result[15][1]->inst = &SBC; result[15][1]->mem_mode = &IZY; result[15][1]->cycles = 5;
	result[15][2]->inst = &EMP; result[15][2]->mem_mode = &EMP; result[15][2]->cycles = 2;
	result[15][3]->inst = &EMP; result[15][3]->mem_mode = &EMP; result[15][3]->cycles = 2;

	result[15][4]->inst = &EMP; result[15][4]->mem_mode = &EMP; result[15][4]->cycles = 2;
	result[15][5]->inst = &SBC; result[15][5]->mem_mode = &ZPX; result[15][5]->cycles = 4;
	result[15][6]->inst = &INC; result[15][6]->mem_mode = &ZPX; result[15][6]->cycles = 6;
	result[15][7]->inst = &EMP; result[15][7]->mem_mode = &EMP; result[15][7]->cycles = 2;
	
	result[15][8]->inst = &SED; result[15][8]->mem_mode = &IMP; result[15][8]->cycles = 2;
	result[15][9]->inst = &SBC; result[15][9]->mem_mode = &ABY; result[15][9]->cycles = 4;
	result[15][10]->inst = &EMP; result[15][10]->mem_mode = &EMP; result[15][10]->cycles = 2;
	result[15][11]->inst = &EMP; result[15][11]->mem_mode = &EMP; result[15][11]->cycles = 2;

	result[15][12]->inst = &EMP; result[15][12]->mem_mode = &EMP; result[15][12]->cycles = 2; 
	result[15][13]->inst = &SBC; result[15][13]->mem_mode = &ABX; result[15][13]->cycles = 4;
	result[15][14]->inst = &INC; result[15][14]->mem_mode = &ABX; result[15][14]->cycles = 7;
	result[15][15]->inst = &EMP; result[15][15]->mem_mode = &EMP; result[15][15]->cycles = 2;

	/*15***********************************************/

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
