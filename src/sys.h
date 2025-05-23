#ifndef LOAD_H
#define LOAD_H

#include <stdlib.h> 
#include "optable.h"
#include "bus.h"
#include "cpu6502.h"

bus_t sys_init() {
	cpu_t cpu = cpu_new(); 
	op_table_t op = op_table_new(); 
	bus_t res = bus_new(cpu, op); 

	cpu_bind(cpu, res); 
	return res; 
}

uint8_t clock(bus_t bus) {
	cpu_t cpu = bus->cpu; 

	if(cpu->cycles == 0) {
		cpu->imp = false; 

		uint8_t op = cpu_read(cpu, cpu->pc, true); 
		cpu->pc++; 

		iinf* instr = op_table_get(bus->op_table, op); 
		if(instr->mem_mode == &IMP) cpu->imp = true; 
		int e1 = (*instr->mem_mode)(cpu); //could be bad syntax
		int e2 = (*instr->inst)(cpu); 

		cpu->cycles = instr->cycles + e1 + e2; 
		cpu->code = op; 
	} else {
		cpu->cycles--; 
	}
	
	return cpu->code; 
}

void pg_load(bus_t bus, char* path) {
	FILE* pg = fopen(path, "r"); 
	if(pg == NULL) {
		fprintf(stderr, "error loading program"); 
		exit(EXIT_FAILURE); 
	}
	uint8_t rlo; 
	uint8_t rhi; 
	fscanf(pg, "%hhx", &rlo); 
	fscanf(pg, "%hhx", &rhi); 
	bus_write(bus, 0xfffc, rlo); 
	bus_write(bus, 0xfffd, rhi); 
 
	uint16_t mem_loc = (((uint16_t)rhi) << 8) | ((uint16_t)rlo); 
	uint8_t tw; 
	while(fscanf(pg, "%hhx", &tw) == 1) {
		bus_write(bus, mem_loc, tw); 
		mem_loc++; 
	}
	fclose(pg); 

	bus_write(bus, mem_loc, 0xff); 
}

void print_mem(bus_t bus, uint16_t start, uint16_t end) {
	for(uint16_t i = start; i < end; i++)
		printf("%hhx\n", bus_read(bus, i, true));
}

//cli utility to cleanly print cpu state without graphics library 
void print_stat(bus_t bus) {
	cpu_t cpu = bus->cpu; 
	system("clear"); 	
	printf("------------------------------------------------------------\n\n"); //50 long
	printf("STAT: |C Z I D B U V N| : vector: %x\n", cpu->stat); 
	printf("      |%b %b %b %b %b %b %b %b|\n\n", 
			flag_get(C, cpu),
			flag_get(Z, cpu),
			flag_get(I, cpu),
			flag_get(D, cpu),
			flag_get(B, cpu),
			flag_get(U, cpu),
			flag_get(V, cpu),
			flag_get(N, cpu)
	); 

	printf("INTERNAL VARS: cycles %d | tmp %x | code %x | cur_mem %x\n\n", 
			cpu->cycles, 
			cpu->tmp, 
			cpu->code,
			cpu->cur_mem
	); 
	printf("REGISTERS: accum %x | X %x | Y %x | pc %x | stkpt %x\n\n",
			cpu->accum, 
			cpu->X,
			cpu->Y,
			cpu->pc,
			cpu->stkpt
	);
	printf("------------------------------------------------------------\n"); //50 long
}

void sys_clr(bus_t bus) {
	op_table_free(bus->op_table); 
	cpu_free(bus->cpu); 
	bus_free(bus); 
}

#endif
