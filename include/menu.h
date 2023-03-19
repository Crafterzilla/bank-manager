#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/user.h"

bool menu();
bool login_prompt();
void user_menu();
void sign_in_portal();
void user_creation_portal();
void get_names(User* new_user);

#endif