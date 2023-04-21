#include "../include/user.h"

void free_user(User* user) {
    //Free all user malloced strings
    free(user->first_name);
    if (user->middle_name != NULL)
        free(user->middle_name);
    free(user->last_name);
    free(user->DOB);
    free(user->SSN);
    free(user->email);
    free(user->address);
    free(user->phone_number);
    free(user->date_of_account_creation);
    free(user->username);
    free(user->password);

    //Reinit user to NULL for wild pointers
    *user = return_null_user();
}
void encrypt_data(User* user) {
    encrypt(user->first_name, user->age);
    encrypt(user->middle_name, user->age);
    encrypt(user->last_name, user->age);
    encrypt(user->DOB, user->age);
    encrypt(user->SSN,user->age);
    encrypt(user->email, user->age);
    encrypt(user->address, user->age);
    encrypt(user->phone_number, user->age);
    encrypt(user->date_of_account_creation, user->age);
    encrypt(user->username, user->age);
    encrypt(user->password, user->age);
}

void set_new_creation_date(User* user) {
    Date current = get_current_date();
    //XX-XX-XXXX 10 char + 1 null
    char* current_date = (char*)malloc(sizeof(char) * 11);
    sprintf(current_date, "%02d-%02d-%d", 
    current.month, current.day, current.year);
    user->date_of_account_creation = current_date;
}

void set_age(User* user) {
    Date age = get_current_age(user->DOB);
    user->age = age.year;
}


char* readline(FILE* fptr, int skip_lines) {
    char* str = NULL; //Init pointer for string
    for (int i = 0; i < skip_lines; i++) {
        free(str); //Free str if not the proper line reached
        size_t bytes = 0; ssize_t size = 0; //Init variables needed
        size = getline(&str, &bytes, fptr); //Read line from file
        if (size == EOF) //If size is zero or EOF is reached, return null
            return NULL;
        
        if (str[size - 1] == '\n') { //Remove '\n' from end of string is it contains it
            str[size - 1] = '\0'; 
        }
    }
    return str;
}

int set_new_user_id() {
    int i = 1;
    while (return_user_file(i, "r") != NULL)
        i++;
    return i;
}

User return_null_user(){
    return (User){0, NULL, NULL, NULL, NULL, NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL};
}

FILE* return_user_file(int ID, const char* mode) {
    char file[100] = {0};
    sprintf(file, "./data/bank_portal/%d.txt", ID);

    return fopen(file, mode);
}

void create_user(User* new_user) {
    new_user->ID = set_new_user_id();
    set_new_creation_date(new_user);
    set_age(new_user);

    int ID = new_user->ID;
    store_user_data(new_user);
    FILE* fptr = return_user_file(ID, "a");
    fprintf(fptr, "0\n0\n");
    fclose(fptr);
}

int store_user_data(User* user) {
    FILE* fptr = return_user_file(user->ID, "w");
    if (!fptr) {
        puts("File creation or opening failed");
        return -1;
    }

    fprintf(fptr, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%s\n%s\n%s\n%s\n%s\n", 
    user->ID, user->first_name, user->middle_name, user->last_name, user->DOB, user->SSN, 
    user->email, user->age, user->address, user->phone_number, user->date_of_account_creation, 
    user->username, user->password);

    free_user(user);
    fclose(fptr);
    return 0;
}

User get_user(int ID) {
    User user;
    FILE* fptr = return_user_file(ID, "r");
    if (!fptr) {  
        return return_null_user();
    }
    user.ID = ID;
    user.first_name = readline(fptr, 2);
    user.middle_name = readline(fptr, READ_ONE_LINE);
    user.last_name = readline(fptr, READ_ONE_LINE); 
    user.DOB = readline(fptr, READ_ONE_LINE);
    user.SSN = readline(fptr, READ_ONE_LINE);
    user.email = readline(fptr, READ_ONE_LINE);
    
    char* age = readline(fptr, READ_ONE_LINE);
    user.age = atoi(age);
    free(age);

    user.address = readline(fptr, READ_ONE_LINE);
    user.phone_number = readline(fptr, READ_ONE_LINE);
    user.date_of_account_creation = readline(fptr, READ_ONE_LINE);
    user.username = readline(fptr, READ_ONE_LINE);
    user.password = readline(fptr, READ_ONE_LINE);

    fclose(fptr);
    return user;
}

int does_data_exist(char *data, const int offset) {
    User user;
    int ID = 1;
    while (true) {
        user = get_user(ID);
        if (user.ID == 0)
            break;
        
        char* compare_str = NULL;
        switch (offset) {
            case ID_OFFSET:
                char ID_str[15] = {0};
                sprintf(ID_str, "%d", user.ID);
                compare_str = ID_str;
                break;
            case FIRST_NAME_OFFSET: compare_str = user.first_name; break;
            case MIDDLE_NAME_OFFSET: compare_str = user.middle_name; break;
            case LAST_NAME_OFFSET: compare_str = user.last_name; break;
            case DOB_OFFSET: compare_str = user.DOB; break;
            case SSN_OFFSET: compare_str = user.SSN; break;
            case EMAIL_OFFSET: compare_str = user.email; break;
            case AGE_OFFSET: 
                char age_str[15] = {0};
                sprintf(age_str, "%d", user.age);
                compare_str = age_str;
                break;
            case ADDRESS_OFFSET: compare_str = user.address; break;
            case PHONE_OFFSET: compare_str = user.phone_number; break;
            case DOAC_OFFSET: compare_str = user.date_of_account_creation; break;
            case USERNAME_OFFSET: compare_str = user.username; break;
            case PASSWORD_OFFSET: compare_str = user.password; break;
        }

        if (strcmp(compare_str, data) == 0) {
            free_user(&user);
            return ID;
        }
        else
            free_user(&user); 
        ID++;
    }
    return -1;
}

void get_names(User *new_user) {
    const char *invaild_chars = "!@#$%%^&*()_=+{}[]/><;,`~: ";
    new_user->first_name = get_str_without_char("What is your first name: ", invaild_chars);

    char choice = get_yes_or_no("Do you have a middle name (y/n): ");
    if (choice == 'y')
        new_user->middle_name = get_str_without_char("What is your middle name: ", invaild_chars);

    invaild_chars = "!@#$%%^&*()_=+{}[]/><;,`~:";
    new_user->last_name = get_str_without_char("What is your last name: ", invaild_chars);
}

void get_username(User* new_user) {
    // Get username
    while (true) {
        // Make user type in username twice
        printf("Type in a username: ");

        new_user->username = get_str();

        printf("Retype username: ");
        char *retry = get_str();

        //Ensure username is not already taken
        if (does_data_exist(new_user->username, USERNAME_OFFSET) > 0) {
            printf("Username '%s' is already taken\n", new_user->username);
            free(retry);
            free(new_user->username);
        } 
        // Compare and ensure usernames match
        else if (strcmp(new_user->username, retry) == 0) {
            free(retry);
            break;
        } //Username and retry do not match
        else {
            free(retry);
            free(new_user->username);
            printf("Usernames do not match\n");
        }
    }
}

void get_password(User* new_user) {
    // Get Password
    while (true) {
        // Make user type in password twice
        printf("Type in a password: ");
        new_user->password = get_str();

        printf("Retype password: ");
        char *retry = get_str();

        // Make sure passwords match
        if (strcmp(new_user->password, retry) == 0) {
            free(retry);
            break;
        }
        else {
            free(retry);
            free(new_user->password);
            printf("Usernames do not match\n");
        }
    }
}