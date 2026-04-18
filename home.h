/*
    File: Home.h
    Author: Braian Halas, Dharm Barot
    Purpose: Header file for home.c
    Date: 03/25/2026
*/

#ifndef HOME_C
#define HOME_C

#include "player.h"
#include "profile.h"

/* Function prototypes */

/*
    Function: initializePlayers
    Purpose: Creates an array of 5 players (1 human, 4 AI) and initializes their chips and status

    Arguments:
        human - User struct for the human player

    Returns:
        None (modifies the players array)
*/

void initializePlayers(GamePlayer players[], UserProfile* human);

/*
    Function: getGameScreen
    Purpose: This function manages the users next choice after login, can be see his stats, or play a game, or exit

    Arguments:
        human - UserProfile struct

    Returns:
        int - the result of the choice
*/

int getHomeScreen(UserProfile* human);


#endif
