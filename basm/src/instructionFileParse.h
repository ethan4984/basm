#pragma once

#include <stdint.h>

typedef struct {
    char *identifier; 
    uint8_t *encoding;
    uint8_t encodingSize;
} instructionIMM_t;

typedef struct {
    char *identifier;
    uint8_t *encoding;
    uint8_t encodingSize;
} instructionRR_t;

typedef struct {
    char *identifier;
    uint8_t *encodingBytes;
} modrmList_t;

typedef struct {
    char *identifier;
    uint8_t *encoding;
    uint8_t encodingSize;
} oneForOne_t;

enum {
    MODRM_ENCODING,
    IMM_INSTRUCTION_ENCODING,
    RR_INSTRUCTION_ENCODING,
    ONE_FOR_ONE
};

instructionIMM_t *grabIMMinstructions(void);

instructionRR_t *grabRRinstructions(void);

oneForOne_t *grabOneForOneInstructions(void);

modrmList_t *grabMODRMlist(void);

void parseInstructionFile(void);
