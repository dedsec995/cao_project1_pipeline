
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cpu.h"

#define REG_COUNT 128
#define MAX_LENGTH 1024

 char* programFile;

CPU*
CPU_init(char* filename)
{
    CPU* cpu = malloc(sizeof(*cpu));
    if(!filename){
        printf("Error!! Missing filename");
        exit(0);
    }
    if (!cpu) {
        return NULL;
    }

    /* Create register files */
    cpu->regs= create_registers(REG_COUNT);
    cpu->filename = filename;
    cpu->fetch_latch.has_inst = 1;
    cpu->clock = 1;
    cpu->pc = 0000;
    return cpu;
}

/*
 * This function de-allocates CPU cpu.
 */
void
CPU_stop(CPU* cpu)
{
    free(cpu);
}

/*
 *This function read the file and add the data to string array 
 */
void
load_the_instructions(CPU *cpu){

    FILE *fp = fopen(cpu->filename, "r");
    int county = 0;
    int i;
    if (fp == NULL)
    {
        printf("Error: could not open file %s", cpu->filename);
    }

    // reading line by line, max 1024 bytes
    // const unsigned MAX_LENGTH = 1024;
    char buffer[MAX_LENGTH];

    while (fgets(buffer, MAX_LENGTH, fp)){
        // printf("%s", buffer);
        strcpy(cpu->instructions[county],buffer);
        // printf("The String array: %s\n",a[0]);
        // printf("The String array: %s\n",a[1]);
        county++;
    }
    cpu->instructionLength = county ;

    // close the file
    fclose(fp);
}

/*
 * This function prints the content of the registers.
 */
void
print_registers(CPU *cpu){
    
    printf("================================\n");
    printf("--------------------------------\n");
    for (int reg=0; reg<REG_COUNT; reg++) {
        printf("REG[%2d]   |   Value=%d  \n",reg,cpu->regs[reg].value);
        printf("--------------------------------\n");
    }
    printf("================================\n\n");
}

/*
 * This function prints the instrucitons.
 */
void
print_instructions(CPU *cpu){
    
    printf("================================\n");
    printf("--------------------------------\n");
    for (int i=0; i<=cpu->instructionLength; i++) {
        printf("Instructions: %s",cpu->instructions[i]);
        printf("--------------------------------\n");
    }
    printf("================================\n\n");
}


/*
 *  CPU CPU simulation loop
 */
int
CPU_run(CPU* cpu)
{
    load_the_instructions(cpu);
    // print_registers(cpu);
    // print_instructions(cpu);
    //TODO Create more Functions
    simulate(cpu);

    printf("Stalled cycles due to structural hazard: %d\n", cpu->hazard);
    printf("Total execution cycles: %d\n",cpu->clock);
    printf("Total instruction simulated: %d\n", cpu->instructionLength);
    printf("IPC: %f\n",cpu->ipc);

    return 0;
}

Register*
create_registers(int size){
    Register* regs = malloc(sizeof(*regs) * size);
    if (!regs) {
        return NULL;
    }
    for (int i=0; i<size; i++){
        regs[i].value = 0;
        regs[i].is_writing = false;
    }
    return regs;
}


/*
*The Main Pipeline Implementation
*/ 
void simulate(CPU* cpu){
    // for (int i=0; i<=cpu->instructionLength; i++) {
    //     printf("Instructions: %s",cpu->instructions[i]);
    //     printf("--------------------------------\n");
    // } 
    for(int i =1;i<cpu->instructionLength;i++){
        writeback_unit(cpu);
        memory2_unit(cpu);
        memory1_unit(cpu); 
        branch_unit(cpu); 
        divider_unit(cpu); 
        multiplier_unit(cpu);
        adder_unit(cpu); 
        register_read_unit(cpu); 
        analysis_unit(cpu); 
        decode_unit(cpu); 
        fetch_unit(cpu); 
        cpu->clock++;
        printf("\nClock Cycle: %d\n",cpu->clock);
        printf("--------------------------------\n");
    }
    //TODO Loop Or recursion?
    // Create Struct or F!!!
    // printf("Hahaha");
}

int writeback_unit(CPU* cpu){
    if(cpu->writeback_latch.has_inst == 1){
        printf("Executing Writeback\n");
        cpu->writeback_latch.has_inst = 0;
        return(0);
    }
    else{
        return(0);
    }
}

void memory2_unit(CPU* cpu){
    if(cpu->memory2_latch.has_inst == 1){
        printf("Executing Memory2\n");
        cpu->writeback_latch.has_inst = 1;
    }
}

void memory1_unit(CPU* cpu){
    if(cpu->memory1_latch.has_inst == 1){
        printf("Executing Memory1\n");
        cpu->memory2_latch.has_inst = 1;
    }
}

void branch_unit(CPU* cpu){
    if(cpu->branch_latch.has_inst == 1){
        printf("Executing branch\n");
        cpu->memory1_latch.has_inst = 1;
    }
}

void divider_unit(CPU* cpu){
    if(cpu->divider_latch.has_inst == 1){
        printf("Executing divider\n");
        cpu->branch_latch.has_inst = 1;
    }
}

void multiplier_unit(CPU* cpu){
    if(cpu->multiplier_latch.has_inst == 1){
        printf("Executing multipler\n");
        cpu->divider_latch.has_inst = 1;
    }
}

void adder_unit(CPU* cpu){
    if(cpu->adder_latch.has_inst == 1){
        printf("Executing adder\n");
        cpu->multiplier_latch.has_inst = 1;
    }
}

void register_read_unit(CPU* cpu){
    if(cpu->register_read_latch.has_inst == 1){
        printf("Executing register read\n");
        cpu->adder_latch.has_inst = 1;
    }
}

void analysis_unit(CPU* cpu){
    if(cpu->analysis_latch.has_inst == 1){
        printf("Executing analysis\n");
        cpu->register_read_latch.has_inst = 1;
    }
}

void decode_unit(CPU* cpu){
    if(cpu->decode_latch.has_inst == 1){
        printf("Executing decode\n");
        cpu->analysis_latch.has_inst = 1;
    }
}

void fetch_unit(CPU* cpu){
    if(cpu->fetch_latch.has_inst == 1){
        printf("Executing fetch\n");
        cpu->decode_latch.has_inst = 1;
    }
}

