#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50
#define DEPT_LEN 50

// Function prototypes for utility functions fix by sund - green
// what is this code for ? - paulus
// is a shared toolbox of input-checking functions that every module uses, so none of them has to rewrite the same code

void clearInputBuffer(void);
void readString(const char *prompt, char *buffer, int size);
int  readInt(const char *prompt, int *value);
int  readDouble(const char *prompt, double *value);
int  readPositiveInt(const char *prompt, int *value);
int  readPositiveDouble(const char *prompt, double *value);

#endif
