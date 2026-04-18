/*
    File: utils.c
    Authors: Stav Shaham, Brian Halas, Dharm Barot
    Purpose: Keep all important and repeated functions
    Date: 03/06/2026
*/

#include "utils.h"
#include <stdio.h>

/*
    Function: clearBuffer
    Purpose: Clears the buffer from invalid input
    Arguments:
        None
    Returns:
        None
*/

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
    Function: removeNewLine
    Purpose: Removes the new line character from a string
    Arguments:
        str - a char array to remove the new line character from
        len - the length of the string
    returns:
        None
*/

void removeNewLine(char* str, int len) {
    int i = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            return;
        }
    }
}

/*
    Function: containsSpace
    Purpose: Checks if a string contains spaces
    Arguments:
        str - a char array to check the spaces
        len - the length of tehe string
    returns:
        An integer, 0 = false, 1 = true
*/

int containsSpace(char* str, int len) {
    int i = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            return 1;
        }
    }

    return 0;
}

/*
    Function: equalStrings
    Purpose: Checks if two strings are the same string
    Arguments:
        str1 - a char array of the first string
        str2 - a char array of the second string
    Returns:
        An integer, 0 = false, 1 = true
*/

int equalStrings(const char* str1, const char* str2) {
    while (*str1 == *str2 && *str1 != '\0') {
        str1++;
        str2++;
    }

    return (*str1 == '\0' && *str2 == '\0');
}

/*
    Function: copyString
    Purpose: Copies a string from another string
    Arguments:
        destination - the char array to copy the string to
        str - the string to copy
    Returns:
        None
*/

void copyString(char* destination, char* str) {
    sprintf(destination, "%s", str);
}
