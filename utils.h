#ifndef UTILS_H
#define UTILS_H

/* Function prototypes */

/*
    Function: clearBuffer
    Purpose: Clears the buffer from invalid input
    Arguments:
        None
    Returns:
        None
*/

void clearBuffer();

/*
    Function: removeNewLine
    Purpose: Removes the new line character from a string
    Arguments:
        str - a char array to remove the new line character from
        len - the length of the string
    returns:
        None
*/

void removeNewLine(char* str, int len);

/*
    Function: containsSpace
    Purpose: Checks if a string contains spaces
    Arguments:
        str - a char array to check the spaces
        len - the length of tehe string
    returns:
        An integer, 0 = false, 1 = true
*/

int containsSpace(char* str, int len);

/*
    Function: equalStrings
    Purpose: Checks if two strings are the same string
    Arguments:
        str1 - a char array of the first string
        str2 - a char array of the second string
    Returns:
        An integer, 0 = false, 1 = true
*/

int equalStrings(const char* str1, const char* str2);

/*
    Function: copyString
    Purpose: Copies a string from another string
    Arguments:
        destination - the char array to copy the string to
        str - the string to copy
    Returns:
        None
*/

void copyString(char* destination, char* str);

#endif
