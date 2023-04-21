#include "../include/readline.h"

char* readline(FILE* fptr, const int skip_lines) {
    #ifdef _WIN32
        //Reading 0 reads current line
        //Reading > 0 reads lines after
        //Returns NULL if BOF or EOF is reached
        //Expects fptr to be at the begining of some line

        //Init counter variables to find size of str and the amount of lines to skip
        int line_size = 0, line_counter = 0;
        char next_char = 0;

        /* Algorithm: Read a char from the file and increment pointer by
        one (done by fgetc). If EOF or reached, return NULL. If '\n' is found,
        if the number of lines were counted, then break from the loop. Else this is not
        the line and continue to next line where line_size is 0 again and line counter is incremented
        by one. Else increment line size
        */
        while (true) {
            next_char = fgetc(fptr);
            if (next_char == EOF)
                return NULL;
            else if (next_char == '\n' && line_counter == skip_lines)
                break;
            else if (next_char == '\n') {
                    line_size = 0;
                    line_counter++;
            }
            else
                line_size++; 
        }

        //Create array of null char with line size found
        char* str = (char*)calloc(sizeof(char), line_size + 1);
        //Move pointer back to the begining of the line
        fseek(fptr, -line_size - 2, SEEK_CUR);
        //Init str with chars from file with fgetc 
        for (int i = 0; i < line_size; i++) {
            next_char = fgetc(fptr);
            str[i] = next_char;
        }
        //Move pointer + 1
        next_char = fgetc(fptr);
            return str;
    #else
        char* str = NULL; //Init pointer for string
        for (int i = 0; i < skip_lines; i++) {
            free(str); //Free str if not the proper line reached
            size_t bytes = 0; ssize_t size = 0; //Init variables needed
            size = getline(&str, &bytes, fptr); //Read line from file
            if (size == EOF) //If size is zero or EOF is reached, return null
                return NULL;
            
            if (str[size - 1] == '\n') { //Remove '\n' from end of string is it contains it
                str[size - 1] = '\0'; 
            }
        }
        return str;

    #endif
}