#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <instructionFileParse.h>
#include <preprocessor.h>

typedef struct {
    uint8_t mdorm;
    uint8_t imm[8];
    uint64_t correspondingInstruction; /* instructions[correspondindInstruction].XXXXXXX */
} tokenizedInstruction;

void parseInputFile(FILE *inputFile) { // post preprocessor operation
    char *line = malloc(50);
    while(fgets(line, 50, inputFile)) {
         
    }
    free(line);
}
