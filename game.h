/*
    File: game.h
    Authors: Dharm Barot
    Purpose: Header file for the game.c file
    Date: 04/10/2026
*/

#ifndef GAME_H
#define GAME_H

#include "player.h"

#define PLAYER_CARDS 2
#define TABLE_CARDS 52
#define VALUES 13
#define SUITS 4
#define HIGH_CARD 1
#define ONE_PAIR 2
#define TWO_PAIR 3
#define THREE_OF_A_KIND 4
#define STRAIGHT 5
#define FLUSH 6
#define FULL_HOUSE 7
#define FOUR_OF_A_KIND 8
#define STRAIGHT_FLUSH 9
#define ROYAL_FLUSH 10

/* Structs */

/* 
    Struct: Table
    Purpose: Keep the table information 
*/ 

typedef struct {
    int pot;
    int small_blind;
    int big_blind;
    Card community[5];
} Table;

/*
    Struct: HandValue
    Purpose: To keep the value of the hand
*/

typedef struct {
    int rank;
    int tiebreak[5];
} HandValue;

/* 
    Function: generateDeck
    Purpose: Generates a new ordered deck of 52 cards
    Arguments:
        deck - array to fill with Card structs
        size - deck size (should be 52)
    Returns:
        void
*/

void generateDeck(Card *deck, int size);

/* 
    Function: shuffleDeck
    Purpose: Shuffles the current deck using Fisher-Yates algorithm
    Arguments:
        deck - array of Card structs
        size - size of deck
    Returns:
        void
*/

void shuffleDeck(Card *deck, int size);

/* 
    Function: dealCard
    Purpose: Deals a single card from the top of the deck
    Arguments:
        deck - array of Card structs
        top - pointer to top card index
    Returns:
        Card struct
*/

Card dealCard(Card *deck, int *top);

/* 
    Function: aiBets
    Purpose: Makes the AI bet
    Arguments:
        ai - GamePlayer struct
        highestBet - the current highest bet
        community - the cards on the table, a Card array
        stage - an int to show the current stage (pre-flop/flop/turn/river)
    Returns:
        the ai bet
*/

int aiBet(GamePlayer *ai, int highestBet, Card community[5], int stage);

/* 
    Function: humanBet
    Purpose: Allows the human player to make a bet
    Arguments:
        player - GamePlayer struct
        highestBet - the current highest bet
    Returns:
        the human bet
*/

int humanBet(GamePlayer *player, int highestBet);

/*
    Function: bettingRound
    Purpose: Sets up all the betting rounds
    Arguments:
        players - array of GamePlayer structs
        pot - a pointer to the por
        community - the cards on the table, a Card array
        stage - an int to show the current stage (pre-flop/flop/turn/river)
    Returns:
        void
*/

int bettingRound(GamePlayer players[], int *pot, Card community[5], int stage);

/* 
    Function: startGame
    Purpose: Initializes and starts a poker game round
    Arguments:
        players - array of GamePlayer structs
    Returns:
        void
*/

void startGame(GamePlayer players[]);

/*
    Function: rankHand
    Purpose: Ranks the hand of a given player
    Arguments:
        hand - the hand of the player, a Card array
        community - the cards on the table, a Card array
    Returns:
        void
*/

HandValue rankHand(Card hand[2], Card community[5]);

/*
    Function: evaluateHands
    Purpose: This function decides the winner, evaluates all hands
    Arguments:
        players - GamePlayer struct
        numPlayers - the number of players that did not fold
        community - the cards on the table, a Card array
    Returns:
        the winner
*/

int evaluateHands(GamePlayer players[], int numPlayers, Card community[5]);

/*
    Function: compareHands
    Purpose: Compares two hands and decides the better hand
    Arguments:
        h1 - the hand of the player, a Card array
        h2 - the hand of the player, a Card array
    Returns:
        the better hand
*/

int compareHands(HandValue h1, HandValue h2);

/* 
    Function: showHand
    Purpose: Shows the player's hand, prints it
    Arguments:
        player - GamePlayer structs
    Returns:
        void
*/

void showHand(GamePlayer *player, int i);

/* 
    Function: getSuitSymbol
    Purpose: Gets the symbols of the cards
    Arguments:
        players - array of GamePlayer structs
        i - the AI number
    Returns:
        char*
*/

const char* getSuitSymbol(char *suit);

/* 
    Function: printBoard
    Purpose: Prints the current board
    Arguments:
        community - the cards on the table, a Card array.
        count - an integer to set the current cards available
    Returns:
        void
*/

void printBoard(Card community[], int count);

/* 
    Function: evaluateSimpleStrength
    Purpose: Evaluates the AI hands to make smarter decisions
    Arguments:
        hand - the AI hand, Card array
        community - the cards on the table, a Card array
        stage - an int to show the current stage (pre-flop/flop/turn/river)
    Returns:
        void
*/

int evaluateSimpleStrength(Card hand[2], Card community[5], int stage);

/* 
    Function: rankHand
    Purpose: Evaluates the hand's rank
    Arguments:
        hand - the player's hand, Card array
        community - the cards on the table, a Card array
        stage - an int to show the current stage (pre-flop/flop/turn/river)
    Returns:
        void
*/

int evaluateSimpleStrength(Card hand[2], Card community[5], int stage);

/* 
    Function: getCardValueString
    Purpose: Converts the number from a number to a string to use A/J/Q/K
    Arguments:
        value - the integer value of the card
    Returns:
        void
*/

const char* getCardValueString(int value);

#endif
