#include "../include/menu.h"
#include "../include/input.h"
#include "../include/military_grade_cryption.h"

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

}

void user_creation_portal() {
    User new_user = (User) {"", "", "", "", "", "", 0, "", "", "", 0, "", ""};

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
    const char* invaild_chars = "!@#$%%^&*()_=+{}[]/><;,`~: ";
    new_user.first_name = get_str_without_char("What is your first name: ", invaild_chars);

    choice = get_yes_or_no("Do you have a middle name (y/n): ");
    if (choice == 'y') 
        new_user.middle_name = get_str_without_char("What is your middle name: ", invaild_chars);

    invaild_chars = "!@#$%%^&*()_=+{}[]/><;,`~:";
    new_user.last_name = get_str_without_char("What is your last name: ", invaild_chars);
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
        printf("Type in a username: ");
        new_user.username = get_str();

        printf("Retype username: ");
        char* retry = get_str();

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
        printf("Type in a password: ");
        new_user.password = get_str();

        printf("Retype password: ");
        char* retry = get_str();
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
    
}