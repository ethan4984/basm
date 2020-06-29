#include <stdio.h>
#include <string.h>
#include <stdint.h>

int64_t findChar(char *line, char character) {
    for(uint64_t i = 0; i < strlen(line); i++) {
        if(line[i] == character)
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
