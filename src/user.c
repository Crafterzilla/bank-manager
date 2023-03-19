#include "../include/user.h"

void free_user(User* user) {
    free(user->first_name);
    if (strlen(user->middle_name) != 0)
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

    *user = (User){NULL, NULL, NULL, NULL, NULL, NULL, 0, NULL, NULL, NULL, 0, NULL, NULL};
}