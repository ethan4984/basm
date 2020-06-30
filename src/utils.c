#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include <utils.h>

void changeFileLine(char *newLine, FILE *inputFile, uint64_t lineNum) {
    rewind(inputFile); /* put the fp at the beginning */

    FILE *tmp = fopen("tmp.txt", "w");
    char *line = malloc(50);

    uint64_t cnt = 0; // counts lines
    while(fgets(line, 50, inputFile)) {
        if(cnt++ == lineNum) {
            fprintf(tmp, newLine);
            fputc('\n', tmp);
            continue;
        } 
        fprintf(tmp, line);
    }

    free(line);
    copyFile(inputFile, tmp, "lol.txt", "tmp.txt");
    system("rm tmp.txt");
}

void copyFile(FILE *dest, FILE *src, char *destFileName, char *srcFileName) {
    freopen(destFileName, "w", dest);
    freopen(srcFileName, "r", src);

    char *line = malloc(50);
    while(fgets(line, 50, src)) { 
        fprintf(dest, line);
    }
    free(line);

    freopen(destFileName, "r", dest);
}

int64_t findChar(char *line, char character, uint64_t num) {
    uint64_t cnt = 0;
    for(uint64_t i = 0; i < strlen(line); i++) {
        if(line[i] == character && ++cnt >= num)
            return i;
    }
    return -1;
}

uint64_t howManyOccurencesOfChar(char *string, char character) {
    uint64_t cnt = 0;
    for(uint64_t i = 0; i < strlen(string); i++) {
        if(string[i] == character) 
            cnt++;
    }

    return cnt;
}
