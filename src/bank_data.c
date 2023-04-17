#include "../include/bank_data.h"

void init_bank_data(Bank_data* data) {
    data->checking_account_amount = 0;
    data->savings_account_amount = 0;
    data->transaction_histroy = NULL;
}