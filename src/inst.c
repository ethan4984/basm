#include <instruction_list.h>

inst_t *valid_inst(const char *instruction) {
    for(size_t i = 0; i < sizeof(inst) / sizeof(inst_t); i++) {
        if(strcmp(inst[i].identifier, instruction) == 0) {
            return &inst[i]; 
        }
    }
    printf("\"%s\" invalid instruction", instruction);
    exit(0);
}
