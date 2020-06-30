#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "utils.h"
#include "preprocessor.h"

static void defineHandler(char *line, FILE *inputFile);
static void includeHandler(char *line, uint64_t fileLine);

directive_t *directives;

uint64_t directivesSize = 0;

static void addNewDirective(uint8_t tpye, char *replaceWith, char *identifier, FILE *includeFile) {
    static uint64_t maxSize = 20;
    if(++directivesSize == maxSize) {
        maxSize += 20;
        directives = realloc(directives, maxSize * sizeof(directive_t));
    }

    directive_t newDirective = { tpye, replaceWith, identifier, includeFile };
    directives[directivesSize - 1] = newDirective;
}

void preprocessorInit(FILE *inputFile) {
    rewind(inputFile); /* just in case */

    directives = malloc(20 * sizeof(directive_t));

    char *line = malloc(50);
    uint64_t lineCnt = 0;
    while(fgets(line, 50, inputFile) && ++lineCnt) {
        if(line[0] != '%') 
            continue;

        printf("directive detected\n");
        char *directiveType = malloc(20);
        strncpy(directiveType, line + 1, findChar(line, ' ', 1) - 1);
        directiveType[findChar(line, ' ', 1)] = '\0';
        printf("directive type %s\n", directiveType);

        if(strcmp(directiveType, "define") == 0) {
            defineHandler(line, inputFile);
        } else if(strcmp(directiveType, "include")) {
            includeHandler(line, lineCnt);
        }
    }
    free(line);
}

static void defineHandler(char *line, FILE *inputFile) {
    char numOfArgs;
    numOfArgs = line[findChar(line, ' ', 2) - 1];

    printf("Number of args %c\n", numOfArgs);

    char *identifier = malloc(20);
    strncpy(identifier, line + findChar(line, ' ', 2) + 1, findChar(line, ' ', 3) - findChar(line, ' ', 2) - 1);
    printf("identifier %s\n", identifier);

    char *replaceWith = malloc(50);
    
    if(line[strlen(line) - 2] != '\\') {
        strncpy(replaceWith, line + findChar(line, ' ', 3) + 1, strlen(line) - findChar(line, ' ', 3) - 2); // - 1 extra for \n
        printf("Replace with %s", replaceWith);
        return;
    }

    uint64_t maxSize = 50, currentSize = 0;

    while(fgets(line, 50, inputFile)) {
        currentSize += strlen(line);
        if(currentSize >= maxSize) {
            maxSize += 50;
            replaceWith = realloc(replaceWith, maxSize);
        }

        char *correctLine = malloc(50);

        if(line[strlen(line) - 2] == '\\')
            strncpy(correctLine, line, strlen(line) - 2); 
        else {
            strncpy(correctLine, line, strlen(line) - 1); 
        }

        strcat(correctLine, "\n");
        strcat(replaceWith, correctLine);
        free(correctLine);

        if(line[strlen(line) - 2] != '\\') {
            break;
        }
    }

    addNewDirective(DEFINE, identifier, replaceWith, NULL);

    //printf("replace with %s\n", replaceWith);
}

static void includeHandler(char *line, uint64_t lineNum) {
    char *includeFileContents = malloc(100);

    char fileName[30];
    strncpy(fileName, line + findChar(line, ' ', 1), strlen(line) - findChar(line, ' ', 1));

    FILE *includeFile = fopen(fileName, "r");
    
    char fileLine[50] = { 0 };
    uint64_t fileSize, maxSize = 100;
    while(fgets(fileLine, 50, includeFile)) {
        fileSize += strlen(fileLine);
        if(fileSize >= maxSize) {
            maxSize += 100;
            includeFileContents = realloc(includeFileContents, maxSize);
        }
    
        strcat(includeFileContents, fileLine);
    }
    
    addNewDirective(INCLUDE, NULL, includeFileContents, includeFile); /* remeber to close includeFile and to free inlcudeFileContents */
}
