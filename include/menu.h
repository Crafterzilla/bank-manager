#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//User related funcitons
typedef struct User {
    char* first_name; //1
    char* middle_name; //2
    char* last_name; //3
    char* DOB; //4
    char* SSN;
    char* email;
    int age;
    char* address;
    char* phone_number;
    char* date_of_account_creation;
    unsigned int ID;
    char* username;
    char* password;
} User;

void create_user(User user);
void free_user(User user);
User get_user(int ID);


bool menu();
bool login_prompt();
void user_menu();
void sign_in_portal();
void user_creation_portal();


#endif