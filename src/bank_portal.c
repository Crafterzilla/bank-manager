#include "../include/bank_portal.h"

void bank_portal(int ID) {
    User_Bank_Data bdata = init_bank_data(ID);
    Date date = get_current_date(); 

    printf("Welcome %s to Gull and Bull Bank Portal\n", bdata.user.first_name);
    printf("Date: %d/%d/%d\n", date.month, date.day, date.year);

    int choice = 0;
    enum options {WITHDRAW = 1, DEPOSIT, TRANSFER, CHECK_ACCOUNTS, VIEW_DATA, LOGOUT};
    while (choice != LOGOUT) {
        puts("Banking Options: ");
        puts("1.) Withdraw money from account");
        puts("2.) Deposit money from account");
        puts("3.) Check money in accounts");
        puts("4.) Transfer money between accounts");
        puts("5.) View personal information");
        puts("6.) Logout");

        printf("Type in an choice from %d to %d: ", WITHDRAW, LOGOUT);
        choice = get_int("Not a vaild integer. Try again: ");

        switch (choice) {
            case WITHDRAW:
                break;
            case DEPOSIT:
                break;
            case TRANSFER:
                break; 
            case CHECK_ACCOUNTS:
                break;
            case VIEW_DATA:
                break;
            case LOGOUT:
                break;
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

    bdata.transaction_histroy = NULL;

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
}