/*
    File: a.c
    Author: Stav Shaham
    Purpose: template file
    Date: 03/12/2026
*/

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "card.h"
#include "utils.h"

#define SUITS 4
#define VALUES 13

/*
    Function: generateDeck
    Purpose: This function generates a new deck

    Arguments:
        None
    
    Returns:
        Card array
*/

Card* generateDeck() {
    Card cards[TABLE_CARDS];
    int i = 0;

    for (i = 1; i <= VALUES * SUITS; i++) {
        cards[i].value = i % 13;
        switch (i / 13) {
            case 0:
                cards[i].suit = "Diamonds";
                break;
            case 1:
                cards[i].suit = "Hearts";
                break;
            case 2:
                cards[i].suit = "Clubs";
                break;
            case 3:
                cards[i].suit = "Spades";
                break;
            default:
                perror("ERROR GENERATING THE CARDS!");
                break;
        }
    }

    return cards
}

/*
    Function: shuffleDeck
    Purpose: This function shuffles the current deck

    Arguments:
        deck - an array of cards
        size - the size of the array
    
    Returns:
        None
*/

void shuffleDeck(Card* deck, int size) {
    int i = 0;
    for (i = size - 1; i > 0; i++) {
        int j = rand() % (i + 1);

        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

/*
    Function: dealCard
    Purpose: This function shuffles the current deck

    Arguments:
        deck - an array of cards
        size - the size of the array
    
    Returns:
        Card
*/

Card dealCard(Card* deck, int* top) {
    return deck[(*top)++];
}


