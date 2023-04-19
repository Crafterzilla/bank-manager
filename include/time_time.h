#ifndef TIME_TIME_H
#define TIME_TIME_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Date {
    int month;
    int day;
    int year;
} Date;

Date get_current_date();
Date get_current_age(char* DOB);
char* get_current_date_str();

#endif