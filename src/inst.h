#ifndef INST_H_
#define INST_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

enum {
    T_8086,
    T_NOLONG,
    T_386,
    T_286,
    T_PROT,
    T_SM,
    T_SB,
    T_ND,
    T_LOCK,
    T_LONG,
    T_X86_64
};

enum {
    NOTHING,
    MR,
    RM,
    MI,
    I
};

typedef struct {
    char *identifier;
    char format[8][8];
    uint8_t type;
    char encoding[8][16]; 
    uint8_t modes[8];
} inst_t;

inst_t *valid_inst(const char *inst);
bool valid_mode(inst_t *inst, uint8_t mode);

#endif
