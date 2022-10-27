#include "includes.h"

int main()
{
    struct cpu _cpu;
    reset(&_cpu);

    const char instructions[][40] = 
    {
        "mov r0, 69",
        "mov r1, 69",
        "mov r2, 0",
        "mov r3, r0",

        "cmp r0, 0",
        "je 9",
        "sub r0, 1",
        "add r2, r1",
        "jmp 4",
        "exit"
    };

    while(_cpu.ip != -1)
    {
        printf("%i | %s\n",_cpu.ip, instructions[_cpu.ip]);
        exec_raw(&_cpu, instructions[_cpu.ip]);
    }

    printf("\nr2: %i\n", _cpu.r[2]);
}