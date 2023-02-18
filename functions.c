#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#include "functions.h"

const char* LOGS_FOLDER = "logs/";
char FILENAME[40];

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
        // Creates a backup copy before deleting content
        char filename_backup[50];
        strcpy(filename_backup, FILENAME);
        strcat(filename_backup, "_backup");

        // Read all data and write in the backup
        FILE* f = fopen(FILENAME, "r");
        FILE* f_backup = fopen(filename_backup, "w");
        char c;
        while ((c = fgetc(f)) != EOF) {
            fprintf(f_backup, "%c", c);
        }
        fclose(f);
        fclose(f_backup);
        
        // Clear current logs
        FILE* file = fopen(FILENAME, "w");
        fclose(file);
    }
}
