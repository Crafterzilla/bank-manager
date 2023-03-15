#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void print_x(int);
char* get_str();
int get_int();
char get_yes_or_no(const char* prompt);

bool invaild_char_in_str(const char* input, const char* invaild_char);
char* get_str_without_char(const char* prompt, const char* invaild_char);
char* get_DOB(const char* prompt);


void collect_user_data();

#endif