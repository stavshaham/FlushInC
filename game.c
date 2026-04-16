/*
    File: game.c
    Author: Stav Shaham, Braian Halas, Dharm Barot
    Purpose: template file
    Date: 03/12/2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "card.h"
#include "utils.h"

/* Generate a standard 52-card deck */
void generateDeck(Card* cards, int size) {
    int i = 0;
    for (i = 0; i < size; i++) {
        cards[i].value = (i % 13) + 1;
        switch (i / 13){
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
        }
    }
}

/* Shuffle deck using Fisher-Yates */
void shuffleDeck(Card* deck, int size){
    int i = 0;
    int j = 0;
    for (i = size - 1; i > 0; i--){
        j = rand() % (i + 1);
        Card tmp = deck[i];
        deck[i] = deck[j];
        deck[j] = tmp;
    }
}

/* Deal one card from the deck */
Card dealCard(Card* deck, int* top) {
    return deck[(*top)++];
}

/* Simple AI betting logic: fold/call/random raise */
int aiBet(GamePlayer *ai, int highestBet, Card community[5], int stage) {
    if (ai->chips <= 0 || ai->is_folded) {
        return 0;
    }

    int toCall = highestBet - ai->current_bet;
    int strength = evaluateSimpleStrength(ai->hand, community, stage);
    int raise = 0;
    int maxRaise = 0;

    /* thresholds */
    int weak = 25;
    int medium = 40;
    int strong = 55;

    if (toCall < 0) {
        toCall = 0;
    }

    /* 1. FOLD LOGIC */
    if (strength < weak) {
        if (toCall > 20) {
            ai->is_folded = 1;
            printf("AI folds.\n");
            return 0;
        }
        printf("AI calls %d.\n", toCall);
        return toCall;
    }

    /* 2. CALL / CHECK LOGIC */
    if (strength < strong) {
        printf("AI calls %d.\n", toCall);
        return toCall;
    }

    /* 3. RAISE LOGIC */
    raise = (rand() % 50) + 20;

    maxRaise = ai->chips / 3;
    if (raise > maxRaise) {
        raise = maxRaise;
    }

    printf("AI raises %d.\n", toCall + raise);
    return toCall + raise;
}

/* Get human player's bet */
int humanBet(GamePlayer *player, int highestBet) {
    int bet = 0;
    int choice = 0;

    if (player->chips <= 0) return 0;

    int toCall = highestBet - player->current_bet;

    printf("\nYour chips: %d | To call: %d\n", player->chips, toCall);

    if (toCall <= 0) {
        printf("Do you want to (1) Check, (2) Raise, (3) Fold? ");
    } else {
        printf("Do you want to (1) Call, (2) Raise, (3) Fold? ");
    }

    scanf("%d", &choice);
    clearBuffer();

    switch(choice) {
        /*  Call/check */
        case 1:
            bet = toCall;
            if (bet < 0) bet = 0;

            printf("You call %d.\n", bet);
            break;

        /* Raise */
        case 2:
            printf("Enter raise amount: ");
            scanf("%d", &bet);
            clearBuffer();

            bet += toCall;
            if (bet < 0) bet = 0;

            printf("You raise %d.\n", bet);
            break;

        /* Fold */
        case 3:
            player->is_folded = 1;
            bet = 0;
            printf("You fold.\n");
            break;

        default:
            player->is_folded = 1;
            bet = 0;
            printf("Invalid input → fold.\n");
            break;
    }

    return bet;
}

