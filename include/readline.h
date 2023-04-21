#ifndef READLINE_H
#define READLINE_H

#include <stdio.h>
#include <stdlib.h>

char* readline(FILE* fptr, const int skip_lines);
    #ifdef _WIN32
        #define READ_ONE_LINE 0
    #else
        #define READ_ONE_LINE 1
    #endif
#endif