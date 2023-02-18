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
char FILENAME[40];

/**
 * @brief Clean stdin buffer until it reads '\n' character
 * 
 */
void clear_stdin();

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

/**
 * @brief Request to the user to insert the error message
 * and write it in the current log file.
 * 
 * @param employee_id Number of the employee submiting the new error.
 */
void add_new_error(int employee_id);

/**
 * @brief Show current log file in the terminal
 * 
 */
void show_current_logs();

/**
 * @brief Deletes current log file and creates again
 * shows to the user a confirmation message.
 * 
 */
void clear_current_logs();

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
        add_new_error(id);
        break;
    case ALL_ERRORS:
        show_current_logs();
        break;
    case CLEAN:
        clear_current_logs();
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
    clear_stdin();
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
        strcpy(FILENAME, LOGS_FOLDER);
        strcat(FILENAME, date);
        FILE* file = fopen(FILENAME, "a");

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
                    "2) Show errors.\n"
                    "3) Clean errors.\n"
                    "4) Finish workday.\n\n"
                    "Choose option: ";
    printf("%s", menu_interface);
    scanf("%d", &option);
    clear_stdin();
    return option;
}

void clear_stdin() {
    while ((getchar()) != '\n');
}

void add_new_error(int employee_id) {
    char err_msg[100];
    char full_msg[150];
    sprintf(full_msg, "[%d]: ", employee_id);
    printf("Write error message: ");
    scanf("%99[^\n]", err_msg);
    clear_stdin();
    strcat(full_msg, err_msg);
    printf("%s", full_msg);

    // Write message in log file
    FILE* file = fopen(FILENAME, "a");
    fprintf(file, "%s\n", full_msg);
    fclose(file);
}

void show_current_logs() {
    printf("\nLogs from file: %s: \n\n", FILENAME);
    char line[200];
    FILE* file = fopen(FILENAME, "r");
    int i = 1;
    while (fgets(line, sizeof(line), file)) {
        printf("%d. %s", i, line);
        i++;
    } 
    fclose(file);
    printf("----------------------------------------\n");
}

void clear_current_logs() {
    printf("Are you sure that you want to clear today's history? [Y/n] ");
    char answer[10];
    scanf("%c", answer);
    if (answer[0] == 'Y' || answer[0] == 'y') {
        FILE* file = fopen(FILENAME, "w");
        fclose(file);
    }
}