int bettingRound(GamePlayer players[], int *pot, Card community[5], int stage) {
    int highestBet = 0;
    int i;

    int needsAction[MAX_PLAYERS];

    // initialize
    for (i = 0; i < MAX_PLAYERS; i++) {
        if (!players[i].is_folded && players[i].chips > 0) {
            needsAction[i] = 1;
        } else {
            needsAction[i] = 0;
        }

        if (players[i].current_bet > highestBet) {
            highestBet = players[i].current_bet;
        }
    }

    int stillActing = 1;

    while (stillActing) {
        stillActing = 0;

        for (i = 0; i < MAX_PLAYERS; i++) {

            if (!needsAction[i]) continue;
            if (players[i].is_folded || players[i].chips <= 0) continue;

            int bet = 0;

            printf("\n--- Player %d turn ---\n", i + 1);

            if (players[i].is_human) {
                bet = humanBet(&players[i], highestBet);
            } else {
                bet = aiBet(&players[i], highestBet, community, stage);
            }

            if (bet < 0) bet = 0;

            players[i].chips -= bet;
            players[i].current_bet += bet;
            *pot += bet;

            // if player raised → everyone else must respond again
            if (players[i].current_bet > highestBet) {
                highestBet = players[i].current_bet;

                int j;
                for (j = 0; j < MAX_PLAYERS; j++) {
                    if (j != i && !players[j].is_folded && players[j].chips > 0) {
                        needsAction[j] = 1;
                    }
                }
            }

            // this player is done for now
            needsAction[i] = 0;
        }

        // check if anyone still needs to act
        for (i = 0; i < MAX_PLAYERS; i++) {
            if (needsAction[i]) {
                stillActing = 1;
                break;
            }
        }
    }

    printf("\nTotal pot: %d\n", *pot);
    return highestBet;
}

/* Start a full Texas Hold'em game round */
void startGame(GamePlayer players[]) {
    Card deck[TABLE_CARDS];
    int top = 0;
    int i = 0;
    int p = 0;
    int winner = -1;
    int bestScore = -1;
    int highCard;
    Table table = {0};

    /* reset round state */
    for (i = 0; i < MAX_PLAYERS; i++) {
        players[i].is_folded = 0;
        players[i].current_bet = 0;
    }

    printf("Enter small blind: ");
    scanf("%d", &table.small_blind);
    clearBuffer();

    printf("Enter big blind: ");
    scanf("%d", &table.big_blind);
    clearBuffer();

    players[0].chips -= table.small_blind;
    players[1].chips -= table.big_blind;

    players[0].current_bet = table.small_blind;
    players[1].current_bet = table.big_blind;

    table.pot = table.small_blind + table.big_blind;

    generateDeck(deck, TABLE_CARDS);
    shuffleDeck(deck, TABLE_CARDS);

    /* deal cards */
    for (i = 0; i < PLAYER_CARDS; i++) {
        for (p = 0; p < MAX_PLAYERS; p++) {
            players[p].hand[i] = dealCard(deck, &top);
        }
    }

    showHand(&players[0], 0);

    printf("\n--- Pre-flop ---\n");
    bettingRound(players, &table.pot, table.community, 0);

    printf("\n--- Flop ---\n");
    for (i = 0; i < MAX_PLAYERS; i++) {
        players[i].current_bet = 0;
    }

    for (i = 0; i < 3; i++)
        table.community[i] = dealCard(deck, &top);

    printBoard(table.community, 3);
    bettingRound(players, &table.pot, table.community, 1);

    printf("\n--- Turn ---\n");
    for (i = 0; i < MAX_PLAYERS; i++) {
        players[i].current_bet = 0;
    }

    table.community[3] = dealCard(deck, &top);

    printBoard(table.community, 4);
    bettingRound(players, &table.pot, table.community, 2);

    printf("\n--- River ---\n");
    for (i = 0; i < MAX_PLAYERS; i++) {
        players[i].current_bet = 0;
    }

    table.community[4] = dealCard(deck, &top);

    printBoard(table.community, 5);
    bettingRound(players, &table.pot, table.community, 3);

    /* simple evaluation: highest card in hand */
    winner = evaluateHands(players, MAX_PLAYERS, table.community);

    if (winner == -1) {
        printf("No winner (all folded)\n");
        return;
    }

    printf("\n--- Players' hand ---\n");
    for (i = 0; i < MAX_PLAYERS; i++) {
        if (!players[i].is_folded) {
            showHand(&players[i], i);
        }
    }

    printf("\n🏆 Winner is Player %d!\n", winner + 1);

    players[winner].chips += table.pot;

    if (winner == 0) {
        players[0].profile->losses += 1;
    } else {
        players[0].profile->losses += 1;
    }
    
    players[0].profile->total_chips = players[0].chips;
    saveProfile(players[0].profile); 
}

