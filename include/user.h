#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "military_grade_cryption.h"
#include <stdbool.h>
#include <time.h>
#include "time_time.h"
// #include "bank_portal.h"
// #include "menu.h"

#define DATA_OFFSET 13

enum datafile_data_offsets {
    ID_OFFSET, 
    FIRST_NAME_OFFSET,
    MIDDLE_NAME_OFFSET,
    LAST_NAME_OFFSET,
    DOB_OFFSET,
    SSN_OFFSET,
    EMAIL_OFFSET,
    AGE_OFFSET,
    ADDRESS_OFFSET,
    PHONE_OFFSET,
    DOAC_OFFSET,
    USERNAME_OFFSET,
    PASSWORD_OFFSET
};

typedef struct User {
    int ID;
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
    char* username;
    char* password;
    // Bank_data bank_data;
} User;

void create_user(User*);
void free_user(User* user);
User get_user(int ID);
FILE* return_user_file(int ID, const char* mode);
//
void set_new_creation_date(User* user);
void set_age(User* user);
void encrypt_data(User* user);
int set_last_user_id();
char* readline(FILE* fptr, const int line);

int store_user_data(User* user);
void store_user_passwords(User user);
int set_user_id();
int set_user_age(char* DOB);
User return_null_user();
#endif