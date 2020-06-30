#pragma once

int64_t findChar(char *line, char character, uint64_t num);

uint64_t howManyOccurencesOfChar(char *string, char character);

void changeFileLine(char *newLine, FILE *inputFile, uint64_t lineNum);

void copyFile(FILE *dest, FILE *src, char *destFileName, char *srcFileName);
