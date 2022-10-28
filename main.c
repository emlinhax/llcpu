#include "includes.h"

int main()
{
    struct cpu _cpu;
    reset(&_cpu);

    const char instructions[MAX_INSTRUCTIONS][MAX_INSTRUCTION_LEN] = 
    {
        "mov r1, 5",
        "mov r2, 5",
        "mov r3, 0",
        "mov r4, r1",

        "#mul:",
        "sub r1, 1",
        "add r3, r2",
        "cmp r1, 0",
        "jne #mul",
        "jmp #end",
        
        "#end:",
        "exit",
    };
    interpret_code_labels(&_cpu.lbls, instructions);

    while(_cpu.ip != -1)
    {
        printf("%i | %s\n",_cpu.ip, instructions[_cpu.ip]);
        exec_raw(&_cpu, instructions[_cpu.ip]);
    }
}