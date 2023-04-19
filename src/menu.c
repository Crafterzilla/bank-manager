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

