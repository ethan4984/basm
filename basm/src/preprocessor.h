#pragma once

enum {
    DEFINE,
    INCLUDE,
};

typedef struct {
    uint8_t identifier;
    char *replaceWith;
    FILE *includeFile;
} directive_t;

FILE *preprocessorInit(FILE *file); /* returns macroized file */
