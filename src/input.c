#include "../include/input.h"

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

bool check_for_ints(char* input, int x, int y) {
    for (int i = 0; i < strlen(input); i++) {
        if (i != x && i != y) {
            if (!isdigit(input[i])) {
                free(input);
                printf("Invaild char in input str\n");
                return true;
            }
        }
    } 
    return false;
}

time_t convert_time_to_unix_time(int month, int day, int year) {
    return (31556926 * (year - 1970)) + (86400 * (day - 1)) + (2629743 * (month - 1)); 
}

bool check_DOB_date(const char* DOB) {
    //Convert big str to small str
    const char month_str[] = {DOB[0], DOB[1], '\0'};
    const char day_str[] = {DOB[3], DOB[4], '\0'};
    const char year_str[] = {DOB[6], DOB[7], DOB[8], DOB[9], '\0'};

    //Convert str to int
    int month = atoi(month_str), day = atoi(day_str), year = atoi(year_str);

    //Check to ensure time isn't greater than current time
    int current_time = time(NULL);
    const time_t u_time = convert_time_to_unix_time(month, day, year);

    if (u_time > current_time) {
        return false;
    }

    //check year
    if(year >= 1900 && year <= 9999) {
        //check month
        if(month >= 1 && month <= 12) {
            //check days
            if((day >= 1 && day <= 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month ==8 || month == 10 || month == 12))
                return true;
            else if((day >= 1 && day <= 30) && (month == 4 || month == 6 || month == 9 || month == 11))
                return true;
            else if((day >= 1 && day <= 28) && (month == 2))
                return true;
            else if(day == 29 && month == 2 && (year % 400 == 0 ||(year % 4== 0  && year % 100 != 0)))
                return true;
            else
                return false;
            }
        else {
            return false;
        }
    }
    else {
        return false;
    }

}

char* get_DOB() {
    char* DOB = "";
    while (true) {
        printf("Type in date of birth in XX/XX/XXXX format: ");
        DOB = get_str();


        //Check if DOB is 10 char long
        if (strlen(DOB) != 10) {
            printf("Date provided must be exaclty 10 char long. Invaild format\n");
            free(DOB);
            continue;
        }

        //Check if DOB has / in the right places
        if (DOB[2] != '/' || DOB[5] != '/') {
            printf("Char '/' not found in the right places. Invaild format\n");
            free(DOB);
            continue;
        }

        //Check for digits in DOB
        if (check_for_ints(DOB, 2, 5))
            continue;

        if (!check_DOB_date(DOB)) {
            printf("The date is invaild\n");
            free(DOB);
            continue;
        }

        return DOB;
    }
}

char* get_SSN() {
    char* SSN = "";
    while (true) {
        printf("Please type in your SSN in XXX-XX-XXXX format: ");
        SSN = get_str();

        //Check SSN size, must be 11
        if (strlen(SSN) != 11) {
            printf("SSN must have 9 digits and 2 dashes\n");
            free(SSN);
            continue;
        }

        if (SSN[3] != '-' || SSN[6] != '-') {
            printf("You must type in SSN as XXX-XX-XXXX format\n");
            free(SSN);
            continue;
        }

        if (check_for_ints(SSN, 3, 6)) {
            continue;
        }
        return SSN;
    }

}

bool is_state_vaild(char* input) {
    char state_abbv[][3] = {"AK","AL","AR","AS","AZ","CA","CO","CT","DC",
    "DE","FL","GA","GU","HI","IA","ID","IL","IN","KS","KY","LA","MA","MD",
    "ME","MI","MN","MO","MS","MT","NC","ND","NE","NH","NJ","NM","NV","NY",
    "OH","OK","OR","PA","PR","RI","SC","SD","TN","TX","UT","VA","VI","VT",
    "WA","WI","WV","WY"};
    const int number_of_states = 55;

    if (strlen(input) != 2) {
        return false;
    }

    input[0] = toupper(input[0]);
    input[1] = toupper(input[1]);

    for (int i = 0; i < number_of_states; i++) {
        if (strcmp(state_abbv[i], input) == 0)
            return true;
    }
    return false;
}

char* get_address() {
    char* street_address = "";
    char* city = "", *state = "";
    int zip_code = -1;

    //Get Street Address 
    printf("What is your street_address: ");
    street_address = get_str();

    //Get City
    printf("What is your city: ");
    city = get_str();

    //Get State Abbv.
    while (true) {
        printf("What is your state abbreviation (Ex. NJ): ");
        state = get_str();
        if (!is_state_vaild(state)) {
            printf("Invaild State. Try again\n");
            free(state);
        }
        else {
            break;
        }
    }

    //Get zip_code
    while (true) {
        printf("What is your zip code: ");
        zip_code = get_int("Invaild Number\nWhat is your zip code: ");
        if (zip_code < 0 || zip_code > 99999)
            printf("Invaild zip code. Range is 00000-99999\n");
        else
            break;
    }


    //Combine all strings into one
    //street_add size + space + city size + space + comma + zip code + null
    //+4 for spaces, commas, null, +5 for zip code
    size_t new_str_len = strlen(city) + strlen(street_address) + strlen(state) + 10;
    char* address = (char*)malloc(sizeof(char) * new_str_len);

    sprintf(address, "%s %s, %s %05d", street_address, city, state, zip_code);

    printf("You live in %s\n", address);
    free(city);
    free(street_address);
    free(state); 

    return address;
}

char* get_phone_number() {
    //
    char* phone_num = "";
    while (true) {
        printf("Type in your phone number in XXX-XXX-XXXX format: ");
        phone_num = get_str();

        if (strlen(phone_num) != 12 || phone_num[3] != '-' || phone_num[7] != '-') {
            printf("Phone number must have 10 digits and 2 dashes in XXX-XXX-XXXX format\n");
            free(phone_num);
            continue;
        }

        if (check_for_ints(phone_num, 3, 7)) {
            continue;
        }

        return phone_num;
    }
}