/* This function sets the hand's rank */
HandValue rankHand(Card hand[2], Card community[5]) {
    HandValue hv = {HIGH_CARD, {0,0,0,0,0}};
    Card all[7];
    int valueCounts[14];
    int suitCounts[4];
    char suits[4] = {'D', 'H', 'C', 'S'};
    char flushSuit = 0;
    int straightHigh = 0;
    int sortedValues[7];
    int idx = 0;
    int pairs = 0;
    int threes = 0;
    int fours = 0;
    int pairVals[2];
    int threeVal = 0;
    int fourVal = 0;
    int start = 0;
    int count = 0;
    int i = 0;
    int j = 0;

    for (i = 0; i < 2; i++) {
        all[i] = hand[i];
    }

    for (i = 0; i < 5; i++) {
        all[i + 2] = community[i];
    }

    for (i = 0; i < 7; i++) {
        valueCounts[all[i].value]++;
        switch(all[i].suit[0]) {
            case 'D': 
                suitCounts[0]++; 
                break;
            case 'H': 
                suitCounts[1]++; 
                break;
            case 'C': 
                suitCounts[2]++; 
                break;
            case 'S': 
                suitCounts[3]++; 
                break;
        }
    }

    /* Detect flush suit */
    for (i = 0; i < 4; i++) {
        if (suitCounts[i] >= 5) {
            flushSuit = suits[i];
        }
    }

    /* Collect sorted card values descending */
    for (i = 13; i >= 1; i--) {
        for (j = 0; j < valueCounts[i]; j++) {
            sortedValues[idx++] = i;
        }
    }

    /* Count multiples */
    for (i = 13; i >= 1; i--) {
        if (valueCounts[i] == 4) { 
            fours = 1; 
            fourVal = i; 
        }

        if (valueCounts[i] == 3) { 
            threes = 1; 
            threeVal = i; 
        }

        if (valueCounts[i] == 2) {
            if (pairVals[0] == 0) {
                pairVals[0] = i;
            } else {
                pairVals[1] = i;
            }

            pairs++;
        }
    }

    /* Check straight */
    for (start = 13; start >= 5; start--){
        count = 0;
        for (j = start; j > start - 5; j--){
            if (valueCounts[j] > 0) {
                count++;
            }
        }
        if (count == 5) {
            straightHigh = start;
            break;
        }
    }

    /* Determine hand type */
    if (fours) {
        hv.rank = FOUR_OF_A_KIND;
        hv.tiebreak[0] = fourVal;
        /* kicker */
        for (i = 0; i < 7; i++) {
            if (all[i].value != fourVal) { 
                hv.tiebreak[1] = all[i].value; 
                break; 
            }
        }
    } else if (threes && pairs) {
        hv.rank = FULL_HOUSE;
        hv.tiebreak[0] = threeVal;
        hv.tiebreak[1] = pairVals[0];
    } else if (flushSuit) {
        hv.rank = FLUSH;
        idx = 0;
        for (i = 13; i >= 1; i--){
            for (j = 0; j < 7; j++){
                if (all[j].value == i && all[j].suit[0] == flushSuit && idx < 5) {
                    hv.tiebreak[idx++] = i;
                }
            }
        }
    } else if (straightHigh) {
        hv.rank = STRAIGHT;
        hv.tiebreak[0] = straightHigh;
    } else if (threes) {
        hv.rank = THREE_OF_A_KIND;
        hv.tiebreak[0] = threeVal;
        idx = 1;
        for (i = 0; i < 7 && idx < 3; i++){
            if (all[i].value != threeVal) {
                hv.tiebreak[idx++] = all[i].value;
            }
        }
    } else if (pairs >= 2) {
        hv.rank = TWO_PAIR;
        hv.tiebreak[0] = pairVals[0];
        hv.tiebreak[1] = pairVals[1];
        for (i = 0; i < 7; i++) {
            if (all[i].value != pairVals[0] && all[i].value != pairVals[1]) {
                hv.tiebreak[2] = all[i].value; 
                break;
            }
        }
    } else if (pairs == 1) {
        hv.rank = ONE_PAIR;
        hv.tiebreak[0] = pairVals[0];
        idx = 1;

        for (i = 0; i < 7 && idx < 4; i++) {
            if (all[i].value != pairVals[0]) {
                hv.tiebreak[idx++] = all[i].value;
            }
        }
    } else {
        hv.rank = HIGH_CARD;
        for (i = 0; i < 5; i++) {
            hv.tiebreak[i] = sortedValues[i];
        }
    }

    return hv;
}

