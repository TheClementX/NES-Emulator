#include "bus.h"

typedef struct bus bus; 

bus* bus_new(cpu_t cpu, op_table_t op) {
	bus* result = malloc(sizeof(bus)); 

	//temp ram for cpu tests
	result->cpu = cpu; 
	result->op_table = op; 
	result->memory = calloc(0xffff, sizeof(uint8_t)); 
	return result; 
}

uint8_t bus_read(bus* bus, uint16_t addr, bool read_only) {
	if(0x0000 <= addr && addr <= 0xffff) 
		return bus->memory[addr]; 	

	return 0x00; 
}

void bus_write(bus* bus, uint16_t addr, uint8_t data) {
	if(0x0000 <= addr && addr <= 0xffff) 
		bus->memory[addr] = data; 
}

void bus_free(bus* bus) {
	free(bus->memory); 
	free(bus); 
}
