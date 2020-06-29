#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include <utils.h>
#include <preprocessor.h>

static void defineHandler(char *line, FILE *inputFile);
static void includeHandler(char *line, FILE *inputFile);

directive_t *directives;

uint64_t directivesSize = 0;

static void addNewDirective(uint8_t tpye, char *replaceWith, FILE *includeFile) {
    static uint64_t maxSize = 20;
    if(++directivesSize == maxSize) {
        maxSize += 20;
        directives = realloc(directives, maxSize * sizeof(directive_t));
    }

    directive_t newDirective = { tpye, replaceWith, includeFile };
    directives[directivesSize - 1] = newDirective;
}

void initMacroizedFile(char *orginalFileName) {
    directives = malloc(20 * sizeof(directive_t));

    FILE *inputFile;
    FILE *outputFile; /* macroized File */

    inputFile = fopen(orginalFileName, "r");
    outputFile = fopen("macroizedFile.txt", "w");

    char *line = malloc(50);
    while(fgets(line, 50, inputFile)) { /* first stage, runs though the file, grabs every directive, and everything else is put back in */
        if(line[0] ==  '%') {
            if(strncmp(line + 1, "define", findChar(line, ' ') - 1) == 0) {
                defineHandler(line, inputFile);        
            } else if(strncmp(line + 1, "include", findChar(line, ' ') - 1) == 0) {
                includeHandler(line, inputFile);
            }
        } else {
            fprintf(outputFile, line); 
        }
    } 
    free(line);
}

static void defineHandler(char *line, FILE *inputFile) {
    char *replaceWith = malloc(50);
    uint64_t currentSize = 0, maxSize = 50;

    char *firstLineOfMacro = malloc(50);
    if(line[strlen(line) - 1] == '\\') {
        strncpy(firstLineOfMacro, line + findChar(line, ' '), strlen(line) - findChar(line, ' ') - 2);
        strcat(replaceWith, firstLineOfMacro);
        free(firstLineOfMacro);
    } else {
        strncpy(firstLineOfMacro, line + findChar(line, ' '), strlen(line) - findChar(line, ' ') - (strlen(line) - findChar(line, '\\')));
        strcat(replaceWith, firstLineOfMacro);
        free(firstLineOfMacro);
        addNewDirective(DEFINE, replaceWith, NULL);
        return;
    }

    while(fgets(line, 50, inputFile)) {
        currentSize += strlen(line);
        if(currentSize >= maxSize) {
            maxSize += 50;
            replaceWith = realloc(replaceWith, maxSize);
        }

        char *macroInstruction = malloc(50);
        strncpy(macroInstruction, line, strlen(line) - 1);
        strcat(replaceWith, macroInstruction);
        free(macroInstruction);

        addNewDirective(DEFINE, replaceWith, NULL);

        if(line[strlen(line) - 1] != '\\') {
            break;     
        }
    }
}

static void includeHandler(char *line, FILE *inputFile) {
    char *fileName = malloc(50);
    strncpy(fileName, line + findChar(line, ' ') + 1, strlen(line) - findChar(line, ' ') - 2);

    FILE *includeInputFile = fopen(fileName, "r");
    addNewDirective(INCLUDE, NULL, includeInputFile); 

    free(fileName);
}

FILE *preprocessorInit(FILE *file) {

}
