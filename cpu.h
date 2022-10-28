#include "includes.h"

void reset(struct cpu* _cpu)
{
    memset(&_cpu->f, 0, (size_t)(sizeof(struct flags)));
    memset(&_cpu->r, 0, (size_t)(sizeof(i32) * 8));
    memset(&_cpu->pr, 0, (size_t)(sizeof(i32) * 8));
    memset(&_cpu->cr, 0, (size_t)(sizeof(i32) * 8));
    _cpu->ip = 0;
}

void exec_raw(struct cpu* _cpu, const char _args[])
{
    char** args = parse_instruction(_args);
    if(args[0][0] == '#' || sizeof(args[0]) < 1)
    {
        _cpu->ip++;
        return;
    }

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
        case mul:
        {
            i32 val = 0;
            if(is_arg_register(args[2]))
                val = _cpu->r[register_by_str(args[2])];
            else
                val = atoi(args[2]);

            i32 dst = register_by_str(args[1]);
            _cpu->r[dst] *= val;
            
            _cpu->ip++;
            break;
        }
        case jmp:
        {
            _cpu->ip = line_by_label_raw(_cpu, args[1]);
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
            if(_cpu->f.cmp)
            {
                _cpu->ip = line_by_label_raw(_cpu, args[1]);
                break;
            }

            _cpu->ip++;
            break;
        }
        case jne:
        {
            if(!_cpu->f.cmp)
            {
                _cpu->ip = _cpu->ip = line_by_label_raw(_cpu, args[1]);
                break;
            }

            _cpu->ip++;
            break;
        }
        case _int:
        {
            _cpu->ip++;
            raise(5); //5 = SIGTRAP
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