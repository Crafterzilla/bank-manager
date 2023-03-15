#include "../include/input.h"

void print_x(int x) {
    printf("%d\n", x);
}

char *get_str() {
    char buffer;
    unsigned int size = 0;
    char *str = (char *)malloc(sizeof(char));
    if (str == NULL) {
        printf("ERROR: Not enough memory detected\n");
        return NULL;
    }

    while (true) {
        buffer = getchar();
        if (buffer == '\n') {
            break;
        }
        size++;
        str = realloc(str, sizeof(char) * (size + 1));
        if (str == NULL) {
            printf("ERROR: Not enough memory detected\n");
            return NULL;
        }
        str[size - 1] = buffer;
        str[size] = '\0';
    }
    return str;
}

int get_int(const char *error_message) {
    bool success = false;
    char *input = NULL;
    while (!success) {
        bool isNegative = false;
        input = get_str();

        // Check for empty string
        if (strlen(input) == 0) {
            printf("%s", error_message);
            free(input);
            continue;
        }
        // Check for negative signs
        if (input[0] == '-') {
            isNegative = true;
            // If num is negative, check for size to be 2 |__| or digits is more than 11 continue against int overflow
            if (strlen(input) < 2 || strlen(input) > 11) {
                printf("%s", error_message);
                free(input);
                continue;
            }
        } else if (strlen(input) > 10) { //Since int is positive, if greeater than 10 digits, continue or else int overflow will occur
            printf("%s", error_message);
            free(input);
            continue;
        }

        // If negative, skip ascii check for first char
        unsigned int i = 0;
        if (isNegative)
            i = 1;
        // Check for invaild characters in input
        for (; i < strlen(input); i++) {
            if (input[i] > '9' || input[i] < '0') {
                printf("%s", error_message);
                success = false;
                free(input);
                break;
            }
            success = true;
        }

        //Last check for int overflow. Check every int to make sure it is not > 2^31 -1
        if (strlen(input) >= 10) {
            const char int_max[] = "2147483647";
            const int int_max_size = 11;
            i = 0;
            if (isNegative)
                i = 1;

            int j = 0; 
            for (; i < int_max_size; i++) {
                if (input[i] > int_max[j]) {
                    printf("%s", error_message);
                    free(input);
                    success = false;
                    break;
                }
                j++;
            }
        }  
    }

    int num = atoi(input);
    free(input);
    return num;
}

char get_yes_or_no(const char* prompt) {
    char choice = 'a';
    while (true) {
        //Get user input for y or n
        printf("%s", prompt);
        char* response = get_str();
        //If response is > 1 letter, output error message
        if (strlen(response) > 1) {
            printf("You must type a letter of size 1 (y/n)\n");
            free(response);
            continue;
        }

        //Convert str into char 
        choice = response[0];
        choice = tolower(choice);
        free(response);

        //Check to ensure char is y or n
        if (choice == 'y' || choice == 'n') {
            return choice;
        }
        else
            printf("You must type y or n as your response\n");
    }
 
}

bool invaild_char_in_str(const char* input, const char* invaild_input) {
    for (int i = 0; i < strlen(input); i++) {
        for (int j = 0; j < strlen(invaild_input); j++) {
            if (input[i] == invaild_input[j]) {
                return true;
            }
        }
    }
    return false;
}

char* get_str_without_char(const char* prompt, const char* invaild_chars) {
    char* name = "";
    while (true) {
        printf("%s", prompt);
        name = get_str();
        if (name != "\0" && !invaild_char_in_str(name, invaild_chars)) {
            break;
        }
        else {
            printf("Invaild char in name or name is blank. Try again\n");
            free(name);
        }
    }
    return name;
}