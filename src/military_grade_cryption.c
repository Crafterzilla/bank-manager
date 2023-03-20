#include "../include/military_grade_cryption.h"

void encrypt(char* input, int r) {
    for (size_t i = 0; i < strlen(input); i++) {
        for (int j = 0; j < r; j++) {
            if (input[i] == '~')
                input[i] = ' ';
            else
                input[i]++;
        } 
    }
}

void decrypt(char * input, int r) {
    for (size_t i = 0; i < strlen(input); i++) {
        for (int j = 0; j < r; j++) {
            if (input[i] == ' ')
                input[i] = '~';
            else
                input[i]--;
        } 
    }
}