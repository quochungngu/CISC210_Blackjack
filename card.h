/* 5 points: This file should contain prototypes for all card/deck-related functions (see card.c) as well as the 'card' structure.
 * a 'card' structure has an (int) rank, a (char) suit, and a pointer to card (next in the pile; 0 for end of the list). 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Card {
    int rank;
    char suit;
    struct Card *next; /* have to use struct Card because the typedef isnt "ready" yet */
} card;

/* Prototype all functions below:*/

card *make_deck();
int count_deck(card *deck);
void destroy_deck(card *deck);
card *shuffle(card *deck);
card *deal(card *deck);
int total(card* hand);
void show(card* hand);
