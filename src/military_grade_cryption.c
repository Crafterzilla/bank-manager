#include "../include/military_grade_cryption.h"

void encrypt(char* input, int r) {
    if (r % 10 == 0)
        r++;
    for (size_t i = 0; i < strlen(input); i++) {
        for (int j = 0; j < r; j++) {
            if (input[i] == 'Z')
                input[i] = 'A';
            else if (input[i] == 'z')
                input[i] = 'a';
            else if (input[i] == '9')
                input[i] = '0';
            else if ((input[i] >= 'a' && input[i] < 'z') || (input[i] >= 'A' && input[i] < 'Z')
            || (input[i] >= '0' && input[i] < '9'))
                input[i]++;
        } 
    }
}

void decrypt(char * input, int r) {
    if (r % 10 == 0)
        r++;
    for (size_t i = 0; i < strlen(input); i++) {
        for (int j = 0; j < r; j++) {
            if (input[i] == 'A')
                input[i] = 'Z';
            else if (input[i] == 'a')
                input[i] = 'z';
            else if (input[i] == '0')
                input[i] = '9';
            else if ((input[i] > 'a' && input[i] <= 'z') || (input[i] > 'A' && input[i] <= 'Z')
            || (input[i] > '0' && input[i] <= '9'))
                input[i]--;
        }
    }
}