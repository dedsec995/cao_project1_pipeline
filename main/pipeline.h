#include <stdbool.h>
#include <assert.h>

int set(CPU* cpu, int instNum);
int add(CPU* cpu, int instNum);
int sub(CPU* cpu, int instNum);
int mul(CPU* cpu, int instNum);
int divi(CPU* cpu, int instNum);
int ld(CPU* cpu, int instNum);
int ret(CPU* cpu, int instNum);