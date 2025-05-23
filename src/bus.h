#ifndef BUS_H
#define BUS_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//everything for bus is prefixed with bus_

// The bus consists of a struct of all the parts in the system
// The bus contains functions for reading and write from memory
// These functions will be used to read from other components on the bus

struct cpu; 
typedef struct cpu* cpu_t; 
struct op_table; 
typedef struct op_table* op_table_t;

struct bus {
	cpu_t cpu; 
	op_table_t op_table; 
	uint8_t* memory; 
	//insert other parts bellow when built
}; 
typedef struct bus* bus_t; 

bus_t bus_new(cpu_t cpu, op_table_t op); 

uint8_t bus_read(bus_t bus, uint16_t addr, bool read_only); 

void bus_write(bus_t bus, uint16_t addr, uint8_t data); 

void bus_free(bus_t bus); 

#endif
