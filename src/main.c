#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <instructionFileParse.h>
#include <preprocessor.h>

int main(int argc, char *argv[]) {
    if(argc <= 2) {
        printf("Fatal Error: Poor formating\n\nYou have to run this like like\n\n./basm inputFile.XXX outputFile.XXX\n");
        return -1;
    }
    
    FILE *inputFile = fopen(argv[1], "r");
    if(inputFile == NULL) {
        printf("%s does not exist\n", argv[1]);
        return -1;
    }

    parseInstructionFile();
    preprocessorInit(inputFile);
}
