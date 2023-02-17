#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

typedef enum {
    NEW_ERROR = 1,
    ALL_ERRORS,
    CLEAN,
    FINISH
} MENU_OPTIONS;

const char* LOGS_FOLDER = "logs/";

/**
 * @brief Request employee identity from stdin. Employee ID must be a four digit long.
 * 
 * @return int : Four digit long employee number.
 */
int request_identity();

/**
 * @brief Calculates today's date and create a log file with that date
 * in the folder LOGS_FOLDER
 * 
 * @return int : 1 if everything went well, 0 if an error occurs when creating the file
 */
int create_today_log_file();

/**
 * @brief Display operator's menu and returns the selected option
 * 
 * @return int : selected option [1,4]
 */
int display_menu();

// MAIN
int main() {
    // Employee ID
    int id = request_identity();
    printf("Employee ID: %d\n", id);

    int file_created_flag = create_today_log_file();
    if (!file_created_flag) {
        printf("Error creating log file, exiting...\n");
        exit(1);
    }

    MENU_OPTIONS option = (MENU_OPTIONS) display_menu();
    switch (option) {
    case NEW_ERROR:
        printf("new error\n");
        break;
    case ALL_ERRORS:
        printf("all errors\n");
        break;
    case CLEAN:
        printf("clean\n");
        break;
    case FINISH:
        printf("finish\n");
    default:
        break;
    }
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

int create_log_directory() {
    int success = 1;
    if (mkdir(LOGS_FOLDER, 0777) == -1) {
        if (errno != EEXIST)
            success = 0;
    }
    return success;
}

int create_today_log_file() {
    int success = 1;

    // Compute date
    time_t timestamp = time(NULL);
    struct tm* date_tm = localtime(&timestamp);
    char date[15];
    strftime(date, sizeof(date), "%Y-%m-%d", date_tm);

    // Create log directory and return if fail
    int dir_created_flag = create_log_directory();
    if (dir_created_flag) {
        // Create new log file
        int success = 1;
        char filename[40];
        strcpy(filename, LOGS_FOLDER);
        strcat(filename, date);
        FILE* file = fopen(filename, "a");

        if (file == NULL)
            success = 0;
        
        fclose(file);
    } else {
        success = 0;
    }
    return success;
}

int display_menu() {
    int option;
    char* menu_interface = 
                    "\n\tMENU\n"
                    "1) Add new error.\n"
                    "2) Check error list.\n"
                    "3) Clean errors.\n"
                    "4) Finish workday.\n\n"
                    "Choose option: ";
    printf("%s", menu_interface);
    scanf("%d", &option);
    return option;
}

