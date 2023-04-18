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

char* readline(FILE* fptr, const int skip_lines) {
    //Set number of lines to read
    int lines_read = 0;
    //Skip number of lines until lines is reached
    //If positive read fowards, if neg read backwards
    if (skip_lines >= 0) {
        while (lines_read != skip_lines) {
            //Read next char in file
            char next_char = fgetc(fptr);
            if (next_char == '\n') //If \n, add to counter
                lines_read++;
            else if (next_char == EOF) { //Else if EOF is reached, return NULL
                return NULL;
            }
        } 
    } 
    else {
        while (lines_read != skip_lines) {
            //Check if fseek returns BOF, if so break and set to BOF
            if (fseek(fptr, -2, SEEK_CUR) < 0) {
                fseek(fptr, 0, SEEK_SET);
                break;
            }
            //Get char and get if fptr is \n to add to lines counted
            char next_char = fgetc(fptr);
            if (next_char == '\n')
                lines_read--;
        }
    }
   //At line, find the size of the string. Then,
    //malloc a new array, put the data in, and then return the
    //data
    int size_of_str = 0;
    char next_char = 'a';
    while (next_char != '\n') {
        next_char = fgetc(fptr);
        size_of_str++;
    }
    
    //Malloc array
    char* str = (char*)malloc(sizeof(char) * (size_of_str + 1));

    //Init str by reversing the ptr
    str[size_of_str - 1] = '\0';
    for (int i = size_of_str - 2; i != -1; i--) {
        fseek(fptr, -2, SEEK_CUR);
        next_char = fgetc(fptr);
        str[i] = next_char;
    }

    //Set pointer to the end of the str read
    fseek(fptr, size_of_str - 1, SEEK_CUR);
    return str;
}

int set_new_user_id() {
    int i = 1;
    while (return_user_file(i, "r") != NULL)
        i++;
    return i;
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

    store_user_data(new_user);
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

// int store_user_data(User* user) {
//     //Check that file exists
//     FILE *fptr = fopen("./data/user_data.txt", "a+");
//     if (fptr == NULL) {
//         printf("Failed to open user_data.txt\n");
//         return 1;
//     }

//     //Check if file is blank
//     char checkBlank = fgetc(fptr);
//     if (checkBlank == EOF) {
//         printf("File empty m8\n");
//         user->ID = 1;
//     }
//     else {
//         //Move pointer back one
//         ungetc(checkBlank, fptr);

//         //Get last user ID
//         set_last_user_id(user, fptr);
//     }

//     //Get last variables for user data
//     set_user_creation_date(user);
//     set_age(user);
//     // encrypt_data(user);
    
//     //Store user data to file
//     fseek(fptr, 0, SEEK_END);
//     write_user_data_to_file(fptr, user);   
//     fclose(fptr);

//     return 0;
// }

User get_user(int ID) {
    User user;
    FILE* fptr = return_user_file(ID, "r");
    if (!fptr) {  
        return (User){0, NULL, NULL, NULL, NULL, NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL};
    }
    const int move = 0;
    user.ID = ID;
    user.first_name = readline(fptr, 1);
    user.middle_name = readline(fptr, move);
    user.last_name = readline(fptr, move);
    user.DOB = readline(fptr, move);
    user.SSN = readline(fptr, move);
    user.email = readline(fptr, move);
    
    char* age = readline(fptr, move);
    user.age = atoi(age);
    free(age);

    user.address = readline(fptr, move);
    user.phone_number = readline(fptr, move);
    user.date_of_account_creation = readline(fptr, move);
    user.username = readline(fptr, move);
    user.password = readline(fptr, move);

    fclose(fptr);
    return user;
}
// User get_user(int ID) {
//     User user;
//     FILE* fptr = fopen("./data/user_data.txt", "r");

//     //Set fptr to the right place in file
//     char* ID_str = NULL;
//     while (true) {
//         ID_str = readline(fptr, ID_OFFSET);
//         if (ID == atoi(ID_str))
//             break;
//         else
//             free(ID_str);
//     }

//     free(ID_str);

//     const int move = 0;
//     user.ID = ID;
//     user.first_name = readline(fptr, move);
//     user.middle_name = readline(fptr, move);
//     user.last_name = readline(fptr, move);
//     user.DOB = readline(fptr, move);
//     user.SSN = readline(fptr, move);
//     user.email = readline(fptr, move);
    
//     char* age = readline(fptr, move);
//     user.age = atoi(age);
//     free(age);

//     user.address = readline(fptr, move);
//     user.phone_number = readline(fptr, move);
//     user.date_of_account_creation = readline(fptr, move);
//     user.username = readline(fptr, move);
//     user.password = readline(fptr, move);

//     fclose(fptr);
//     return user;
// }