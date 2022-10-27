#pragma once
#include "stdio.h"
#include "string.h"

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
    jmp,
    cmp,
    je,
    jne,
    exit
};

struct flags
{
    bl cmp;
};

#include "utils.h"
#include "cpu.h"