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

int main() {
    return EXIT_SUCCESS;
}

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
