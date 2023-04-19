#include "../include/time_time.h"

Date get_current_date() {
    time_t current_time = time(NULL); //Get current unix_time
    struct tm tm = *localtime(&current_time); //Get localtime

    //Fix tm times
    tm.tm_mon++;
    tm.tm_year += 1900;

    return (Date) {tm.tm_mon, tm.tm_mday, tm.tm_year};
}

char* get_current_date_str() {
    Date current_time = get_current_date();
    char* date_str = (char*)calloc(100, sizeof(char));

    sprintf(date_str, "%d/%d/%d", current_time.month, current_time.day, current_time.year);
    return date_str;
}
Date get_current_age(char* DOB) {
    //DOB = XX-XX-XXXX
    //Code from https://www.geeksforgeeks.org/program-calculate-age/

    //Get current date
    Date current = get_current_date();

    //Convert str to ints
    const char month_str[] = {DOB[0], DOB[1], '\0'};
    const char day_str[] = {DOB[3], DOB[4], '\0'};
    const char year_str[] = {DOB[6], DOB[7], DOB[8], DOB[9], '\0'};

    Date birth = (Date) {atoi(month_str), atoi(day_str), atoi(year_str)};

    int month[] = { 31, 28, 31, 30, 31, 30,
                    31, 31, 30, 31, 30, 31 };

    if (birth.day > current.day) {
        current.day = month[birth.month - 1];
        current.month--;
    }

    if (birth.month > current.month) {
        current.year--;
        current.month += 12;
    }

    return (Date) {current.month - birth.month, current.day - birth.day, current.year - birth.year};
}