#ifndef BANK_DATA_H
#define BANK_DATA_H

#include <stdio.h>
#include "user.h"

typedef struct Bank_data {
    double checking_account_amount;
    double savings_account_amount;
    char **transaction_histroy;
} Bank_data;

void init_bank_data(Bank_data*);

#endif