#ifndef _CPU_H_
#define _CPU_H_
#include <stdbool.h>
#include <assert.h>

#define MAX_LENGTH 1024
#define NO_OF_LINE 256

typedef struct Register
{
    int value;          // contains register value
    bool is_writing;    // indicate that the register is current being written
	                    // True: register is not ready
						// False: register is ready
} Register;

/* Model of CPU */
typedef struct CPU
{
	/* Integer register file */
	Register *regs;
	char* filename;
	char instructions[NO_OF_LINE][MAX_LENGTH];
	int instructionLength;
	int hazard;
	int cycles;
	float ipc;
	
} CPU;

CPU*
CPU_init();

Register*
create_registers(int size);

int
CPU_run(CPU* cpu);

void
CPU_stop(CPU* cpu);

void 
simulate(CPU* cpu);

#endif
