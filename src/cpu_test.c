
/* TESTING CPU ON PROGRAMS 
	 * create a function to load a program from a commandline passed file into memory
	 * create a function to initialize the state of the cpu
	 * run the cpu clock in a loop 
	 * test the output of the code
 * TESTING CPU FUNCTIONS
	 * write test cases for each function 
	 * make sure to check clock cycles
	 * program counters 
	 * any other things that can be messed up per instruction
* */

#include "sys.h" 
#include <unistd.h>

int main(int argc, char* argv[]) {
	char* pg = argv[1]; 
	bus_t bus = sys_init(); 
	pg_load(bus, pg); 

	while(true) {
		uint8_t code = clock(bus); 
		if(code == 0xff) 
			break; 
		print_stat(bus);
		usleep(1); 
	}
	sys_clr(bus);
	return 0; 
}
