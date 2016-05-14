//
//  main.c
//  5-8
//
//  Created by Xueyong Qian on 21/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day)
{
    int i, leap;
    if (year < 1) {
        printf("day_of_year: illegal year value:%d!\n", year);
        exit(EXIT_FAILURE);
    }
    if (month < 1 || month > 12) {
        printf("day_of_year: illegal month value:%d\n", month);
        exit(EXIT_FAILURE);
    }
    if (day < 1 || day > 31) {
        printf("day_of_year: illegal day value:%d\n", day);
        exit(EXIT_FAILURE);
    }
    leap = year % 4 == 0 && year %100 != 0 || year %400 == 0;
    for (i=1; i<month; ++i) {
        day += daytab[leap][i];
    }
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    
    if (year < 1) {
        printf("month_day: illegal year value:%d!\n", year);
        exit(EXIT_FAILURE);
    }
    if (yearday < 1 || yearday > 366) {
        printf("month_day:illegal day value:%d\n", yearday);
        exit(EXIT_FAILURE);
    }
    leap = year % 4 == 0 && year %100 != 0 || year %400 == 0;
    for (i = 1; yearday > daytab[leap][i]; ++i) {
        yearday -= daytab[leap][i];
    }
    *pmonth = i;
    *pday = yearday;
}
int main(int argc, const char * argv[])
{

    printf("day of year:%d\n", day_of_year(1990, 32, 24));
    return 0;
}

