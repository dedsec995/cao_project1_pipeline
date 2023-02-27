
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cpu.h"

#define REG_COUNT 128
#define MAXY_LENGHT 512

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
    cpu->pc = 0;
    cpu->memoryPort = 1;
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
 * This function read the file and add the data to string array 
 */
void
load_the_instructions(CPU *cpu){
    FILE *filePointer = fopen(cpu->filename, "r");
    int county = 0;
    if (filePointer == NULL)
    {
        printf("Error: could not open file %s", cpu->filename);
    }
    char buffer[MAXY_LENGHT];
    while (fgets(buffer, MAXY_LENGHT, filePointer)){
        strcpy(cpu->instructions[county],buffer);
        county++;
    }
    cpu->instructionLength = county ;
    fclose(filePointer);
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

int
load_the_memory(int num){
    char *filename = "../programs/memory_map.txt"; 
    FILE *filePointer = fopen(filename, "r");
    int county = 0;
    int n;
    if (filePointer == NULL)
    {
        printf("Error: could not open file %s", filename);
    }
    while (fscanf(filePointer, " %d", &n) == 1) {
        if((num-1) == county){
            fclose(filePointer);
            return n;
        }
        county++;
    }
    fclose(filePointer);
    return (-1);
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
    cpu->hazard = 0;
    simulate(cpu);
    // print_registers(cpu);
    cpu->ipc = (double)cpu->instructionLength/(double)cpu->clock;
    printf("Stalled cycles due to structural hazard: %d\n", cpu->hazard);
    printf("Total execution cycles: %d\n",cpu->clock);
    printf("Total instruction simulated: %d\n", cpu->instructionLength);
    printf("IPC: %6f\n",cpu->ipc);

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
    printf("================================");
    printf("\nClock Cycle #: %d\n",cpu->clock);
    printf("--------------------------------\n");
    int last_inst = 0;
    cpu->fetch_latch.halt_triggered = 0;
    for(;;){
        if(writeback_unit(cpu)){
            break;
        }
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
        printf("\n================================");
        printf("\nClock Cycle #: %d\n",cpu->clock);
        printf("--------------------------------\n");
    }
    //TODO Loop Or recursion?
    // Create Struct or F!!!
    // printf("Hahaha");
}

int writeback_unit(CPU* cpu){
    if(cpu->writeback_latch.has_inst == 1 && cpu->writeback_latch.halt_triggered==0){
        printf("WB             : %s",cpu->instructions[cpu->writeback_latch.pc]);
        // cpu->writeback_latch.has_inst = 0;
        if(strcmp(cpu->writeback_latch.opcode,"ret") == 10){
            // printf("Last Instruction for Writeback");
            cpu->writeback_latch.has_inst = 0;
            return(1);
        }
        else if (strcmp(cpu->writeback_latch.opcode,"set")==0){
            cpu->regs[atoi(cpu->writeback_latch.rg1+1)].value = atoi(cpu->writeback_latch.or1+1);
            return(0);
        }
        else if (strcmp(cpu->writeback_latch.opcode,"ld")==0){
            return(0);
        }
        // printf("%d\n",cpu->writeback_latch.buffer);
        cpu->regs[atoi(cpu->writeback_latch.rg1+1)].value = cpu->writeback_latch.buffer;
        return(0);
    }
    else if (cpu->writeback_latch.halt_triggered==1){
        cpu->writeback_latch.halt_triggered = 0;
        return(0);
    }
}

void memory2_unit(CPU* cpu){
    if(cpu->memory2_latch.has_inst == 1 && cpu->memory2_latch.halt_triggered==0){
        // printf("%d",cpu->memory2_latch.buffer);
        // printf("%s",cpu->memory2_latch.opcode);
        printf("Mem2           : %s",cpu->instructions[cpu->memory2_latch.pc]);
        // if (cpu->halt_triggered == 1){
        //     cpu->fetch_latch.has_inst = 1;
        //     cpu->halt_triggered == 0;
        //     cpu->memoryPort = 1;
        // }
        // printf("%d",strcmp(cpu->memory2_latch.opcode,"ld"));
        if(strcmp(cpu->memory2_latch.opcode,"ret") == 10){
            cpu->writeback_latch = cpu->memory2_latch;
            // printf("Last Instruction for Memory2");
            cpu->memory2_latch.has_inst = 0;
            return;
        }
        else if (strcmp(cpu->memory2_latch.opcode,"ld") == 0){
            cpu->hazard+=1;
            cpu->memoryPort = 0;
            cpu->fetch_latch.halt_triggered = 1;
            printf("ld called, Halting Fetch\n");
        }
        cpu->writeback_latch = cpu->memory2_latch;
    }
    else if (cpu->memory2_latch.halt_triggered==1){
        cpu->writeback_latch = cpu->memory2_latch;
    }
}

void memory1_unit(CPU* cpu){
    if(cpu->memory1_latch.has_inst == 1 && cpu->memory1_latch.halt_triggered==0){
        // printf("%d",cpu->memory1_latch.buffer);
        printf("Mem1           : %s",cpu->instructions[cpu->memory1_latch.pc]);
        if(strcmp(cpu->memory1_latch.opcode,"ret") == 10){
            cpu->memory2_latch = cpu->memory1_latch;
            // printf("Last Instruction for Memory1");
            cpu->memory1_latch.has_inst = 0;
            return;
        }
        cpu->memory2_latch = cpu->memory1_latch;
    }
    else if (cpu->memory1_latch.halt_triggered==1){
        cpu->memory2_latch = cpu->memory1_latch;
    }
}

void branch_unit(CPU* cpu){
    if(cpu->branch_latch.has_inst == 1 && cpu->branch_latch.halt_triggered==0){
        // printf("%d",cpu->branch_latch.buffer);
        printf("BR             : %s",cpu->instructions[cpu->branch_latch.pc]);
        if(strcmp(cpu->branch_latch.opcode,"ret") == 10){
            cpu->memory1_latch = cpu->branch_latch;
            // printf("Last Instruction for Branch");
            cpu->branch_latch.has_inst = 0;
            return;
        }
        cpu->memory1_latch = cpu->branch_latch;
    }
    else if (cpu->branch_latch.halt_triggered==1){
        cpu->memory1_latch = cpu->branch_latch;
    }
}

void divider_unit(CPU* cpu){
    if(cpu->divider_latch.has_inst == 1 && cpu->divider_latch.halt_triggered==0){
        // printf("%d",cpu->divider_latch.buffer);
        printf("DIV            : %s",cpu->instructions[cpu->divider_latch.pc]);
        if(strcmp(cpu->divider_latch.opcode,"ret") == 10){
            cpu->branch_latch = cpu->divider_latch;
            // printf("Last Instruction for Divider");
            cpu->divider_latch.has_inst = 0;
            return;
        }
        else if(strcmp(cpu->divider_latch.opcode,"div") == 0){
            //TODO Write Divide Logic
            cpu->divider_latch.buffer = atoi(cpu->divider_latch.or1+1) / atoi(cpu->divider_latch.or2+1);
            // printf("div the numbers\n");
            // printf("%d",cpu->divider_latch.buffer);
        }
        cpu->branch_latch = cpu->divider_latch;
    }
    else if (cpu->divider_latch.halt_triggered==1){
        cpu->branch_latch = cpu->divider_latch;
    }
}

void multiplier_unit(CPU* cpu){
    if(cpu->multiplier_latch.has_inst == 1 && cpu->multiplier_latch.halt_triggered==0){
        printf("MUL            : %s",cpu->instructions[cpu->multiplier_latch.pc]);
        if(strcmp(cpu->multiplier_latch.opcode,"ret") == 10){
            cpu->divider_latch = cpu->multiplier_latch;
            // printf("Last Instruction for Multipler");
            cpu->multiplier_latch.has_inst = 0;
            return;
        }
        else if(strcmp(cpu->multiplier_latch.opcode,"mul") == 0){
            //TODO Write Multiplication Logic
            cpu->multiplier_latch.buffer = atoi(cpu->multiplier_latch.or1+1) * atoi(cpu->multiplier_latch.or2+1);
            // printf("mul the numbers\n");
            // printf("%d",cpu->multiplier_latch.buffer);
        }
        cpu->divider_latch = cpu->multiplier_latch;
    }
    else if (cpu->multiplier_latch.halt_triggered==1){
        cpu->divider_latch = cpu->multiplier_latch;
    }
}

void adder_unit(CPU* cpu){
    if(cpu->adder_latch.has_inst == 1 && cpu->adder_latch.halt_triggered==0){
        printf("ADD            : %s",cpu->instructions[cpu->adder_latch.pc]);
        if(strcmp(cpu->adder_latch.opcode,"ret") == 10){
            cpu->multiplier_latch = cpu->adder_latch;
            // printf("Last Instruction for Adder");
            cpu->adder_latch.has_inst = 0;
            return;
        }
        else if(strcmp(cpu->adder_latch.opcode,"add") == 0){
            //TODO Write Addition Logic
            // printf("Add the numbers\n");
            cpu->adder_latch.buffer = atoi(cpu->adder_latch.or1+1) + atoi(cpu->adder_latch.or2+1);
            // printf("%d",cpu->adder_latch.buffer);
        }
        else if(strcmp(cpu->adder_latch.opcode,"sub") == 0){
            //TODO Write Subtraction Logic
            cpu->adder_latch.buffer = atoi(cpu->adder_latch.or1+1) - atoi(cpu->adder_latch.or2+1);
            // printf("%d",cpu->adder_latch.buffer);
            // printf("Sub the numbers\n");
        }
        cpu->multiplier_latch = cpu->adder_latch;
    }
    else if (cpu->adder_latch.halt_triggered==1){
        cpu->multiplier_latch = cpu->adder_latch;
    }
}

void register_read_unit(CPU* cpu){
    if(cpu->register_read_latch.has_inst == 1 && cpu->register_read_latch.halt_triggered==0){
        printf("RR             : %s",cpu->instructions[cpu->register_read_latch.pc]);
        if(strcmp(cpu->register_read_latch.opcode,"ret") == 10){
            cpu->adder_latch = cpu->register_read_latch;
            // printf("Last Instruction for Register read");
            cpu->register_read_latch.has_inst = 0;
            return;
        }
        else if(strcmp(cpu->register_read_latch.opcode,"ld") == 0){
            cpu->adder_latch = cpu->register_read_latch;
            // Read memory map
            return;
        }
        cpu->register_read_latch.rg1_val = cpu->regs[atoi(cpu->register_read_latch.rg1+1)].value;
        cpu->adder_latch = cpu->register_read_latch;
        // printf("Reg: %s Value: %d",cpu->register_read_latch.rg1,cpu->regs[atoi(cpu->register_read_latch.rg1+1)].value); 
        // printf("%s",cpu->register_read_latch.rg1+1);
    }
    else if(cpu->register_read_latch.halt_triggered==1){
        cpu->adder_latch = cpu->register_read_latch;
    }
}

void analysis_unit(CPU* cpu){
    if(cpu->analysis_latch.has_inst == 1 && cpu->analysis_latch.halt_triggered==0){
        // printf("Inside analysis_unit");
        printf("IA             : %s",cpu->instructions[cpu->analysis_latch.pc]);
        if(strcmp(cpu->analysis_latch.opcode,"ret") == 10){
            cpu->register_read_latch=cpu->analysis_latch;
            // printf("Last Instruction for analysis");
            cpu->analysis_latch.has_inst = 0;
            return;
        }
        cpu->register_read_latch=cpu->analysis_latch;
    }
    else if (cpu->analysis_latch.halt_triggered==1){
        cpu->register_read_latch=cpu->analysis_latch;
    }
}

void decode_unit(CPU* cpu){
    // printf("%d:%d",cpu->decode_latch.has_inst,cpu->decode_latch.halt_triggered);
    if(cpu->decode_latch.has_inst == 1 && cpu->decode_latch.halt_triggered==0){
        printf("ID             : %s",cpu->instructions[cpu->decode_latch.pc]);
        if(strcmp(cpu->decode_latch.opcode,"ret") == 10){
            cpu->analysis_latch = cpu->decode_latch;
            // printf("Last Instruction for decode");
            cpu->decode_latch.has_inst = 0;
            return;
        }
        cpu->analysis_latch = cpu->decode_latch;
    }
    else if(cpu->decode_latch.halt_triggered==1){
        cpu->analysis_latch = cpu->decode_latch;
    }
}

void fetch_unit(CPU* cpu){
    if(cpu->fetch_latch.has_inst == 1 && cpu->fetch_latch.halt_triggered == 0){
        cpu->fetch_latch.pc = cpu->pc;
        cpu->pc++;
        printf("IF             : %s",cpu->instructions[cpu->fetch_latch.pc]);
        char str1[128];
        strcpy(str1,cpu->instructions[cpu->fetch_latch.pc]);

        //-----------------------------Dynamic Spliting---------------------------------------------
        char **token= NULL;
        char *p = str1;
        char *sepa=" ";
        size_t  arr_len = 0,q;
        for (;;)
        {
            p += strspn(p, sepa);
            if (!(q = strcspn(p, sepa)))
                    break;
            if (q)
            {
                    token = realloc(token, (arr_len+1) * sizeof(char *));
                    token[arr_len] = malloc(q+1);
                    strncpy(token[arr_len], p, q);
                    token[arr_len][q] = 0;
                    arr_len++;
                    p += q;
            }
        }
        token = realloc(token, (arr_len+1) * sizeof(char *));
        token[arr_len] = NULL;
        cpu->fetch_latch.instLen;
        //-------------------------------------Dynamic Spliting------------------------------------------
        if(arr_len == 5 ){
            cpu->fetch_latch.instAddr = (atoi)(token[0]);
            strcpy(cpu->fetch_latch.opcode,token[1]);
            strcpy(cpu->fetch_latch.rg1,token[2]);
            strcpy(cpu->fetch_latch.or1,token[3]);
            strcpy(cpu->fetch_latch.or2,token[4]);
        }
        else if(arr_len == 4){
           cpu->fetch_latch.instAddr = (atoi)(token[0]);
            strcpy(cpu->fetch_latch.opcode,token[1]);
            strcpy(cpu->fetch_latch.rg1,token[2]);
            strcpy(cpu->fetch_latch.or1,token[3]); 
        }
        else if(arr_len == 3){
           cpu->fetch_latch.instAddr = (atoi)(token[0]);
            strcpy(cpu->fetch_latch.opcode,token[1]);
            strcpy(cpu->fetch_latch.rg1,token[2]); 
        }
        else if(arr_len == 2){
           cpu->fetch_latch.instAddr = (atoi)(token[0]);
            strcpy(cpu->fetch_latch.opcode,token[1]);
        }
        if(strcmp(cpu->fetch_latch.opcode,"ret") == 10){
            // printf("Last Instruction for fetch");
            cpu->decode_latch = cpu->fetch_latch;
            cpu->fetch_latch.has_inst = 0;
            return;
        }
        cpu->fetch_latch.halt_triggered = 0;
        cpu->decode_latch = cpu->fetch_latch;
        // printf("%d",cpu->fetch_latch.halt_triggered);
        // printf("%d",cpu->decode_latch.halt_triggered);
        printf("given latch to decode");
    }
    else if(cpu->fetch_latch.halt_triggered == 1){
        printf("IF             : Halted due to MemoryPort\n");
        // cpu->fetch_latch.has_inst = 0;
        cpu->decode_latch = cpu->fetch_latch;
        cpu->fetch_latch.halt_triggered = 0;
        // printf("fetch inst: %d",cpu->fetch_latch.has_inst);
    }
}

