#include "includes.h"

char** parse_instruction(const char _str[])
{
    char* str = calloc(strlen(_str)+1, sizeof(char));
    strcpy(str, _str);

    char** arr = malloc(5 * sizeof(char*)); //5 is max anyway so fuck you.
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
    if(strcmp(str, "jmp") == 0)
        return jmp;
    if(strcmp(str, "cmp") == 0)
        return cmp;
    if(strcmp(str, "je") == 0)
        return je;
    if(strcmp(str, "jne") == 0)
        return jne;
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