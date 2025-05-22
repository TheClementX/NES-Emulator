#include "cpu6502.h" 

typedef struct cpu cpu; 

cpu* cpu_new() {	
	cpu* result = malloc(sizeof(cpu)); 
	//finish this function		
	result->accum = 0; 
	result->X = 0; 
	result->Y = 0; 
	result->pc = 0; 
	result->stkpt = 0x01ff; 
	result->stat = 0; 
	
	result->bus = NULL; 
	result->op_table = op_table_new(); 

	result->cycles = 0; 
	result->tmp = 0; 
	result->code = 0; 
	result->cur_mem = 0; 

	return result; 
}

void cpu_free(cpu_t cpu) {
	op_table_free(cpu->op_table); 
	free(cpu); 
}

void cpu_bind(cpu_ cpu, bus_t bus) {
	if(bus->cpu != cpu) {
		fprintf(stderr, "cpu does not belong to bus"); 
		exit(EXIT_FAILURE); 

	cpu->bus = bus; 
}

//flag functions
void flag_tog(FLAGS f, cpu_t cpu) {
	uint8_t s = cpu->stat; 
	s ^= f; 
	cpu->stat = s; 
}

void flag_set(FLAGS f, cpu_t cpu) {
	cpu->stat |= f; 
}

void flag_clr(FLAGS f, cpu_t cpu) {
	cpu->stat = cpu->stat & (~f);
}

bool flag_get(FLAGS f, cpu_t cpu) {
	if((cpu->stat & f) == 0) return false; 
	return true; 
}

//read and write functions
uint8_t cpu_read(cpu_t cpu, uint16_t addr, bool read_only) {
	return bus_read(cpu->bus, addr); 
}

void cpu_write(cpu_t cpu, uint16_t addr, uint8_t data) {
	bus_write(cpu->bus, addr, data); 
}

//hardware functions: functions that would be called by hardware

//stack push 
//0x0100 <-- 0x01ff : grows left to right or up in memory 
void cpu_stack_push(cpu_t cpu, uint8_t data) {
	if(cpu->stkpt < 0x0100) {
		fprintf(stderr, "stack overflow"); 
		exit(EXIT_FAILURE); 
	}

	cpu_write(cpu, cpu->stkpt, data); 
	cpu->stkpt--; 
}

void cpu_stack_pop(cpu_t cpu) {
	if(cpu->stkpt == 0x01ff) {
		fprintf(stderr, "pop from an empty stack"); 
		exit(EXIT_FAILURE); 
	}

	cpu->sktpt++; 
	uint8_t result = cpu_read(cpu, cpu->stkpt); 
	cpu_write(cpu, cpu->stkpt, 0x00); 
	return result; 
}

//clock
void clock(cpu_t cpu) {
	if(cycles == 0) {
		uint8_t op = cpu_read(cpu, cpu->pc, true); 
		cpu->pc++; 
		iinf* instr = op_table_get(cpu->op_table, op); 
		int e1 = (*instr->mem_mode)(); //could be bad syntax
		int e2 = (*instr->inst)(); 
		cpu->cycles = instr->cycles + e1 + e2; 
		cpu->code = op; 
	} else {
		cpu->cycles--; 
	}
	return cpu->code; 
}

//maskable interrupt
void IRQ(cput_t cpu) {
	FLAGS flag = I; 
	if(!flag_get(flag, cpu)) {
		uint8_t hi = (uint8_t)((cpu->stkpt & 0xff00) >> 4); 
		uint8_t lo = (uint8_t)((cpu->stkpt & 0x00ff) >> 4); 

		cpu_stack_push(cpu, hi); 
		cpu_stack_push(cpu, lo); 

		//could be wrong integer logic 
		cpu_stack_push(cpu, cpu->stat | (1<<4)); 
		uint16_t nlo = (uint16_t)cpu_read(cpu, 0xfffa); 
		uint16_t nhi = (uint16_t)cpu_read(cpu, 0xfffa + 1); 
		cpu->pc = nlo | (nhi << 8); 
		cpu->cycles = 7; 
		cpu->code = 0; 
		cpu->cur_mem = 0; 
	}
}

//non maskable interrupt
void NMI(cpu_t cpu) {
	uint8_t hi = (uint8_t)((cpu->stkpt & 0xff00) >> 4); 
	uint8_t lo = (uint8_t)((cpu->stkpt & 0x00ff) >> 4); 

	cpu_stack_push(cpu, hi); 
	cpu_stack_push(cpu, lo); 

	//could be wrong integer logic 
	cpu_stack_push(cpu, cpu->stat | (1<<4)); 
	uint16_t nlo = (uint16_t)cpu_read(cpu, 0xfffe); 
	uint16_t nhi = (uint16_t)cpu_read(cpu, 0xfffe + 1); 
	cpu->pc = nlo | (nhi << 8); 
	cpu->cycles = 8; 
	cpu->code = 0; 
	cpu->cur_mem = 0; 
}

//reset
void RES(cpu_t cpu) {
	uint16_t nlo = (uint16_t)cpu_read(cpu, 0xfffc); 
	uint16_t nhi = (uint16_t)cpu_read(cpu, 0xfffc + 1); 
	cpu->pc = nlo | (nhi << 8); 

	cpu->accum = 0; 
	cpu->X = 0; 
	cpu->Y = 0; 
	cpu->stkpt = 0x01ff; 
	cpu->stat = 0; 
	cpu->tmp = 0; 
	cpu->code = 0; 
	cpu->cur_mem = 0; 


	cpu->cycles=8; 
}

/*  define address mode functions
	these functions take in the cpu and return the memory accessed
	they each follow a different specific protocol to return mem
	each instruction is associated with a specific address mode
	address modes are stored with funcs in the instruction table

	these functions return the required clock adjustment
*/

//read information is put into the cpu tmp var
//pc will only be incremented in the instruction function

uint8_t IMP(cpu_t cpu) {
	cpu->tmp = 0x00; 
	cpu->mem = 0x00; 
	return 0; 
}

uint8_t IMD(cpu_t cpu) {
	cpu->tmp = cpu_read(cpu, cpu->pc+1, true); 
	cpu->mem = cpu->pc+1; 
	cpu->pc++; 
	return 0; 
}

uint8_t ABS(cpu_t cpu) {
	uint16_t lo = (uint16_t)cpu_read(cpu, cpu->pc+1, true); 
	uint16_t hi = (uint16_t)cpu_read(cpu, cpu->pc+2, true); 

	uint16_t addr = (hi << 8) | lo; 
	cpu->tmp = cpu_read(cpu, addr, true); 
	cpu->cur_mem = addr; 
	cpu->pc += 2; 
	return 0; 
}

uint8_t ZPZ(cpu_t cpu) {
	uint16_t lo = (uint16_t)cpu_read(cpu, cpu->pc+1, true); 

	uint16_t addr = 0x0000 | lo; 
	cpu->tmp = cpu_read(cpu, addr, true); 
	cpu->cur_mem = addr; 
	cpu->pc++; 
	return 0; 
}

//+1 cycle if page boundary crossed 
uint8_t ABX(cpu_t cpu) {
	uint8_t extra = 0; 

	uint16_t lo = (uint16_t)cpu_read(cpu, cpu->pc+1, true); 
	uint16_t hi = (uint16_t)cpu_read(cpu, cpu->pc+2, true); 

	lo += cpu->X; 
	if(lo > 0x00ff) extra = 1; 

	uint16_t addr = (hi << 8) + lo; 
	cpu->tmp = cpu_read(cpu, addr, true); 
	cpu->cur_mem = addr; 

	cpu->pc += 2; 
	return extra; 
}

//+1 cycle if page boundary crossed 
uint8_t ABY(cpu_t cpu) {
	uint8_t extra = 0; 

	uint16_t lo = (uint16_t)cpu_read(cpu, cpu->pc+1, true); 
	uint16_t hi = (uint16_t)cpu_read(cpu, cpu->pc+2, true); 

	lo += cpu->Y; 
	if(lo > 0x00ff) extra = 1; 

	uint16_t addr = (hi << 8) + lo; 
	cpu->tmp = cpu_read(cpu, addr, true); 
	cpu->cur_mem = addr; 

	cpu->pc += 2; 
	return extra; 
}

uint8_t ZPX(cpu_t cpu) {
	uint16_t lo = (uint16_t)cpu_read(cpu, cpu->pc+1, true); 
	//wrap around for zp addressing
	lo = (lo + cpu->X) % 0x00ff; 

	uint16_t addr = 0x00ff & lo; 
	cpu->tmp = cpu_read(cpu, addr, true); 
	cpu->cur_mem = addr; 
	cpu->pc++; 
	return 0; 
}

uint8_t ZPY(cpu_t cpu) {
	uint16_t lo = (uint16_t)cpu_read(cpu, cpu->pc+1, true); 
	//wrap around for zp addressing
	lo = (lo + cpu->Y) % 0x00ff; 

	uint16_t addr = 0x00ff & lo; 
	cpu->tmp = cpu_read(cpu, addr, true); 
	cpu->cur_mem = addr; 
	cpu->pc++; 
	return 0; 
}

//simulate low byte overflow wrap around bug
uint8_t IND(cpu_t cpu) {
	uint16_t rlo = (uint16_t)cpu_read(cpu, cpu->pc+1, true); 
	uint16_t rhi = (uint16_t)cpu_read(cpu, cpu->pc+2, true); 
	uint16_t ref = (rhi << 8) | rlo; 
	
	uint16_t lo = (uint16_t)cpu_read(cpu, ref, true); 
	uint16_t hi = (uint16_t)cpu_read(cpu, ref+1, true); 
	//bug code
	if(rlo == 0x00ff) 
		hi = (uint16_t)cpu_read(cpu, (ref | 0xff00), true); 
	uint16_t addr = (hi << 8) | lo; 

	cpu->tmp = cpu_read(cpu, addr, true); 
	cpu->cur_mem = addr; 
	cpu->pc += 2; 
	return 0; 
}

uint8_t REL(cpu_t cpu) {
	int8_t ofs = cpu_read(cpu, pc+1, true); 
	if(ofs > 127 || ofs < -128) {
		fprintf(stderr, "invalid relative addresss"); 
		exit(EXIT_FAILURE); 
	}
	cpu->tmp = ofs; 
	cpu->cur_mem = pc+1; 

	cpu->pc++; 
	return 0; 
}

uint8_t IZX(cpu_t cpu) {
	uint16_t rlo = (uint16_t)cpu_read(cpu, cpu->pc+1, true); 
	rlo = (rlo + cpu->X) % 0xff;  

	uint16_t ref = 0x00FF & rlo; 
	uint16_t lo = cpu_read(cpu, ref, true); 
	uint16_t hi = cpu_read(cpu, (ref+1 % 0xff), true); 

	uint16_t addr = (hi << 8) | lo; 
	cpu->tmp = cpu_read(cpu, addr, true); 
	cpu->cur_mem = addr; 
	
	cpu->pc++; 
	return 0; 
}

//has potential to change page and add extra clock cycle
uint8_t IZY(cpu_t cpu) {
	uint16_t rlo = (uint16_t)cpu_read(cpu, cpu->pc+1, true); 

	uint16_t ref = 0x00FF & rlo; 
	uint16_t lo = cpu_read(cpu, ref, true); 
	lo = lo + cpu->Y; 
	uint8_t extra = 0; 
	if(lo > 0x00ff) extra = 1;  

	//accounts for overflow could be incorrect
	uint16_t hi = cpu_read(cpu, (ref+1 % 0xff), true); 

	uint16_t addr = (hi << 8) + lo; 
	cpu->tmp = cpu_read(cpu, addr, true); 
	cpu->cur_mem = addr; 
	
	cpu->pc++; 
	return extra; 
}

//define instruction functions

/* instructions are read by accessing their position in the instructiontable.
 * the position holds its address mode
 * the position will dictate clock cycles and such
 */

//overflow formula accum ^ result & ~(acuum ^ data)
//A+M+C
uint8_t ADC(cpu_t cpu) {
	uint8_t car =  flag_get(C, cpu) ? 1 : 0; 
	uint16_t res = cpu->accum + cpu->tmp + car; 	

	flag_clr(C, cpu); 
	if(res > 0xff) flag_set(C, cpu)
	if((res & 0x80) > 0) flag_set(N, cpu); 
	if(res == 0) flag_set(Z, cpu); 

	//overflow
	uint8_t as = cpu->accum & 0x80;
	uint8_t ds = cpu->tmp & 0x80;  
	uint8_t rs = (uint8_t)(res & 0x0080);   

	if(( (as ^ ar) & ~(as ^ ds) ) > 0) flag_set(V, cpu); 

	cpu->accum = res; 
	//for extra clock cycle
	pc
	return 0; 
}

uint8_t AND(cpu_t cpu); {
	uint8_t res = cpu->tmp & cpu->accum; 
	if(res == 0) flag_set(Z, cpu); 
	if(0x80 & res > 0) flag_set(N, cpu); 

	cpu->accum = res; 
	return 0; 
}

uint8_t ASL(cpu_t cpu) {
	if(cpu->tmp & 0x80 > 0) flag_set(C, cpu); 
	uint8_t res = cpu->temp << 1; 
	if(res == 0) flag_set(Z, cpu); 
	if(res & 0x80 > 0) flag_set(N, cpu); 

	uint8_t r = cpu->code >> 4; 
	uint8_t c = cpu->code & 0x0f; 

	if(cpu->op_table[r][c]->mem_mode == &IMP) {
		cpu->accum = res; 
	} else {
		cpu_write(cpu, cpu->cur_mem, res); 
	}
	return 0; 
}

uint8_t BCC(cpu_t cpu) {
	if(!flag_get(C, cpu)) {
		//offset is signed but this depends on interpretation
		//not +-
		uint16_t addr = cpu->pc + cpu->tmp; 
		cpu->pc = addr; 
		if((0xff00 & cpu->pc) != (addr & 0x0ff))
			return 2; 
		else 
			return 1; 
	}
	return 0; 
}

uint8_t BCS(cpu_t cpu) {
	if(flag_get(C, cpu)) {
		uint16_t addr = cpu->pc + cpu->tmp; 
		cpu->pc = addr; 
		if((0xff00 & cpu->pc) != (addr & 0x0ff))
			return 2; 
		else 
			return 1; 
	}
	return 0; 
}

uint8_t BEQ(cpu_t cpu) {
	if(flag_get(Z, cpu)) {
		uint16_t addr = cpu->pc + cpu->tmp; 
		cpu->pc = addr; 
		if((0xff00 & cpu->pc) != (addr & 0x0ff))
			return 2; 
		else 
			return 1; 
	}
	return 0; 
}

uint8_t BIT(cpu_t cpu) {
	if(cpu->tmp & 0x80 > 0) flag_set(N, cpu); 
	if(cpu->tmp & 0x40 > 0) flag_set(V, cpu); 
	if(cpu->tmp & cpu->accum == 0) flag_set(Z, cpu); 
	return 0; 
}

uint8_t BMI(cpu_t cpu) {
	if(flag_get(N, cpu)) {
		uint16_t addr = cpu->pc + cpu->tmp; 
		cpu->pc = addr; 
		if((0xff00 & cpu->pc) != (addr & 0x0ff))
			return 2; 
		else 
			return 1; 
	}
	return 0; 

}

uint8_t BNE(cpu_t cpu) {
	if(!flag_get(Z, cpu)) {
		uint16_t addr = cpu->pc + cpu->tmp; 
		cpu->pc = addr; 
		if((0xff00 & cpu->pc) != (addr & 0x0ff))
			return 2; 
		else 
			return 1; 
	}
	return 0; 
}

uint8_t BPL(cpu_t cpu) {
	if(!flag_get(N, cpu)) {
		uint16_t addr = cpu->pc + cpu->tmp; 
		cpu->pc = addr; 
		if((0xff00 & cpu->pc) != (addr & 0x0ff))
			return 2; 
		else 
			return 1; 
	}
	return 0; 
}

//this could be wrong
uint8_t BRK(cpu_t cpu) {
	pc++; 

	flag_set(I, cpu); 
	flag_set(B, cpu); 
	
	uint8_t plo = (uint8_t)(cpu->pc & 0x00ff); 
	uint8_t phi = (uint8_t)(cpu->pc >> 8); 
	cpu_stack_push(cpu, phi); 
	cpu_stack_push(cpu, plo); 
	cpu_stack_push(cpu, cpu->stat); 
	

	uint16_t rlo = (uint16_t)cpu_read(cpu, 0xfffe);
	uint16_t rhi = (uint16_t)cpu_read(cpu, 0xffff);  
	cpu->pc = (rhi << 8) | rlo; 
	return 0; 
}

uint8_t BVC(cpu_t cpu) {
	if(!flag_get(V, cpu)) {
		uint16_t addr = cpu->pc + cpu->tmp; 
		cpu->pc = addr; 
		if((0xff00 & cpu->pc) != (addr & 0x0ff))
			return 2; 
		else 
			return 1; 
	}
	return 0; 
}

uint8_t BVS(cpu_t cpu) {
	if(flag_get(V, cpu)) {
		uint16_t addr = cpu->pc + cpu->tmp; 
		cpu->pc = addr; 
		if((0xff00 & cpu->pc) != (addr & 0x0ff))
			return 2; 
		else 
			return 1; 
	}
	return 0; 
}

uint8_t CLC(cpu_t cpu) {
	flag_clr(C, cpu); 
	return 0; 
}

uint8_t CLD(cpu_t cpu) {
	flag_clr(D, cpu); 
	return 0; 
}

uint8_t CLI(cpu_t cpu) {
	flag_clr(I, cpu); 
	return 0; 
}

uint8_t CLV(cpu_t cpu) {
	flag_clr(V, cpu); 
	return 0; 
}

uint8_t CMP(cpu_t cpu) {
	uint16_t cmp = cpu->accum - cpu->tmp; 

	if(cmp == 0) flag_set(Z, cpu); 
	if(0x0080 & cmp > 0) flag_set(N, cpu); 
	if(0xFF00 & cmp > 0) flag_set(C, cpu); 
	return 0; 
}

uint8_t CPX(cpu_t cpu) {
	uint16_t cmp = cpu->X - cpu->tmp; 

	if(cmp == 0) flag_set(Z, cpu); 
	if(0x0080 & cmp > 0) flag_set(N, cpu); 
	if(0xFF00 & cmp > 0) flag_set(C, cpu); 
	return 0; 
}

uint8_t CPY(cpu_t cpu) {
	uint16_t cmp = cpu->Y - cpu->tmp; 

	if(cmp == 0) flag_set(Z, cpu); 
	if(0x0080 & cmp > 0) flag_set(N, cpu); 
	if(0xFF00 & cmp > 0) flag_set(C, cpu); 
	return 0; 
}

uint8_t DEC(cpu_t cpu) {
	uint8_t res = cpu->tmp--; 
	if(res == 0) flag_set(Z, cpu); 
	if(res & 0x80 > 0) flag_set(Z, cpu); 
	cpu_write(cpu, cpu->cur_mem, res); 
	return 0; 
}

uint8_t DEX(cpu_t cpu) {
	uint8_t res = cpu->X--; 
	if(res == 0) flag_set(Z, cpu); 
	if(res & 0x80 > 0) flag_set(Z, cpu); 
	return 0; 
}

uint8_t DEY(cpu_t cpu) {
	uint8_t res = cpu->Y--; 
	if(res == 0) flag_set(Z, cpu); 
	if(res & 0x80 > 0) flag_set(Z, cpu); 
	return 0; 
}

uint8_t EOR(cpu_t cpu) {
	uint8_t res = cpu->tmp ^ cpu->accum; 
	if(res == 0) flag_set(Z, cpu); 
	if(res & 0x80 > 0) flag_set(Z, cpu); 
	cpu->accum = res; 
	return 0; 
}

uint8_t INC(cpu_t cpu) {
	uint8_t res = cpu->tmp++; 
	if(res == 0) flag_set(Z, cpu); 
	if(res & 0x80 > 0) flag_set(Z, cpu); 
	cpu_write(cpu, cpu->cur_mem, res); 	
	return 0; 
}

uint8_t INX(cpu_t cpu) {
	uint8_t res = cpu->X++; 
	if(res == 0) flag_set(Z, cpu); 
	if(res & 0x80 > 0) flag_set(Z, cpu); 
	return 0; 
}

uint8_t INY(cpu_t cpu) {
	uint8_t res = cpu->Y++; 
	if(res == 0) flag_set(Z, cpu); 
	if(res & 0x80 > 0) flag_set(Z, cpu); 
	return 0; 
}

uint8_t JMP(cpu_t cpu) {
	cpu->pc = cpu->tmp; 
	return 0; 
}

//tricky instruction could cause problems with pc push 
uint8_t JSR(cpu_t cpu) {
	cpu->pc--; 
	uint8_t plo = (uint8_t)(0x00ff & cpu->pc); 
	uint8_t phi = (uint8_t)(cpu->pc >> 8); 

	cpu_stack_push(cpu, phi);  	
	cpu_stack_push(cpu, plo);  	
	
	cpu->pc = cpu->tmp; 
	return 0; 
}

uint8_t LDA(cpu_t cpu) {
	cpu->accum = cpu->tmp 
	if(cpu->accum == 0) flag_set(Z, cpu); 
	if(cpu->accum & 0x80 > 0) flag_set(N, cpu); 
	return 0; 
}

uint8_t LDX(cpu_t cpu) {
	cpu->X = cpu->tmp 
	if(cpu->X == 0) flag_set(Z, cpu); 
	if(cpu->X & 0x80 > 0) flag_set(N, cpu); 
	return 0; 
}

uint8_t LDY(cpu_t cpu) {
	cpu->Y = cpu->tmp 
	if(cpu->Y == 0) flag_set(Z, cpu); 
	if(cpu->Y & 0x80 > 0) flag_set(N, cpu); 
	return 0; 
}

uint8_t LSR(cpu_t cpu) {
	if(cpu->tmp & 0x01 > 0) flag_set(C, cpu); 
	flag_clr(N, cpu); 
	uint8_t res = cpu->tmp >> 1; 
	if(res == 0) flag_set(Z, cpu); 
	
	uint8_t r = cpu->code >> 4; 
	uint8_t c = cpu->code & 0x0f; 

	if(cpu->op_table[r][c]->mem_mode == &IMP)
		cpu->accum = res; 
	else 
		cpu _write(cpu, cpu->cur_mem, res); 

	return 0; 
}

uint8_t NOP(cpu_t cpu) {
	return 0; 
}

uint8_t ORA(cpu_t cpu) {
	uint8_t res = cpu->accum | cpu->tmp; 
	if(res == 0) flag_set(Z, cpu); 
	if(res & 0x80 > 0) flag_set(N, cpu); 
	cpu->accum = res; 
	return 0; 
}

uint8_t PHA(cpu_t cpu) {
	cpu_stack_push(cpu, cpu->accum); 
	return 0; 
}

uint8_t PHP(cpu_t cpu) {
	flag_set(B, cpu); 
	flag_set(U, cpu); 
	cpu_stack_push(cpu, cpu->stat); 
	flag_clr(B, cpu); 
	flag_clr(U, cpu); 
	return 0; 
}

uint8_t PLA(cpu_t cpu) {
	cpu->accum = cpu_stack_pop(cpu); 
	return 0; 	
}

uint8_t PLP(cpu_t cpu) {
	cpu->stat = cpu_stack_pop(cpu); 
	return 0; 
}

uint8_t ROL(cpu_t cpu) {
	uint8_t r = cpu->code >> 4; 
	uint8_t c = cpu->code & 0x0f;

	if(cpu->op_table[r][c] == &IMP) {
		if(cpu->accum & 0x80 > 0) flag_set(C, cpu); 
		cpu->accum = cpu->accum << 1; 
		if(flag_get(C, cpu)) cpu->accum |= 0x01; 
		else cpu->accum &= 0xfe; 
	} else {
		uint8_t res = cpu->tmp; 
		if(res & 0x80 > 0) flag_set(C, cpu); 
		res = res << 1; 
		if(flag_get(C, cpu)) res |= 0x01; 
		else res &= 0xfe; 
		cpu_write(cpu, cpu->cur_mem, res); 
	}
	return 0; 
}

uint8_t ROR(cpu_t cpu) {
	uint8_t r = cpu->code >> 4; 
	uint8_t c = cpu->code & 0x0f;

	if(cpu->op_table[r][c] == &IMP) {
		if(cpu->accum & 0x01 > 0) flag_set(C, cpu); 
		cpu->accum = cpu->accum >> 1; 
		if(flag_get(C, cpu)) cpu->accum |= 0x80; 
	} else {
		uint8_t res = cpu->tmp; 
		if(res & 0x01 > 0) flag_set(C, cpu); 
		res = res >> 1; 
		if(flag_get(C, cpu)) res |= 0x80; 
		cpu_write(cpu, cpu->cur_mem, res); 
	}
	return 0; 
}

uint8_t RTI(cpu_t cpu) {
	cpu->stat = cpu_stack_pop(cpu); 
	uint16_t plo = cpu_stack_pop(cpu); 
	uint16_t phi = cpu_stack_pop(cpu); 
	cpu->pc = (phi << 8) | plo; 
	return 0; 
}

uint8_t RTS(cpu_t cpu) {
	uint16_t plo = cpu_stack_pop(cpu); 
	uint16_t phi = cpu_stack_pop(cpu); 
	cpu->pc = (phi << 8) | plo; 
	cpu->pc++; 
	return 0; 
}

//A-M-(~C)
//invert data to use add formula
uint8_t SBC(cpu_t cpu) {
	uint8_t car =  flag_get(C, cpu) ? 1 : 0; 
	//+1 for twos complement
	uint8_t dat = ~(cpu->tmp) + 1;  
	uint16_t res = cpu->accum + dat + car; 	

	flag_clr(C, cpu); 
	if(res > 0xff) flag_set(C, cpu)
	if((res & 0x80) > 0) flag_set(N, cpu); 
	if(res == 0) flag_set(Z, cpu); 

	//overflow
	uint8_t as = cpu->accum & 0x80;
	uint8_t ds = dat & 0x80;  
	uint8_t rs = (uint8_t)(res & 0x0080); 

	if(( (as ^ ar) & ~(as ^ ds) ) > 0) flag_set(V, cpu); 

	cpu->accum = res; 
	//for extra clock cycle
	return 0; 
}

uint8_t SEC(cpu_t cpu) {
	flag_set(C, cpu); 
	return 0; 
}

uint8_t SED(cpu_t cpu) {
	flag_set(D, cpu); 
	return 0; 
}

uint8_t SEI(cpu_t cpu) {
	flag_set(I, cpu); 
	return 0; 
}

uint8_t STA(cpu_t cpu) {
	cpu_stack_push(cpu, cpu->accum); 
	return 0; 
}

uint8_t STX(cpu_t cpu) {
	cpu_stack_push(cpu, cpu->X); 
	return 0; 
}

uint8_t STY(cpu_t cpu) {
	cpu_stack_push(cpu, cpu->Y); 
	return 0; 
}

uint8_t TAX(cpu_t cpu) {
	cpu->X = cpu->accum; 
	return 0; 
}

uint8_t TAY(cpu_t cpu) {
	cpu->Y = cpu->accum; 
}

uint8_t TSX(cpu_t cpu) {
	cpu->X = cpu->stkpt; 
	return 0; 
}

uint8_t TXA(cpu_t cpu) {
	cpu->accum = cpu->X; 
	return 0; 
}

uint8_t TXS(cpu_t cpu) {
	cpu->stkpt = cpu->X; 
	return 0; 
}

uint8_t TYA(cpu_t cpu) {
	cpu->accum = cpu->Y; 
	return 0; 
}


//the empty instruction for illegal opcodes
//throws an error 
uint8_t EMP(cpu_t cpu) {
	fprint(stderr, "invalid opcode"); 
	exit(EXIT_FAILURE); 
}