/* Evaluates all hands in the game */
int evaluateHands(GamePlayer players[], int numPlayers, Card community[5]) {
    int winner = -1;
    int i;
    HandValue bestHv;
    int first = 1;

    for (i = 0; i < numPlayers; i++) {

        if (players[i].is_folded)
            continue;

        HandValue hv = rankHand(players[i].hand, community);

        if (first) {
            bestHv = hv;
            winner = i;
            first = 0;
            continue;
        }

        if (compareHands(hv, bestHv) > 0) {
            bestHv = hv;
            winner = i;
        }
    }

    return winner;
}

/* Compres two hands */
int compareHands(HandValue h1, HandValue h2){
    if(h1.rank > h2.rank) return 1;
    if(h1.rank < h2.rank) return -1;
    
    int i = 0;

    /* same rank, compare tiebreakers */
    for (i = 0; i < 5; i++) {
        if (h1.tiebreak[i] > h2.tiebreak[i]) {
            return 1;
        }

        if (h1.tiebreak[i] < h2.tiebreak[i]) {
            return -1;
        }
    }
    return 0;
}

/* Prints the player's hand */
void showHand(GamePlayer *player, int i) {
    if (player->is_human) {
        printf("\nYour Hand:\n");
    } else {
        printf("\nPlayer %d hand:\n", i + 1);
    }

    printf("  [%s%s] [%s%s]\n",
        getCardValueString(player->hand[0].value), getSuitSymbol(player->hand[0].suit),
        getCardValueString(player->hand[1].value), getSuitSymbol(player->hand[1].suit)
    );
}

/* Return suit symbol for better UI */
const char* getSuitSymbol(char *suit) {
    if (strcmp(suit, "Hearts") == 0) {
        return "♥";
    }

    if (strcmp(suit, "Diamonds") == 0) {
        return "♦";
    }

    if (strcmp(suit, "Clubs") == 0) {
        return "♣";
    }

    if (strcmp(suit, "Spades") == 0) {
        return "♠";
    }

    return "?";
}

/* Prints the board */
void printBoard(Card community[], int count) {
    int i;

    printf("\nCommunity Cards:\n");

    for (i = 0; i < count; i++) {
        printf("  [%d%s] ", community[i].value, getSuitSymbol(community[i].suit));
    }

    printf("\n");
}

/* Evaluates the AI hand strength */
int evaluateSimpleStrength(Card hand[2], Card community[5], int stage) {
    int score = 0;
    int i = 0;

    /* hole cards matter most early */
    score += hand[0].value + hand[1].value;

    /* pair in hand */
    if (hand[0].value == hand[1].value) {
        score += 35;
    }

    /* bonus for high cards */
    if (hand[0].value >= 11) score += 5;
    if (hand[1].value >= 11) score += 5;

    /* community cards influence increases later */
    for (i = 0; i < 5; i++) {
        if (community[i].value == 0) {
            continue;
        }

        if (community[i].value >= 10) {
            score += stage * 2;
        }
    }

    /* stage scaling (later = more conservative AI) */
    score += stage * 3;

    return score;
}

const char* getCardValueString(int value) {
    switch (value) {
        case 1:  return "A";  // Ace
        case 11: return "J";
        case 12: return "Q";
        case 13: return "K";
        default: {
            static char buffer[3];
            snprintf(buffer, sizeof(buffer), "%d", value);
            return buffer;
        }
    }
}
