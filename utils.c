#include "utils.h"

// This section will clear the input buffer  ---  pau
void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

//  this section will  Read a full line of text safely using fgets -- green
void readString(const char *prompt, char *buffer, int size)
{
    printf("%s", prompt);
    if (fgets(buffer, (size_t)size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    // this fixes  the trailing newline character --- update by sunday guys
    buffer[strcspn(buffer, "\n")] = '\0';
}

//  this section will Read a floating-point number input
int readDouble(const char *prompt, double *value)
{
    char buffer[64];
    char *end;

    readString(prompt, buffer, sizeof(buffer));
    if (strlen(buffer) == 0) {
        return 0;
    }
    *value = strtod(buffer, &end);
    if (end == buffer || *end != '\0') {
        return 0;  
    }
    return 1;
}

//  this section will read a whole number -returns 1 on success, 0 on invalid input  ## dont touch this code it is working fine
int readInt(const char *prompt, int *value)
{
    char buffer[64];
    char *end;
    long v;

    readString(prompt, buffer, sizeof(buffer));
    if (strlen(buffer) == 0) {
        return 0;
    }
    v = strtol(buffer, &end, 10);
    if (end == buffer || *end != '\0') {
        return 0;   
    }
    *value = (int)v;
    return 1;
}

// Read a whole number that must be >= 0 -- ano who did this ?
int readPositiveInt(const char *prompt, int *value)
{
    if (!readInt(prompt, value)) {
        return 0;
    }
    return *value >= 0;
}

// Read a floating-point number that must be >= 0 --  same but double 
int readPositiveDouble(const char *prompt, double *value)
{
    if (!readDouble(prompt, value)) {
        return 0;
    }
    return *value >= 0.0;
}
