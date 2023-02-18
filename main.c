#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#include "functions.h"

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

    // Menu loop
    int exit_flag = 0;
    while(!exit_flag) {
        // Clear Menu after every action
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
            exit_flag = 1;
            break;
        default:
            printf("Option not valid, try again...\n");
            break;
        }
    }
    printf("Exiting program...\n");
    return 0;
}
