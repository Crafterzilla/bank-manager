#include "../include/menu.h"

bool login_prompt() {
    printf("Gull & Bull Bank Terminal Login Portal\n");   
    char choice = get_yes_or_no("Do you currently bank with Gull & Bull bank (y/n): ");

    if (choice == 'y') {
        sign_in_portal();
    }
    else {
        choice = get_yes_or_no("Would you like to create an account with us (y/n): ");
        if (choice == 'y') {
            user_creation_portal();
        }
    }
}


void sign_in_portal() {
    //Open data file for reading
    FILE* user_data_file = fopen("./data/user_data.txt", "r");
    if (user_data_file == NULL) {
        printf("Error reading data file\n");
        return;
    }

    //Get Date for portal
    Date date = get_current_date();
    //Ask user to type in username and password

    char* username = NULL, *password = NULL;
    bool access_granted = false;
    printf("Welcome back to Gull and Bull Bank\n");
    printf("Current Date: %d/%d/%d\n", date.month, date.day, date.year);
    while (!access_granted) { 
        printf("Username: ");
        username = get_str();

        printf("Password: ");
        password = get_str();

        printf("Please wait...\n");

        //Check if username and password match with any user
        if (does_data_exist(user_data_file, username, USERNAME_OFFSET)) {
            char* user_password = readline(user_data_file, 0);
            //Check if password exists and grant access if they match
            if (strcmp(password, user_password) == 0) {
                printf("Access granted!\n");
                access_granted = true;
            }
            else { //Tell user to try again
                printf("Invaild Password\nTry again\n");
            }

            //Free memory
            free(user_password);
            user_password = NULL;
        }
        else { //Tell user to type in a vaild user
            printf("Username does not exist\n");
            printf("Type in a vaild username or create a new user\n");
        }
        //Free memory
        free(password);
        free(username);
        password = NULL;
        username = NULL;
    }
    fclose(user_data_file); //Close file
}

void get_names(User* new_user) {
    const char* invaild_chars = "!@#$%%^&*()_=+{}[]/><;,`~: ";
    new_user->first_name = get_str_without_char("What is your first name: ", invaild_chars);

    char choice = get_yes_or_no("Do you have a middle name (y/n): ");
    if (choice == 'y') 
        new_user->middle_name = get_str_without_char("What is your middle name: ", invaild_chars);
    
    invaild_chars = "!@#$%%^&*()_=+{}[]/><;,`~:";
    new_user->last_name = get_str_without_char("What is your last name: ", invaild_chars); 
}

void user_creation_portal() {
    //Init new_user
    User new_user = (User) {0, NULL, NULL, NULL, NULL, NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL};

    printf("Welcome to Gull & Bull User Creation Portal\n");
    printf("You will be guided to help you create a new user on our secure networks\n");
    printf("It is recommended you read our terms of service\n");

    //Ask user to agree with terms and coniditons
    char choice = get_yes_or_no("Have you read and agreed with our terms and conditions (y/n): ");
    if (choice == 'n') {
        printf("Damn that sucks. Maybe next time m8\n");
        return;
    }

    //Thank the user
    printf("Thank you for choosing to bank with Gull & Bull bank\n");
    printf("Moving to Creation Portal...\n\n");

    //Get names of new user
    get_names(&new_user); 
    puts("");

    //Get user date of birth
    new_user.DOB = get_DOB();

    //Get user SSN
    new_user.SSN = get_SSN();

    //Get user address
    new_user.address = get_address();

    //Get user phone #
    new_user.phone_number = get_phone_number();

    //Get user email
    new_user.email = get_email();

    //Get username
    while (true) {
        //Make user type in username twice
        printf("Type in a username: ");
       
        new_user.username = get_str();

        printf("Retype username: ");
        char* retry = get_str();

        //Compare and ensure usernames match
        if (strcmp(new_user.username, retry) == 0) {
            free(retry);
            break;
        }
        else {
            free(retry);
            free(new_user.username);
            printf("Usernames do not match\n");
        }
    }

    //Get Password
    while (true) {
        //Make user type in password twice
        printf("Type in a password: ");
        new_user.password = get_str();

        printf("Retype password: ");
        char* retry = get_str();

        //Make sure passwords match
        if (strcmp(new_user.password, retry) == 0) {
            free(retry);
            break;
        }
        else {
            free(retry);
            free(new_user.password);
            printf("Usernames do not match\n");
        }
    } 

    //Store the data on file and free memory
    store_user_data(&new_user);
    free_user(&new_user);
}

bool does_data_exist(FILE* fptr, char* data, const int offset) {
    fseek(fptr, 0, SEEK_SET);

    //Set the readline ptr to usernames and check the first
    //username
    char* tmp_data = readline(fptr, offset);
    if (strcmp(tmp_data, data) == 0) {
        free(tmp_data);
        return true;
    }
    free(tmp_data);

    //Check the remaining usernames for possible usernames
    while (true) {
        char* stored_data = readline(fptr, DATA_OFFSET); //Read username line
        if (stored_data == NULL) //If EOF, return false
            return false;
        if (strcmp(stored_data, data) == 0) //If 0, return true
            return true; 
        //Free data if usernames did not match
        free(stored_data);
        stored_data = NULL;
    }
 
    return false; 
}