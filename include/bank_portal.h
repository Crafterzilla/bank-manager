#ifndef BANK_PORTAL_H
#define BANK_PORTAL_H

#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "time_time.h"
#include "input.h"

enum account_type {CHECKING = 1, SAVINGS};

typedef struct User_Bank_Data {
    User user;
    double checking_account_amount;
    double savings_account_amount;
    FILE* transaction_fptr;
} User_Bank_Data;

//Basic banking portal back-end
void bank_portal(int ID);
User_Bank_Data init_bank_data(int ID);
User_Bank_Data null_bank();
FILE* transaction_fptr(int ID, const char*);
void store_bank_data(User_Bank_Data*);
int checking_or_savings();
//Options in file
void withdraw(User_Bank_Data*);
void deposit(User_Bank_Data*);
void transfer(User_Bank_Data*);
void check_account_value(User_Bank_Data*);
void print_account_data(User_Bank_Data*);
void print_transaction_history(User_Bank_Data*);

#endif