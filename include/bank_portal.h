#ifndef BANK_PORTAL_H
#define BANK_PORTAL_H

#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "time_time.h"
#include "input.h"

typedef struct User_Bank_Data {
    User user;
    double checking_account_amount;
    double savings_account_amount;
    char **transaction_histroy;
} User_Bank_Data;

void bank_portal(int ID);
User_Bank_Data init_bank_data(int ID);
User_Bank_Data null_bank();
void store_bank_data(User_Bank_Data*);

#endif