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
    Purpose: Initializes all game players, linking human to profile and creating AI
    Arguments:
        players - array of GamePlayer structs
        human_profile - pointer to human profile
    Returns:
        void
*/
void initGamePlayers(GamePlayer players[], UserProfile *human_profile);

/* 
    Function: resetGamePlayers
    Purpose: Resets all players' in-game state for a new round
    Arguments:
        players - array of GamePlayer structs
    Returns:
        void
*/
void resetGamePlayers(GamePlayer players[]);

#endif
