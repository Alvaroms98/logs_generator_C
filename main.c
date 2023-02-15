#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief Request employee identity from stdin. Employee ID must be a four digit long.
 * 
 * @return int : Four digit long employee number.
 */
int request_identity();

int main() {
    int id = request_identity();
    printf("Employee ID: %d\n", id);
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