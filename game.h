/*
    File: game.h
    Authors: Dharm Barot
    Purpose: Header file for the game.c file
    Date: 02/25/2026
*/

#ifndef GAME_H
#define GAME_H

#include "card.h"

#define PLAYER_CARDS 2
#define TABLE_PLAYERS 4
#define TABLE_CARDS 52;

typedef struct {
    int money;
    Card* cards[2];
} Player;

typedef struct {
    int Pot;
    Player players[TABLE_PLAYERS];
    Card cards[TABLE_CARDS];
    int small_blind
    int big_blind;    
} Table;

/* Function prototypes */
*Card generateDeck();
void shuffleDeck(Card* deck, int size);
Card dealCard(Card* deck, int* top);

#endif
