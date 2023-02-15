#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/**
 * @brief Request employee identity from stdin. Employee ID must be a four digit long.
 * 
 * @return int : Four digit long employee number.
 */
int request_identity();

/**
 * @brief Returns today's date with the format YYYY-MM-DD.
 * 
 * @param date char*: pointer to store string date.
 * @param length int: length of the char array.
 */
void today_date(char* date, int length);


// MAIN
int main() {
    // Employee ID
    int id = request_identity();
    printf("Employee ID: %d\n", id);

    // Today's date
    char date[15];
    today_date(date, sizeof(date));
    printf("Today's date: %s\n", date);

    return 0;
}

int request_identity() {
    char id_string[20];
    int id = 0;
    printf("Enter employee number: ");
    scanf("%s", id_string);
    int i = 0;
    int x = 3;
    while(id_string[i]) {
        int tmp = (int)(id_string[i] - '0');
        int factor = x - i;
        id += tmp*pow(10, factor);
        i++;
    }
    if (i != 4) {
        printf("ID not valid, exiting...\n");
        exit(1);
    }
    return id;
}

void today_date(char* date, int length) {
    time_t timestamp = time(NULL);
    struct tm* date_tm = localtime(&timestamp);
    strftime(date, length, "%Y-%m-%d", date_tm);
}

