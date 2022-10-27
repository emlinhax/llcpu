#include "includes.h"

struct cpu
{
    i32 ip;
    struct flags f;
    i32 r[8];
};

void reset(struct cpu* _cpu)
{
    memset(&_cpu->f, 0, (size_t)(sizeof(struct flags)));
    memset(&_cpu->r, 0, (size_t)(sizeof(i32) * 8));
    _cpu->ip = 0;
}

void exec_raw(struct cpu* _cpu, const char _args[])
{
    char** args = parse_instruction(_args);
    i32 _op = op_by_str(args[0]);
    switch(_op)
    {
        case mov:
        {
            i32 val = 0;
            if(is_arg_register(args[2]))
                val = _cpu->r[register_by_str(args[2])];
            else
                val = atoi(args[2]);

            i32 dst = register_by_str(args[1]);
            _cpu->r[dst] = val;

            _cpu->ip++;
            break;
        }
        case inc:
        {
            i32 dst = register_by_str(args[1]);
            _cpu->r[dst]++;

            _cpu->ip++;
            break;
        }
        case dec:
        {
            i32 dst = register_by_str(args[1]);
            _cpu->r[dst]--;
            
            _cpu->ip++;
            break;
        }
        case add:
        {
            i32 val = 0;
            if(is_arg_register(args[2]))
                val = _cpu->r[register_by_str(args[2])];
            else
                val = atoi(args[2]);

            i32 dst = register_by_str(args[1]);
            _cpu->r[dst] += val;
            
            _cpu->ip++;
            break;
        }
        case sub:
        {
            i32 val = 0;
            if(is_arg_register(args[2]))
                val = _cpu->r[register_by_str(args[2])];
            else
                val = atoi(args[2]);

            i32 dst = register_by_str(args[1]);
            _cpu->r[dst] -= val;
            
            _cpu->ip++;
            break;
        }
        case jmp:
        {
            i32 val = atoi(args[1]);
            _cpu->ip = val;
            break;
        }
        case cmp:
        {
            //val1
            i32 val1 = 0;
            if(is_arg_register(args[1]))
                val1 = _cpu->r[register_by_str(args[1])];
            else
                val1 = atoi(args[1]);

            //val2
            i32 val2 = 0;
            if(is_arg_register(args[2]))
                val2 = _cpu->r[register_by_str(args[2])];
            else
                val2 = atoi(args[2]);

            _cpu->f.cmp = val1 == val2;
            _cpu->ip++;
            break;
        }
        case je:
        {
            i32 val = atoi(args[1]);
            if(_cpu->f.cmp)
            {
                _cpu->ip = val;
                break;
            }

            _cpu->ip++;
            break;
        }
        case jne:
        {
            i32 val = atoi(args[1]);
            if(!_cpu->f.cmp)
            {
                _cpu->ip = val;
                break;
            }

            _cpu->ip++;
            break;
        }
        case exit:
        {
            _cpu->ip = -1;
            break;
        }
        default:
        {
            _cpu->ip = -1;
            break;
        }
    }
}