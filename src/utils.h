#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *append_str(char *dest, char *src);

int find_char(char *src, char character);

int find_char_file(FILE *fp, char *ret, char c);

char *get_scope(FILE *fp, char *line);

void replace_char(char *src, char c, char replace);

void remove_char(char *src, char c);

#endif 
