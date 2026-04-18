/*
    File: player.h
    Authors: Braian Halas, Dharm Barot
    Purpose: Header file for player.c
    Date: 04/08/2026

*/

#ifndef PLAYER_H
#define PLAYER_H

#include "profile.h"
#include "card.h"

#define MAX_PLAYERS 5

typedef struct {
    UserProfile *profile; // Human player links to profile
    int chips;            // In-game chips
    Card hand[2];         // Hole cards
    int is_human;         // 1=human, 0=AI
    int is_folded;        // Folded status
    int current_bet;      // Current bet
} GamePlayer;

/*
    Function: initGamePlayers
    Purpose: Initializes players for a game round
    Arguments:
        players - GamePlayer struct array to store the players
        human_profile - UserProfile to pass the profile of the user
    Returns:
        None
*/

void initGamePlayers(GamePlayer players[], UserProfile *human_profile);

/*
    Function: resetGamePlayers
    Purpose: Reset players' in-game state
    Arguments:
        players - GamePlayer struct array to store the players
    Returns:
        None
*/

void resetGamePlayers(GamePlayer players[]);

#endif
