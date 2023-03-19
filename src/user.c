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
    *user = (User){0, NULL, NULL, NULL, NULL, NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL};
}

void write_user_data_to_file(FILE* fstream, User* user) {
    fprintf(fstream, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%s\n%s\n%s\n%s\n%s\n\n", 
    user->ID, user->first_name, user->middle_name, user->last_name, user->DOB, user->SSN, 
    user->email, user->age, user->address, user->phone_number, user->date_of_account_creation, 
    user->username, user->password);
}

void get_user_creation_date(User* user) {
    Date current = get_current_date();
    //XX-XX-XXXX 10 char + 1 null
    char* current_date = (char*)malloc(sizeof(char) * 11);
    sprintf(current_date, "%02d-%02d-%d", 
    current.month, current.day, current.year);
    user->date_of_account_creation = current_date;
}

void get_age(User* user) {
    Date age = get_current_age(user->DOB);
    user->age = age.year;
}

int store_user_data(User* user) {
    //Check if file is blank
    FILE *fptr = fopen("./data/user_data.txt", "a+");
    if (fptr == NULL) {
        printf("Failed to open user_data.txt\n");
        return 1;
    }

    //Check if file is blank
    char checkBlank = fgetc(fptr);
    if (checkBlank == EOF) {
        printf("File empty m8\n");
        get_user_creation_date(user);
        get_age(user);
        user->ID = 1;
        write_user_data_to_file(fptr, user);
    }
    else {
       ungetc(checkBlank, fptr);
    }
    
}