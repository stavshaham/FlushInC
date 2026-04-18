/*
    File: auth.c
    Author: Stav Shaham, Braian Halas, Dharm Barot
    Purpose: Access all auth function on a different file.
             Part of CS125 Final Project
    Date: 03/06/2026
*/

#include <stdio.h>
#include <stdlib.h>
#include "auth.h"
#include "utils.h"

/* Functions */

/*
    Function: getAuthType
    Purpose: Decides if the user wants to log in, register, or exit the program
    Arguments:
        None
    Returns:
        An integer, the choice of the user
*/

int getAuthType() {
    int choice;

    /* Prompt the user to enter a valid auth option */
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

/*
    Function: loginUser
    Purpose: Asks the user to put his user credentials and login
    Arguments:
        None
    Returns:
        An integer, 1 = successfull, 0 = faild
*/

int loginUser(char* user) {
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


	// Checks if the username matches the password saved
    while (fscanf(f, "%s %s", username, password) == 2) {
        if (equalStrings(username, username_input)) {
            if (equalStrings(password, password_input)) {
                fclose(f);
                copyString(user, username);
                printf("%s\n", user); 
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

/*
    Function: registerUser
    Purpose: Asks the user to create a new username and password
    Arguments:
        None
    Returns:
        An integer, 1 = successfull, 0 = faild
*/

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
    
    /* Format: username chips handsWon handsLost */
    fprintf(f, "%s %d %d %d\n", username_input, 10000, 0, 0);
    fclose(f);

    return 1;
}

/*
    Function: usernameExists
    Purpose: Checks if a username already exists
    Arguments:
        str - a char array of the username
        len - the length of the char array
    Returns:
        An integer, 1 = found, 0 = not found
*/

int usernameExists(const char* username, int len) {
    char f_username[SIZE];
    char f_password[SIZE];
    FILE* f = fopen("users.txt", "r");
    
    if (f == NULL) {
        return 0;
    }

    while (fscanf(f, "%s %s", f_username, f_password) == 2) {
        if (equalStrings(f_username, username)) {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}
