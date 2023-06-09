#include "../include/bank_portal.h"

void bank_portal(int ID) {
    User_Bank_Data bdata = init_bank_data(ID);
    Date date = get_current_date(); 

    printf("\nWelcome %s to Gull and Bull Bank Portal\n", bdata.user.first_name);
    printf("Date: %d/%d/%d\n", date.month, date.day, date.year);

    int choice = 0;
    enum options {WITHDRAW = 1, DEPOSIT, CHECK_ACCOUNTS, TRANSFER, VIEW_DATA, VIEW_HISTORY, LOGOUT};
    while (choice != LOGOUT) {
        puts("\nBanking Options: ");
        puts("1.) Withdraw money from account");
        puts("2.) Deposit money from account");
        puts("3.) Check money in accounts");
        puts("4.) Transfer money between accounts");
        puts("5.) View/Edit personal information");
        puts("6.) View Transaction History");
        puts("7.) Logout");

        printf("Type in an choice from %d to %d: ", WITHDRAW, LOGOUT);
        choice = get_int("Not a vaild integer. Try again: ");

        switch (choice) {
            case WITHDRAW: withdraw(&bdata); break;
            case DEPOSIT: deposit(&bdata); break;
            case TRANSFER: transfer(&bdata); break; 
            case CHECK_ACCOUNTS: check_account_value(&bdata); break;
            case VIEW_DATA: user_data(&bdata); break;
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

    double_str = readline(fptr, READ_ONE_LINE);
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

int checking_or_savings(const char* prompt) {
    int choice = 0;
    while (true) {
        puts("\n1.) Checking account");
        puts("2.) Savings account");
        puts("3.) Return");
        printf(prompt);

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
    int choice = checking_or_savings("Withdraw from which account: ");
    if (choice == 0)
        return;
    printf("Withdraw how much (Type in decimal/integer number): ");
    double withdraw_amount = get_double();
    char* date = get_current_date_str();
    fseek(bdata->transaction_fptr, 0, SEEK_END);

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
    int choice = checking_or_savings("Deposit into which account: ");
    if (choice == 0)
        return;
    printf("Deposit how much (Type in decimal/integer number): ");
    double deposit_amount = get_double();
    char* date = get_current_date_str();
    fseek(bdata->transaction_fptr, 0, SEEK_END);

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
        line = readline(bdata->transaction_fptr, READ_ONE_LINE);
        if (line == NULL) {
            return;
        }
        printf("%s\n", line);
        free(line);
    }
    puts("");
}

void transfer(User_Bank_Data* bdata) {
    enum recipents {SELF = 1, ZEELLE, RETURN};
    printf("Transfer recipents: \n");
    puts("1.) Transfer between accounts");
    puts("2.) Zeelle (Send money to other Gull and Bull users)");
    puts("3.) Return");

    int choice = 0;
    while (true) {
        printf("Type in an option: ");
        choice = get_int("Invaild integer: ");

        if (choice == SELF || choice == ZEELLE || choice == RETURN)
            break;
        else
            printf("Invaild option\n"); 
    }

    switch (choice) {
        case SELF: transfer_self(bdata); break;
        case ZEELLE: zeelle(bdata); break; 
        case RETURN: return;
    }
}

void transfer_self(User_Bank_Data* bdata) {
    int account = checking_or_savings("Which account are you transfering money to: ");

    printf("Type in amount to transfer over: ");
    double amount = get_double();
    char* date = get_current_date_str();
    fseek(bdata->transaction_fptr, 0, SEEK_END);

    switch (account) {
        case CHECKING:
            bdata->checking_account_amount += amount;
            bdata->savings_account_amount -= amount; 
            fprintf(bdata->transaction_fptr, "%s Transfer from savings to checking: -$%.2lf\n", date, amount);
            break;
        case SAVINGS: 
            bdata->checking_account_amount -= amount;
            bdata->savings_account_amount += amount;
            fprintf(bdata->transaction_fptr, "%s Transfer from checking to savings: $%.2lf\n", date, amount);
            break;
        case 3:
            break;
    } 
    free(date);
}

void zeelle(User_Bank_Data* bdata) {
    printf("\nZeelee Portal: \n");
    printf("To transfer money to other account, type in their phone number below\n");

    //Find user through their phone number using does_data_exist function
    //return the ID once done and keep retrying until user if found or if user
    //gives up
    int ID = 0;
    while (ID <= 0 && ID != bdata->user.ID) {
        char* phone_num = get_phone_number();
        printf("Searching for user...\n");
        ID = does_data_exist(phone_num, PHONE_OFFSET);
        
        if (ID <= 0) {
            char choice = get_yes_or_no("User not found. Try again (y/n): ");
            if (choice == 'n')
                return;
        }

        free(phone_num);
    }

    //Load the other user's bank account into memory
    User_Bank_Data other_bdata = init_bank_data(ID);

    //Check to make sure user is the correct user in case of wrong number
    printf("User with name %s %s found!\n", other_bdata.user.first_name, other_bdata. user.last_name);
    char choice = get_yes_or_no("Is user correct (y/n): ");
    if (choice == 'n') {
        store_bank_data(&other_bdata);
        return;
    }

    //Type in amount to send
    printf("Type in amount to be sent: ");
    double amount = get_double();

    //Add to other user, take away from self
    other_bdata.checking_account_amount += amount;
    bdata->checking_account_amount -= amount;

    //Get the current date to put all transaction into their
    //repective logs    
    char* date = get_current_date_str();

    //Put pointer to end. Then, type out the transaction that occured
    fseek(bdata->transaction_fptr, 0, SEEK_END);
    fprintf(bdata->transaction_fptr, "%s Sent money to user %s through Zeelle: -$%.2lf\n", 
    date, other_bdata.user.first_name, amount);

    //Put the pointer to end for other user. Then store the transaction that 
    //occurred for that user
    fseek(other_bdata.transaction_fptr, 0, SEEK_END);
    fprintf(other_bdata.transaction_fptr, "%s Received money from user %s through Zeelle: $%.2lf\n",
    date, bdata->user.first_name, amount);

    //Free allocated memory in heap
    free(date);
    store_bank_data(&other_bdata);
}

void user_data(User_Bank_Data* bdata) {
    enum data_options {VIEW = 1, MODIFY, RETURN};
    int choice = 0;
    while (true) {
        printf("\n1.) View personal data\n");
        printf("2.) Modify personal data\n");
        printf("3.) Return\n");
        
        printf("Type an option above: ");
        choice = get_int("Invaild integer: ");

        if (choice >= VIEW && choice <= RETURN)
            break;
        else
            printf("Invaild option\n"); 
    }

    switch (choice) {
        case VIEW: print_user_data(&(bdata->user)); break;
        case MODIFY: modify_user_data(&(bdata->user)); break;
        case RETURN: break;
    }
}

void print_user_data(User* user) {
    printf("\nUser informtation for User %d: \n", user->ID);
    printf("First name: %s\n", user->first_name);
    printf("Middle name: %s\n", user->middle_name);
    printf("Last name: %s\n", user->last_name);
    printf("Date of birth: %s\n", user->DOB);
    printf("SSN: %s\n", user->SSN);
    printf("Email: %s\n", user->email);
    printf("Age: %d\n", user->age);
    printf("Address: %s\n", user->address);
    printf("Phone number: %s\n", user->phone_number);
    printf("Date of account creation: %s\n", user->date_of_account_creation);
    printf("Username: %s\n\n", user->username);
}

void modify_user_data(User* user) {
    enum changable_data {NAME = 1, EMAIL, ADDRESS, PHONE, PASSWORD, RETURN};

    puts("\nOption to change info for: ");
    printf("%d.) Change Name\n", NAME);
    printf("%d.) Change Email\n", EMAIL);
    printf("%d.) Change Address\n", ADDRESS);
    printf("%d.) Change Phone number\n", PHONE);
    printf("%d.) Change Password\n", PASSWORD);
    printf("%d.) Return\n", RETURN);

    int choice = 0;
    while (true) {
        printf("Type in an option to change: ");
        choice = get_int("Invaild integer: ");
        if (choice >= NAME && choice <= RETURN)
            break;
        else
            printf("Invaild option\n");
    }

    switch (choice) {
        case NAME:
            get_names(user);
            break;
        case EMAIL:
            free(user->email);
            user->email = get_email();
            break;
        case ADDRESS:
            free(user->address);
            user->address = get_address();
            break;
        case PHONE:
            free(user->phone_number);
            user->phone_number = get_phone_number();
            break;
        case PASSWORD:
            free(user->password);
            get_password(user);
            break;
        case RETURN: 
            break;
    }
}