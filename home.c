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
#include "player.h"
#include "utils.h"
#include "stats.c"

/*
    Function: initializePlayers
    Purpose: Creates an array of 5 players (1 human, 4 AI) and initializes their chips and status

    Arguments:
        human - User struct for the human player
    
    Returns:
        None (modifies the players array)
*/

void initializePlayers(GamePlayer players[], UserProfile* human) {
    printf("Initializing players...\n");
    int i = 0;
    for (i = 0; i < MAX_PLAYERS; i++) {
        printf("%d\n", i);
        if (i == 0) {
            // First player is human
            printf("%d\n", human->total_chips);
            players[i].is_human = 1;
            players[i].is_folded = 0;
            players[i].chips = human->total_chips;
            players[i].profile = human;      // link to user profile for updating stats
        } else {
            // AI players
            players[i].is_human = 0;
            players[i].is_folded = 0;
            players[i].chips = 1000 + (rand() % 4000); // give AI random chips
            players[i].profile = NULL; // no history tracking for AI
        }
        players[i].current_bet = 0;
    }

    printf("Done with initializing players \n");
}

/*
    Function: getGameScreen
    Purpose: This function manages the users next choice after login, can be see his stats, or play a game, or exit

    Arguments:
        human - UserProfile struct
    
    Returns:
        int - the result of the choice
*/

int getHomeScreen(UserProfile* human) {
    int choice = 0;
    int running = 1;

    while (running) {

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
                ;
                GamePlayer players[MAX_PLAYERS];
                initializePlayers(players, human);
                startGame(players);
                break;

            case 2:
                showStats(human);
                break;

            case 3:
                printf("Back to main menu \n");
                running = 0;
                break;
        }
    }

    return choice;
}
