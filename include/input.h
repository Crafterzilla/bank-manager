#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

char* get_str();
int get_int(const char*);
double get_double();
char get_yes_or_no(const char* prompt);

bool invaild_char_in_str(const char* input, const char* invaild_char);
char* get_str_without_char(const char* prompt, const char* invaild_char);

//DOB functions
char* get_DOB();
bool check_for_ints(char* input, int, int);
bool check_DOB_date(const char* DOB);
long long convert_time_to_unix_time(int, int, int);
void collect_user_data();

char* get_SSN();
char* get_phone_number();
char* get_email();

//Address functions
char* get_address();
bool is_state_vaild(char*);

#endif