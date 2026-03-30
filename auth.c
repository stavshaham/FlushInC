/*
    File: auth.c
    Author: Stav Shaham
    Purpose: Access all auth function on a different file.
             Part of CS125 Final Project
    Date: 03/06/2026
*/

#include <stdio.h>
#include <stdlib.h>
#include "auth.h"
#include "utils.h"

/* Functions */

int getAuthType() {
    int choice;

    /* Prompt the user to enter a valid auth option" */
    printf("Choose an action from the following: \n");
    printf(" - Login (1) \n");
    printf(" - Register (2)\n");
    printf(" - Exit (3) \n");


    while (scanf("%d", &choice) <= 0 || choice < 1 || choice > 3) {
        clearBuffer();
        printf("Please enter a valid number: \n");
        printf(" - Login (1) \n");
        printf(" - Register (2)\n");
        printf(" - Exit (3) \n");
    }

    clearBuffer();

    return choice;
}

int loginUser() {
    /* TODO: check if username exists, if so check if it fits the password, return 1 if success, return 0 if failed. */
    char username_input[SIZE];
    char password_input[SIZE];
    char username[SIZE];
    char password[SIZE];
    FILE* f = fopen("users.txt", "r");

    if (f == NULL) {
        perror("Couldn't access file");
        return 0;
    }

    system("clear");
    printf("Login Dashboard: \n");
    printf("Please enter your username: \n");
    
    fgets(username_input, sizeof(username_input), stdin);
    removeNewLine(username_input, SIZE);

    while (containsSpace(username_input, SIZE)) {
        printf("Please enter a valid username - No spaces allowed! \n");
        printf("Please enter your username: \n");
        fgets(username_input, sizeof(username_input), stdin);
        removeNewLine(username_input, SIZE);
    }

    printf("Please enter your password: \n");
    
    system("stty -echo");
    fgets(password_input, sizeof(password_input), stdin);
    system("stty echo");
    printf("\n");
    removeNewLine(password_input, SIZE);
    
    while (fscanf(f, "%s %s", username, password) == 2) {
        if (equalsStrings(username, username_input)) {
            if (equalsStrings(password, password_input)) {
                fclose(f);
                printf("Login successfully \n");
                return 1;
            } else {
                fclose(f);
                printf("Password does not match our information. \n");
                return 0;
            }
        }
    }

    printf("The entered username does not exists.\n");
    fclose(f);
    return 0;
}

int registerUser() {
    /* TODO: check if username is available, is so, create the new user and return 1, if not, return 0; */
    char username_input[SIZE];
    char password_input[SIZE];
    FILE* f = fopen("users.txt", "a");

    if (f == NULL) {
        f = fopen("users.txt", "w");
        perror("Couldn't access file");
        return 0;
    }

    system("clear");
    printf("Register Dashboard: \n");
    printf("Please enter a username: \n");
   
    fgets(username_input, sizeof(username_input), stdin);
    removeNewLine(username_input, SIZE);

    while (containsSpace(username_input, SIZE)) {
        printf("Please enter a valid username - No spaces allowed! \n");
        printf("Please enter your username: ");
        fgets(username_input, sizeof(username_input), stdin);
        removeNewLine(username_input, SIZE);
    }

    while (usernameExists(username_input, SIZE)) {
        clearBuffer();
        printf("Username already exists, please enter a new username: \n");
        fgets(username_input, sizeof(username_input), stdin);
        removeNewLine(username_input, SIZE);
    }

    printf("Enter your password: \n");

    fgets(password_input, sizeof(password_input), stdin);
    removeNewLine(password_input, SIZE);

    fprintf(f, "%s %s\n", username_input, password_input);
    printf("Username has been successfully registered! \n");

    fclose(f);

    f = fopen("user_data.txt", "a");
    
    if (f == NULL) {
        perror("Couldn't access file");
        return 0;
    }
    
    /* Format: username chips hands_won hands_lost */
    fprintf(f, "%s %d %d %d", username_input, 10000, 0, 0);
    fclose(f);

    return 1;
}

int usernameExists(const char* username, int len) {
    char f_username[SIZE];
    char f_password[SIZE];
    FILE* f = fopen("users.txt", "r");
    
    if (f == NULL) {
        return 0;
    }

    while (fscanf(f, "%s %s", f_username, f_password) == 2) {
        if (equalsStrings(f_username, username)) {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

User getUserData(char* username) {
    User currentUser;

    return currentUser;
}
