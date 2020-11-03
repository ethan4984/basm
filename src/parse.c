#include <parse.h>

void parse(pp_t *out) { 
    char *inst, *save = out->output;
    while((inst = strtok_r(save, ";", &save))) {
        uint8_t encoding[15], cnt = 0;

        char *word, *save1 = inst;
        word = strtok_r(save1, " ", &save1);
    
        inst_t *instruction = valid_inst(word); 
        uint8_t prefix = 0;

        if(!instruction) {
            if(strcasecmp(word, "lock") == 0) {
                prefix = P_LOCK;
                encoding[cnt++] = 0xF0;
            } else if(strcasecmp(word, "rep") == 0) {
                prefix = P_REP;
            }
        }

        if(prefix) { 
            word = strtok_r(save1, " ", &save1);
            instruction = valid_inst(word); 
        }

        if(instruction == NULL) {
            printf(" nrgrngrjUnknown instruction %s\n", word); 
            exit(0);
        }

        if(instruction->operand_encoding == OP_EN_VOID) {
            char *encode, *save3 = instruction->encoding;
            while((encode = strtok_r(save3, " ", &save3))) {
                encoding[cnt++] = strtol(encode, NULL, 16);
            }
        } else {

        }
        
        for(int i = 0; i < cnt; i++) {
            printf("%x ", encoding[i]);
        }
        printf("\n"); 
    }
}
