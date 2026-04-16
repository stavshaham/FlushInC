/*
    File: stats.c
    Author: Braian Halas, Dharm Barot
    Purpose: template file
    Date: 04/15/2026
*/

#include <stdio.h>
#include <stdlib.h>
#include "profile.h"

void a();

/*
    Function: a
    Purpose: a

    Arguments:
        arg1 - a
    
    Returns:
        None
*/

void showStats(UserProfile* profile) {
    system("clear");
    printf("\nPlayer Stats\n");

    printf("Wins: %d\n", profile->wins);
    printf("Losses: %d\n", profile->losses);
    printf("Chips: %d\n", profile->total_chips);
}
