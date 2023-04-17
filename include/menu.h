#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "user.h"
#include "time_time.h"
#include "input.h"
#include "military_grade_cryption.h"

bool menu();
bool login_prompt();
void user_menu();
int sign_in_portal();
void user_creation_portal();
void get_names(User* new_user);
void get_username(User* new_user);
void get_password(User* new_user);
//Username and Password Checks
bool does_data_exist(FILE*, char* username, const int offset);
bool is_password_vaild(FILE*, char* username, char* password);
#endif