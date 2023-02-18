#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef enum {
    NEW_ERROR = 1,
    ALL_ERRORS,
    CLEAN,
    FINISH
} MENU_OPTIONS;

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

#endif