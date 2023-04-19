#include "../include/bank_portal.h"

void bank_portal(int ID) {
    User_Bank_Data bdata = init_bank_data(ID);
    Date date = get_current_date(); 

    printf("\nWelcome %s to Gull and Bull Bank Portal\n", bdata.user.first_name);
    printf("Date: %d/%d/%d\n", date.month, date.day, date.year);

    int choice = 0;
    enum options {WITHDRAW = 1, DEPOSIT, CHECK_ACCOUNTS, TRANSFER, VIEW_DATA, VIEW_HISTORY, LOGOUT};
    while (choice != LOGOUT) {
        puts("Banking Options: ");
        puts("1.) Withdraw money from account");
        puts("2.) Deposit money from account");
        puts("3.) Check money in accounts");
        puts("4.) Transfer money between accounts");
        puts("5.) View personal information");
        puts("6.) View Transaction History");
        puts("7.) Logout");

        printf("Type in an choice from %d to %d: ", WITHDRAW, LOGOUT);
        choice = get_int("Not a vaild integer. Try again: ");

        switch (choice) {
            case WITHDRAW: withdraw(&bdata); break;
            case DEPOSIT: deposit(&bdata); break;
            case TRANSFER:
                break; 
            case CHECK_ACCOUNTS: check_account_value(&bdata); break;
            case VIEW_DATA:
                break;
            case VIEW_HISTORY: print_transaction_history(&bdata); break;
            case LOGOUT: break;
            default:
                printf("%d is an invaild option. Please type an integer from %d to %d\n", choice, WITHDRAW, LOGOUT);
                break;
        }
    }

    store_bank_data(&bdata);
}

User_Bank_Data null_bank() {
    return (User_Bank_Data){return_null_user(), 0, 0, NULL};
}

FILE* transaction_fptr(int ID, const char* mode) {
    //Get str for where the transcations are stored for user ID
    char filename[100] = {0};
    sprintf(filename, "./data/logs/%d_log.txt", ID);

    //Attempt to open file. If success full, return file,
    //else create file, and reopen file in mode and return it 
    FILE* transaction_file = fopen(filename, mode);
    if (!transaction_file) {
        transaction_file = fopen(filename, "w");
        fclose(transaction_file);
        transaction_file = fopen(filename, mode);
    }

    return transaction_file;
}

User_Bank_Data init_bank_data(int ID) {
    //Attempt to open bank_data to see if user has logged into account
    FILE* fptr = return_user_file(ID, "r");
    if (!fptr) {
        puts("File does not exist");
        return null_bank();
    }

    
    User_Bank_Data bdata = null_bank(); //init bank data
    bdata.user = get_user(ID); //Get user data from ID.txt
    char* tmp = NULL;

    char* double_str = readline(fptr, DATA_OFFSET);
    bdata.checking_account_amount = strtod(double_str, &tmp);
    free(double_str);

    double_str = readline(fptr, 0);
    bdata.savings_account_amount = strtod(double_str, &tmp);
    free(double_str);

    bdata.transaction_fptr = transaction_fptr(ID, "r+");

    fclose(fptr); //Close file
    return bdata; //Return all the data
}

void store_bank_data(User_Bank_Data* bdata) {
    int ID = bdata->user.ID;
    store_user_data(&(bdata->user));

    FILE* fptr = return_user_file(ID, "a");
    fprintf(fptr, "%lf\n%lf\n", bdata->checking_account_amount, bdata->savings_account_amount);

    fclose(fptr);
    free_user(&(bdata->user));

    fclose(bdata->transaction_fptr);
}

void check_account_value(User_Bank_Data* bdata) {
    puts("\nYour accounts: ");
    printf("Checking account: $%.2lf\n", bdata->checking_account_amount);
    printf("Savings account: $%.2lf\n\n", bdata->savings_account_amount);
}

int checking_or_savings() {
    int choice = 0;
    while (true) {
        puts("1.) Checking account");
        puts("2.) Savings account");
        puts("3.) Return");
        printf("Withdraw/Deposit from which account: ");

        choice = get_int("Invaild integer: ");
        if (choice == 3)
            return 0;
        else if (choice != CHECKING && choice != SAVINGS)
            printf("Invaid option\n");
        else
            break; 
    }
    return choice;
}

void withdraw(User_Bank_Data* bdata) {
    check_account_value(bdata);
    int choice = checking_or_savings();
    if (choice == 0)
        return;
    printf("Withdraw how much (Type in decimal/integer number): ");
    double withdraw_amount = get_double();
    char* date = get_current_date_str();

    switch (choice) {
        case CHECKING:
            bdata->checking_account_amount -= withdraw_amount;
            fprintf(bdata->transaction_fptr, "%s Checking account withdraw: -$%.2lf\n", date, withdraw_amount);
            break;
        case SAVINGS:
            bdata->savings_account_amount -= withdraw_amount; 
            fprintf(bdata->transaction_fptr, "%s Savings account withdraw: -$%.2lf\n", date, withdraw_amount);
            break;
    }

    free(date);
}

void deposit(User_Bank_Data* bdata) {
    check_account_value(bdata);
    int choice = checking_or_savings();
    if (choice == 0)
        return;
    printf("Deposit how much (Type in decimal/integer number): ");
    double deposit_amount = get_double();
    char* date = get_current_date_str();

    switch (choice) {
        case CHECKING:
            bdata->checking_account_amount += deposit_amount;
            fprintf(bdata->transaction_fptr, "%s Checking account deposit: $%.2lf\n", date, deposit_amount);
            break;
        case SAVINGS:
            bdata->savings_account_amount += deposit_amount; 
            fprintf(bdata->transaction_fptr, "%s Savings account deposit: $%.2lf\n", date, deposit_amount);
            break;
    }

    free(date);
}

void print_transaction_history(User_Bank_Data* bdata) {
    printf("\nTransaction history: \n");

    char* line = "test";
    fseek(bdata->transaction_fptr, 0, SEEK_SET);
    while (true) {
        line = readline(bdata->transaction_fptr, 0);
        if (line == NULL) {
            return;
        }
        printf("%s\n", line);
        free(line);
    }
    puts("");
}