#pragma once

enum {
    DEFINE,
    INCLUDE,
};

typedef struct {
    uint8_t type;
    char *identifier;
    char *replaceWith;
    FILE *includeFile;
} directive_t;

void preprocessorInit(FILE *file); /* returns macroized file */
