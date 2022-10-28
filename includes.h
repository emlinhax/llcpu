#pragma once
#include "stdio.h"
#include "string.h"

#define MAX_INSTRUCTIONS 50
#define MAX_LABELS 40
#define MAX_LABEL_NAME_LEN 30
#define MAX_PARAMETERS 5
#define MAX_INSTRUCTION_LEN 50

typedef __uint32_t i32;
typedef __uint64_t i64;
typedef short bl;
typedef char byte;

enum op
{
    mov,
    inc,
    dec,
    add,
    sub,
    mul,
    jmp,
    cmp,
    je,
    jne,
    _int,
    exit
};

struct flags
{
    bl cmp;
};

struct label
{
    i32 line;
    char name[MAX_LABEL_NAME_LEN];
};

enum ctlreg_mask {
    RRAP,       //Protected Register Access Protection
    HI,         //Handle Interrupts
    unused3,
    unused4,
    unused5,
    unused6,
    unused7,
    unused8
};

struct cpu
{
    i32 ip;
    struct flags f;
    i32 cr[8];  //control register (cpu's ruleset)
    i32 r[8];   //user registers
    i32 pr[8];  //protected registers (reserved)

    struct label lbls[MAX_LABELS];
};

#include "utils.h"
#include "cpu.h"
