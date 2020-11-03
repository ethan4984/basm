#ifndef INST_H_
#define INST_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

enum {
    M_NOX86_64,
    M_386, 
    P_LOCK,
    P_REP,
    OP_EN_VOID
};

typedef struct {
    char *identifier; 
    char *format;
    uint8_t operand_encoding;
    char *encoding;
    uint8_t modes[4];
    uint8_t prefixes[4];
} inst_t;

inst_t *valid_inst(const char *inst);
int valid_mode(inst_t *inst, uint8_t mode);
int valid_prefix(inst_t *inst, const char *str);

#endif
