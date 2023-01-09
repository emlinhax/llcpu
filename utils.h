#include "includes.h"

struct label* interpret_code_labels(struct label labels[MAX_LABELS], const char instructions[MAX_INSTRUCTIONS][MAX_INSTRUCTION_LEN])
{
    i32 lblidx = 0;
    for(i32 i = 0; i < MAX_INSTRUCTIONS; i++)
    {
        char instruction[MAX_INSTRUCTION_LEN];
        strcpy(instruction, instructions[i]);
        if(instruction[0] == '#')
        {
            char lblname[MAX_LABEL_NAME_LEN];
            strncpy(lblname, instruction+1, MAX_LABEL_NAME_LEN);

            struct label lbl = {i, lblname};
            strcpy(&lbl.name, &lblname);

            labels[lblidx] = lbl;

            lblidx++;
        }
    }
}

char** parse_instruction(const char _str[])
{
    char* str = calloc(strlen(_str)+1, sizeof(char));
    strcpy(str, _str);

    char** arr = malloc(MAX_PARAMETERS * sizeof(char*));
    char seps[]   = " ,";

    char *token;
    token = strtok(str, seps);

    i32 idx = 0;
    while( token != NULL )
    {
        arr[idx] = malloc(20 * sizeof(char));
        strcpy(arr[idx], token);

        token = strtok( NULL, seps );
        idx++;
    }

    return arr;
}

i32 line_by_label_raw(struct cpu* _cpu, const char* label)
{
    char lblname[MAX_LABEL_NAME_LEN];
    memset(lblname, 0, MAX_LABEL_NAME_LEN);

    strncpy(lblname, label+1, strlen(label));
    lblname[strlen(lblname)] = ':';

    for(int i = 0; i < MAX_LABELS; i++)
    {
        if(strcmp(lblname, _cpu->lbls[i].name) == 0)
        {
            return _cpu->lbls[i].line;
        }
    }
}

enum op op_by_str(char* str)
{
    if(strcmp(str, "mov") == 0)
        return mov;
    if(strcmp(str, "inc") == 0)
        return inc;
    if(strcmp(str, "dec") == 0)
        return dec;
    if(strcmp(str, "add") == 0)
        return add;
    if(strcmp(str, "sub") == 0)
        return sub;
    if(strcmp(str, "mul") == 0)
        return mul;
    if(strcmp(str, "jmp") == 0)
        return jmp;
    if(strcmp(str, "cmp") == 0)
        return cmp;
    if(strcmp(str, "je") == 0)
        return je;
    if(strcmp(str, "jne") == 0)
        return jne;
    if(strcmp(str, "setctl") == 0)
        return setctl;
    if(strcmp(str, "getctl") == 0)
        return getctl;
    if(strcmp(str, "int") == 0)
        return _int;
    if(strcmp(str, "exit") == 0)
        return exit;
    
    return -1;
}

i32 register_by_str(const char* arg)
{
    char tmp = arg[strlen(arg)-1];
    i32 i = tmp - '0'; //char -> int
    return i;
}

bl is_arg_register(char* arg)
{
    return arg[0] == 'r';
}

i32 val_by_arg(struct cpu* _cpu, char* arg)
{
    i32 val = 0;
    if(is_arg_register(arg))
        return _cpu->r[register_by_str(arg)];
    else
        return atoi(arg);
}

i32 write_r(struct cpu* _cpu, i32 ri, i32 val)
{
    if(ri > 8)
    {
        if(!_cpu->cr[RRAP])
            _cpu->r[ri] = val;
    }
    else
    {
        _cpu->r[ri] = val;
    }
}
