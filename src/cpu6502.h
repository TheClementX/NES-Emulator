#ifndef CPU_H
#define CPU_H

#include "lib/dep.h"
#include "bus.h"

//A link to the reference manual for the 6502 cpu
//https://www.masswerk.at/6502/6502_instruction_set.html#modes

//6502 function type definition  
typedef uint8_t cpu_func(void); 

struct cpu {
	//registers 
	uint8_t accum; //accumulator
	uint8_t X; 
	uint8_t Y; 
	uint16_t pc; //program counter
	//stack is on pg1 from 0x0100 - 0x01ff
	uint8_t stkpt; //stack pointer 
	uint8_t stat; //status / flags

	bus_t bus; 	
	op_table_t op_table; 

	uint8_t cycles; //to store cycle count 
	uint8_t tmp; //to store mem values
	uint8_t code; //current opcode value
	uint16_t cur_mem; //location of current memory lookup 
}; 
typedef struct cpu* cpu_t; 

//flag functions
enum FLAGS {
	C = (1 << 0), //carry flag 
	Z = (1 << 1), //zero flag 
	I = (1 << 2), //interrupt inhibit flag 
	D = (1 << 3), //decimal flag 
	B = (1 << 4), //break flag 
	U = (1 << 5), //unused 
	V = (1 << 6), //overflow flag 
	N = (1 << 7), //negative flag 
}; 
typedef enum FLAGS FLAGS; 

//new free bind functions
cpu_t cpu_new(); 
void cpu_free(cpu_t cpu); 
void cpu_bind(cpu_t cpu, bus_t bus);

//flag functions
void flag_tog(FLAGS f, cpu_t cpu); 
void flag_set(FLAGS f, cpu_t cpu); 
void flag_clr(FLAGS f, cpu_t cpu); 
bool flag_get(FLAGS f, cpu_t cpu); 

//read and write functions
uint8_t cpu_read(cpu_t cpu, uint16_t addr, bool read_only); 
void cpu_write(cpu_t cpu, uint16_t addr, uint8_t data); 

//hardware functions: functions that would be called by hardware

//stack push
void cpu_stack_push(cpu_t cpu, uint8_t data); 

//clock
void clock(cpu_t cpu); 

//maskable interrupt
void IRQ(cput_t cpu); 

//non maskable interrupt
void NMI(cpu_t cpu); 

//reset
void RES(cpu_t cpu); 

/*  define address mode functions
	these functions take in the cpu and return the memory accessed
	they each follow a different specific protocol to return mem
	each instruction is associated with a specific address mode
	address modes are stored with funcs in the instruction table

	these functions return the required clock adjustment
*/


//read information is put into the cpu tmp var
//pc will only be incremented in the instruction function

//Implied				Immediate
uint8_t IMP(cpu_t cpu); uint8_t IMD(cpu_t cpu); 
//Absolute				Zero-Page
uint8_t ABS(cpu_t cpu); uint8_t ZPZ(cpu_t cpu); 
//Indexed AbsoluteX		Indexed Absolute Y
uint8_t ABX(cpu_t cpu); uint8_t ABY(cpu_t cpu); 
//Zero-PageX			Zero-PageY
uint8_t ZPX(cpu_t cpu); uint8_t ZPY(cpu_t cpu); 
//Indirect				Relative
uint8_t IND(cpu_t cpu); uint8_t REL(cpu_t cpu); 
//Indirect Zero-PageX	Indirect Zero-PageY	
uint8_t IZX(cpu_t cpu); uint8_t IZY(cpu_t cpu); 

//define instruction functions

/* instructions are read by accessing their position in the instructiontable.
 * the position holds its address mode
 * the position will dictate clock cycles and such
 */

uint8_t ADC(cpu_t cpu); uint8_t AND(cpu_t cpu); uint8_t ASL(cpu_t cpu); uint8_t BCC(cpu_t cpu); 
uint8_t BCS(cpu_t cpu); uint8_t BEQ(cpu_t cpu); uint8_t BIT(cpu_t cpu); uint8_t BMI(cpu_t cpu); 
uint8_t BNE(cpu_t cpu); uint8_t BPL(cpu_t cpu); uint8_t BRK(cpu_t cpu); uint8_t BVC(cpu_t cpu); 
uint8_t BVS(cpu_t cpu); uint8_t CLC(cpu_t cpu); uint8_t CLD(cpu_t cpu); uint8_t CLI(cpu_t cpu); 
uint8_t CLV(cpu_t cpu); uint8_t CMP(cpu_t cpu); uint8_t CPX(cpu_t cpu); uint8_t CPY(cpu_t cpu); 
uint8_t DEC(cpu_t cpu); uint8_t DEX(cpu_t cpu); uint8_t DEY(cpu_t cpu); uint8_t EOR(cpu_t cpu); 
uint8_t INC(cpu_t cpu); uint8_t INX(cpu_t cpu); uint8_t INY(cpu_t cpu); uint8_t JMP(cpu_t cpu); 

uint8_t JSR(cpu_t cpu); uint8_t LDA(cpu_t cpu); uint8_t LDX(cpu_t cpu); uint8_t LDY(cpu_t cpu); 
uint8_t LSR(cpu_t cpu); uint8_t NOP(cpu_t cpu); uint8_t ORA(cpu_t cpu); uint8_t PHA(cpu_t cpu); 
uint8_t PHP(cpu_t cpu); uint8_t PLA(cpu_t cpu); uint8_t PLP(cpu_t cpu); uint8_t ROL(cpu_t cpu); 
uint8_t ROR(cpu_t cpu); uint8_t RTI(cpu_t cpu); uint8_t RTS(cpu_t cpu); uint8_t SBC(cpu_t cpu); 
uint8_t SEC(cpu_t cpu); uint8_t SED(cpu_t cpu); uint8_t SEI(cpu_t cpu); uint8_t STA(cpu_t cpu); 
uint8_t STX(cpu_t cpu); uint8_t STY(cpu_t cpu); uint8_t TAX(cpu_t cpu); uint8_t TAY(cpu_t cpu); 
uint8_t TSX(cpu_t cpu); uint8_t TXA(cpu_t cpu); uint8_t TXS(cpu_t cpu); uint8_t TYA(cpu_t cpu); 

//the empty instruction for illegal opcodes
uint8_t EMP(cpu_t cpu); 

#endif 
