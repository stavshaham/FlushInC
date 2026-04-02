/*
    File: Home.c
    Author: Braian Halas, Dharm Barot
    Purpose: This file is responsible for the home screen
    Date: 03/25/2026
*/

#include <stdio.h>
#include <stdlib.h>
#include "home.h"
#include "game.h"
#include "utils.h"

/*
    Function: getGameScreen
    Purpose: This function manages the users next choice after login, can be see his stats, or play a game, or exit

    Arguments:
        arg1 - a
    
    Returns:
        None
*/

int getHomeScreen() {
    int choice = 0;

    printf("Select an action from the following: \n"); 
    printf(" - Play a game (1) \n"); 
    printf(" - See stats (2) \n"); 
    printf(" - Exit (3) \n"); 
    
    while (scanf("%d", &choice) <= 0 || choice < 1 || choice > 3) {
        clearBuffer();
        printf("Please enter a valid number: \n");
        printf(" - Play a game (1) \n"); 
        printf(" - See stats (2) \n"); 
        printf(" - Exit (3) \n");
    }

    clearBuffer();

    switch (choice) {
        case 1: 
            startGame();
            break;

        case 2:
            /* showStats(); */
            break;

        case 3:
            system("exit");
            break;
    }

    return choice;
}
