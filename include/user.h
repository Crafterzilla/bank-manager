#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct User {
    char* first_name; //1
    char* middle_name; //2
    char* last_name; //3
    char* DOB; //4
    char* SSN; //5
    char* email; //8
    int age;
    char* address; //6
    char* phone_number; //7
    char* date_of_account_creation;
    unsigned int ID;
    char* username;
    char* password;
} User;

void create_user(User user);
void free_user(User* user);
User get_user(int ID);

void store_user_data(User user);
void store_user_passwords(User user);
int set_user_id();
int set_user_age(char* DOB);

#endif