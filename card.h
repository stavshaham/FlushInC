/*
    File: card.h
    Author: Braian Halas
    Purpose: Keep the card struct, no C file is needed
    Date: 03/25/2026
*/

#ifndef CARD_H
#define CARD_H

/* Structs */

/*
	Struct: Card
	Purpose: Hold the card data
*/

typedef struct {
    int value;
    char* suit;
} Card;

#endif
