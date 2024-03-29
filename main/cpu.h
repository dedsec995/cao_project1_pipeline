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

typedef struct Stages
{
	char opcode_str[128]; // The instruction
    int pc;          // Program Counter
    bool has_inst;   // Is this the turn of this Pipeline Stage
	int instAddr; // Instruction what??
	int instLen; // Current Instruction Length
	char opcode[128]; // Opcode
	char rg1[20]; // Register 1
	char rg2[20]; // Register 2
	char rg3[20]; // Register 3
	int rg1_val; // Register 1 Value
	int rg2_val; // Register 2 value
	int rg3_val; // Register 3 Value
	long buffer; // Temp value
	char or1[20]; // oprand 1
	char or2[20]; // oprand 2
	int halt_triggered; //Halted????

} Stages;

/* Model of CPU */
typedef struct CPU
{
	/* Integer register file */
	Register *regs;	// The registers
	char* filename; // File to be read
	char instructions[NO_OF_LINE][MAX_LENGTH]; // Instructions Char array
	int instructionLength; // Total Instruction Length
	int hazard; // Total structural hazard done
	float ipc; // Instructions per cycle
	int pc; // Program Counter
	int clock; // Total Cycle Completed
	int memoryPort; // Memory Port
	int halt_triggered; // Halted???

	// The Pipeline
	Stages fetch_latch; 
	Stages decode_latch;
	Stages analysis_latch;
	Stages register_read_latch;
	Stages adder_latch;
	Stages multiplier_latch;
	Stages divider_latch;
	Stages branch_latch;
	Stages memory1_latch;
	Stages memory2_latch;
	Stages writeback_latch;

} CPU;

//	    |						      |
//	    | Function Declarations Below |
//	    |						      |
//	    v						      v

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

void 
fetch_unit(CPU* cpu);

void 
decode_unit(CPU* cpu);

void 
analysis_unit(CPU* cpu);

void 
register_read_unit(CPU* cpu);

void 
adder_unit(CPU* cpu);

void 
multiplier_unit(CPU* cpu);

void 
divider_unit(CPU* cpu);

void 
branch_unit(CPU* cpu);

void 
memory1_unit(CPU* cpu);

void 
memory2_unit(CPU* cpu);

int
writeback_unit(CPU* cpu);

#endif
