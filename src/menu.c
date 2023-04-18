#include "../include/menu.h"

bool login_prompt() {
    printf("Gull & Bull Bank Terminal Login Portal\n");
    char choice = get_yes_or_no("Do you currently bank with Gull & Bull bank (y/n): ");

    if (choice == 'y') {
        int ID = sign_in_portal();
        bank_portal(ID);
    }
    else {
        choice = get_yes_or_no("Would you like to create an account with us (y/n): ");
        if (choice == 'y') {
            user_creation_portal();
        }
    }
}

int sign_in_portal() {
    // Get Date for portal
    Date date = get_current_date();
    // Ask user to type in username and password

    char *username = NULL, *password = NULL;
    bool access_granted = false;
    printf("Welcome back to Gull and Bull Bank\n");
    printf("Current Date: %d/%d/%d\n", date.month, date.day, date.year);
    
    int ID = 0;
    while (!access_granted) {
        printf("Username: ");
        username = get_str();

        printf("Password: ");
        password = get_str();

        printf("Please wait...\n");


        ID = does_data_exist(username, USERNAME_OFFSET);
        if (ID > 0) {
            User user = get_user(ID);
            if (strcmp(user.password, password) == 0)
                access_granted = true;
            else
                puts("Invaild pasword");
            
            free_user(&user);
        }
        else {
            printf("Username '%s' does not exist\n", username);
        }

        free(username);
        free(password);
    }

    return ID; //return the ID of the user for future use
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
void user_creation_portal() {
    // Init new_user
    User new_user = (User){0, NULL, NULL, NULL, NULL, NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL};

    printf("Welcome to Gull & Bull User Creation Portal\n");
    printf("You will be guided to help you create a new user on our secure networks\n");
    printf("It is recommended you read our terms of service\n");

    // Ask user to agree with terms and coniditons
    char choice = get_yes_or_no("Have you read and agreed with our terms and conditions (y/n): ");
    if (choice == 'n') {
        printf("Damn that sucks. Maybe next time m8\n");
        return;
    }

    // Thank the user
    printf("Thank you for choosing to bank with Gull & Bull bank\n");
    printf("Moving to Creation Portal...\n\n");

    // Get names of new user
    get_names(&new_user);
    puts("");

    // Get user date of birth
    new_user.DOB = get_DOB();

    // Get user SSN
    new_user.SSN = get_SSN();

    // Get user address
    new_user.address = get_address();

    // Get user phone #
    new_user.phone_number = get_phone_number();

    // Get user email
    new_user.email = get_email();

    get_username(&new_user);

    get_password(&new_user);

    //Init Bank_data
    // Store the data on file and free memory
    create_user(&new_user);
    free_user(&new_user);
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

        if (strcmp(compare_str, data) == 0)
            return ID;
        else
            free_user(&user); 
        ID++;
    }
    return -1;
}
