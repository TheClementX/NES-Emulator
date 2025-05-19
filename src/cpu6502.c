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
void cpu_stack_push(cpu_t cpu, uint8_t data) {
	if(cpu->stkpt < 0x0100) {
		fprintf(stderr, "stack overflow"); 
		exit(EXIT_FAILURE); 
	}

	cpu->bus->memory[cpu->stkpt] = data; 
	cpu->stkpt--; 
}

//clock
void clock(cpu_t cpu) {
	if(cycles == 0) {
		iinf* instr = op_table_get(cpu->op_table, cpu->pc); 
		int e1 = (*instr->mem_mode)(); //could be bad syntax
		int e2 = (*instr->inst)(); 
		cpu->cycles = instr->cycles + e1 + e2; 
	} else {
		cpu->cycles--; 
	}
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
	uint16_t nlo = (uint16_t)cpu_read(cpu, 0xfffa); 
	uint16_t nhi = (uint16_t)cpu_read(cpu, 0xfffa + 1); 
	cpu->pc = nlo | (nhi << 8); 
	cpu->cycles = 8; 
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
	return 0; 
}

uint8_t IMD(cpu_t cpu) {
	cpu->tmp = cpu_read(cpu, cpu->pc+1, true); 
	return 0; 
}

uint8_t ABS(cpu_t cpu) {
	uint16_t lo = (uint16_t)cpu_read(cpu, cpu->pc+1, true); 
	uint16_t hi = (uint16_t)cpu_read(cpu, cpu->pc+2, true); 

	uint16_t addr = (hi << 8) | lo; 
	cpu->tmp = cpu_read(cpu, addr, true); 
	return 0; 
}

uint8_t ZPZ(cpu_t cpu) {
	uint16_t lo = (uint16_t)cpu_read(cpu, cpu->pc+1, true); 

	uint16_t addr = 0x0000 | lo; 
	cpu->tmp = cpu_read(cpu, addr, true); 
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

	return extra; 
}

uint8_t ZPX(cpu_t cpu) {
	uint16_t lo = (uint16_t)cpu_read(cpu, cpu->pc+1, true); 
	//wrap around for zp addressing
	lo = (lo + cpu->X) % 0x00ff; 

	uint16_t addr = 0x00ff & lo; 
	cpu->tmp = cpu_read(cpu, addr, true); 
	return 0; 
}

uint8_t ZPY(cpu_t cpu) {
	uint16_t lo = (uint16_t)cpu_read(cpu, cpu->pc+1, true); 
	//wrap around for zp addressing
	lo = (lo + cpu->Y) % 0x00ff; 

	uint16_t addr = 0x00ff & lo; 
	cpu->tmp = cpu_read(cpu, addr, true); 
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
	return 0; 
}

uint8_t REL(cpu_t cpu) {
	int8_t ofs = cpu_read(cpu, pc+1, true); 
	if(ofs > 127 || ofs < -128) {
		fprintf(stderr, "invalid relative addresss"); 
		exit(EXIT_FAILURE); 
	}
	cpu->tmp = ofs; 

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
	
	return 0; 
}

uint8_t IZY(cpu_t cpu) {
	uint16_t rlo = (uint16_t)cpu_read(cpu, cpu->pc+1, true); 
	rlo = (rlo + cpu->Y) % 0xff;  

	uint16_t ref = 0x00FF & rlo; 
	uint16_t lo = cpu_read(cpu, ref, true); 
	uint16_t hi = cpu_read(cpu, (ref+1 % 0xff), true); 

	uint16_t addr = (hi << 8) | lo; 
	cpu->tmp = cpu_read(cpu, addr, true); 
	
	return 0; 
}

//define instruction functions

/* instructions are read by accessing their position in the instructiontable.
 * the position holds its address mode
 * the position will dictate clock cycles and such
 */

uint8_t ADC(cpu_t cpu) {

}

uint8_t AND(cpu_t cpu); {

}

uint8_t ASL(cpu_t cpu) {

}

uint8_t BCC(cpu_t cpu) {

}

uint8_t BCS(cpu_t cpu) {

}

uint8_t BEQ(cpu_t cpu) {

}

uint8_t BIT(cpu_t cpu) {

}

uint8_t BMI(cpu_t cpu) {

}

uint8_t BNE(cpu_t cpu) {

}

uint8_t BPL(cpu_t cpu) {

}

uint8_t BRK(cpu_t cpu) {

}

uint8_t BVC(cpu_t cpu) {

}

uint8_t BVS(cpu_t cpu) {

}

uint8_t CLC(cpu_t cpu) {

}

uint8_t CLD(cpu_t cpu) {

}

uint8_t CLI(cpu_t cpu) {

}

uint8_t CLV(cpu_t cpu) {

}

uint8_t CMP(cpu_t cpu) {

}

uint8_t CPX(cpu_t cpu) {

}

uint8_t CPY(cpu_t cpu) {

}

uint8_t DEC(cpu_t cpu) {

}

uint8_t DEX(cpu_t cpu) {

}

uint8_t DEY(cpu_t cpu) {

}

uint8_t EOR(cpu_t cpu) {

}

uint8_t INC(cpu_t cpu) {

}

uint8_t INX(cpu_t cpu) {

}

uint8_t INY(cpu_t cpu) {

}

uint8_t JMP(cpu_t cpu) {

}

uint8_t JSR(cpu_t cpu) {

}

uint8_t LDA(cpu_t cpu) {

}

uint8_t LDX(cpu_t cpu) {

}

uint8_t LDY(cpu_t cpu) {

}

uint8_t LSR(cpu_t cpu) {

}

uint8_t NOP(cpu_t cpu) {

}

uint8_t ORA(cpu_t cpu) {

}

uint8_t PHA(cpu_t cpu) {

}

uint8_t PHP(cpu_t cpu) {

}

uint8_t PLA(cpu_t cpu) {

}

uint8_t PLP(cpu_t cpu) {

}

uint8_t ROL(cpu_t cpu) {

}

uint8_t ROR(cpu_t cpu) {

}

uint8_t RTI(cpu_t cpu) {

}

uint8_t RTS(cpu_t cpu) {

}

uint8_t SBC(cpu_t cpu) {

}

uint8_t SEC(cpu_t cpu) {

}

uint8_t SED(cpu_t cpu) {

}

uint8_t SEI(cpu_t cpu) {

}

uint8_t STA(cpu_t cpu) {

}

uint8_t STX(cpu_t cpu) {

}

uint8_t STY(cpu_t cpu) {

}

uint8_t TAX(cpu_t cpu) {

}

uint8_t TAY(cpu_t cpu) {

}

uint8_t TSX(cpu_t cpu) {

}

uint8_t TXA(cpu_t cpu) {

}

uint8_t TXS(cpu_t cpu) {

}

uint8_t TYA(cpu_t cpu) {

}


//the empty instruction for illegal opcodes
uint8_t EMP(cpu_t cpu) {

}

