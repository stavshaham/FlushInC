/*
    File: stats.c
    Author: Braian Halas, Dharm Barot
    Purpose: show the players' stats
    Date: 04/15/2026
*/

#include <stdio.h>
#include <stdlib.h>
#include "profile.h"

/*
    Function: showStats
    Purpose: To show the players' stats
    Arguments:
        profile - the profile to show the stats
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
