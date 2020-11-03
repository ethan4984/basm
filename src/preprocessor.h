#ifndef PREPROCESSOR_H_
#define PREPROCESSOR_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include <utils.h>

typedef struct {
    size_t addr;
    const char *identifier;
} label_t;

typedef struct {
    size_t arg_cnt;
    char *replace, *identifier;
} macro_t;

typedef struct {
    char *output;
    size_t label_cnt;
    label_t *labels;
} pp_t;

pp_t *parse_file(char *file_name);

#endif
