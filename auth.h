/* 
    File: auth.h
    Authors: Dharm Barot and Braian Halas
    Purpose: Header file for auth.c
    Date: 03/25/2026
*/

#ifndef AUTH_H
#define AUTH_H

#define SIZE 50

typedef struct {
    char username[SIZE];
    int chips;
} User;

/* Function prototypes */

/*
    Function: getAuthType
    Purpose: Decides if the user wants to log in, register, or exit the program
    Arguments:
        None
    Returns:
        An integer, the choice of the user
*/

int getAuthType();

/*
    Function: loginUser
    Purpose: Asks the user to put his user credentials and login
    Arguments:
        None    
    Returns:
        An integer, 1 = successfull, 0 = faild
*/

int loginUser();

/*
    Function: registerUser
    Purpose: Asks the user to create a new username and password
    Arguments:
        None
    Returns:
        An integer, 1 = successfull, 0 = faild
*/

int registerUser();

/*
    Function: usernameExists
    Purpose: Checks if a username already exists
    Arguments:
        str - a char array of the username
        len - the length of the char array
    Returns:
        An integer, 1 = found, 0 = not found   
*/

int usernameExists(const char* str, int len);

#endif
