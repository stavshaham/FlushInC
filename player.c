/*
    File: player.c
    Author: Stav Shaham
    Purpose: Implements initialization and reset functions for in-game players
    Date: 04/08/2026
*/

#include <stdio.h>
#include <stdlib.h>
#include "player.h"

/*
	Function: initGamePlayers
	Purpose: Initializes players for a game round
	Arguments:
		players - GamePlayer struct array to store the players
		human_profile - UserProfile to pass the profile of the user
	Returns:
		None
*/

void initGamePlayers(GamePlayer players[], UserProfile* human_profile) {
    int i = 0;

    /* Human player */
    players[0].profile = human_profile;
    if (human_profile->total_chips == 0) {
        human_profile->total_chips = 10000;
    }
    players[0].chips = human_profile->total_chips;
    players[0].is_human = 1;
    players[0].is_folded = 0;
    players[0].current_bet = 0;

    /* AI players */
    for (i = 1;i < MAX_PLAYERS; i++) {
        players[i].profile = NULL;
        players[i].chips = human_profile->total_chips;
        players[i].is_human = 0;
        players[i].is_folded = 0;
        players[i].current_bet = 0;
    }
}

/*
	Function: resetGamePlayers
	Purpose: Reset players' in-game state
	Arguments:
		players - GamePlayer struct array to store the players
	Returns:
		None
*/

void resetGamePlayers(GamePlayer players[]) {
    int i = 0;
    for (i = 0; i < MAX_PLAYERS; i++) {
        players[i].is_folded = 0;
        players[i].current_bet = 0;
        if (!players[i].is_human && players[i].chips == 0) {
            players[i].chips=1000;
        }
    }
}
