#include <instruction_list.h>

inst_t *valid_inst(const char *instruction) {
    for(size_t i = 0; i < sizeof(inst) / sizeof(inst_t); i++) {
        if(strcasecmp(inst[i].identifier, instruction) == 0) {
            return &inst[i]; 
        }
    }
    return NULL;
}

int valid_prefix(inst_t *inst, const char *str) {
    uint8_t prefix = 0;

    if(strcasecmp(str, "lock") == 0) {
        prefix = P_LOCK;
    } else if(strcasecmp(str, "rep") == 0) {
        prefix = P_REP;
    }

    for(int i = 0; i < 4; i++) {
        if(inst->prefixes[i] == prefix)
            return prefix;
    }

    return 0;
}

int valid_mode(inst_t *inst, uint8_t mode) {
    for(int i = 0; i < 4; i++) {
        if(inst->modes[i] == mode)
            return 1;
    }
    return 0;
}
