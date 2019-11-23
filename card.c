/* 40 points */
/* Define all card/deck related functions as follows:
 * make_deck: generates a new list of 52 unique cards with ranks 1-13 and suits CDHS. Returns a pointer to the head of the list. 
 *            Note: you must use malloc to create all 52 cards.
 * destroy_deck: consumes a pointer to a card. Free memory for all cards in the list.
 * shuffle: consumes a pointer to a card (expected to be the head of a list of cards). Returns a pointer to a card (the possibly new head).
 *          Randomly re-orders the cards in the list. Note; this function has been provided for you.
 * deal: consumes a pointer to a card (expected to be the head of a list of cards). Finds the last card in the list, prints its values, removes it
 *       from the list, and returns it (pointer to card). 
 * total: consumes a pointer to card. Returns the sum of the values in the list headed by the given card (note: 10,11,12, and 13 all value as 10).
 * show: consumes a pointer to card. Prints the rank and suit of all cards in the list (this may be one card) on one line. For example:
 *       11H 9S 3D 1C 1S
*/
#include "card.h"

// Makes a linked list of 52 cards
card *make_deck(){
	// Initializing the first card in deck as One of Clubs
	// "first" will be the head of the linked list of cards
	card *first = (card *) malloc(sizeof(card));
	first->rank = 1;
	first->suit = 'C';
	
	// Making rest of the cards in Clubs
	card *current = first;
	for(int rank=2;rank<14;rank++){
		card *newCard = (card *) malloc(sizeof(card));
		newCard->rank = rank;
		newCard->suit = 'C';

		current->next = newCard;
		current = newCard;
	}
	
	// Making all cards in Diamond, Hearts, and Spades.
	char suit[3] = "DHS";
	for(int i=0;i<strlen(suit);i++){
		for(int rank=1;rank<14;rank++) {
			card *newCard = (card *) malloc(sizeof(card));
			newCard->rank = rank;
			newCard->suit = suit[i];

			current->next = newCard;
			current = newCard;
		}
	}
	
	// Mark the last card as last by setting its next to 0;
	current->next = 0;
	
	return first;
}

// Tranverses through a linked list of cards and frees every node
void destroy_deck(card *deck){
	if(deck) {
		card *current = deck;
		card *next = current->next;
		
		while(next){
			free(current);
			current->next = 0;
			current = next;
			next = current->next;
		}
	
		free(current);
		current->next = 0;
		//printf("Collection of cards has been destroyed.\n");
	} else {
		printf("Deck is already empty and can't be destroyed.\n");
	}
}

/* counts the number of cards in the list headed by "deck" */
int count_deck(card *deck) {
    int count=0;
    /* No initialization required. When "deck" is NULL (zero), it's at the end. Otherwise, move to the
    next card and increment the count. No body of the for loop! */
    for(;deck;deck=deck->next,count++);
    return count;
}

/* Emulates a "riffle shuffle" of "deck". */
card *shuffle(card *deck) {
    int size = count_deck(deck);
    card *cut=deck;
    for(int i=0; i<size/2; i++){
        cut=cut->next;
    }
    /* cut is now the card 1/2 way through the deck */
    card *riffle=cut->next;
    cut->next = 0; /* deck and riffle now head separate lists */
    /* Shuffle the deck by randomly pulling a card from the head of "deck" or "riffle"
       and make it the new head of "retdeck" */
    card *retdeck=0;
    for(;deck || riffle;) { /* just like a while loop */
        card *temp;
        if(deck && (!riffle || drand48()<0.5)) {
            /* next card comes from the top of 'deck' */
            temp=deck;
            deck=deck->next;
        } else if(riffle) {
            /* next card comes from the top of 'riffle' */
            temp=riffle;
            riffle=riffle->next;
        }
        /* put the card at the top of the "retdeck" */
        temp->next=retdeck;
        retdeck=temp;
    }
    return retdeck;
}

// Removes the last card in the linked list of cards and prints its rank and suit and returns it
card *deal(card *deck){
	card *drawn = 0;

	if (deck){
		card *current = deck;
		card *next = current->next;
		
		// Checks if there is only 1 card left in deck
		if (next) {
			// Cycle through linked list until current is the card before the last card
			// and next is the last card
			while(next->next){
				current = next;
				next = current->next;
			}

			// The drawn card is the card located at "next"
			// The card before the last card located at "current" becomes the new last card
			drawn = next;
			current->next = 0;
		} else {
			drawn = current;
		}	
		printf("Dealt %d%c\n",drawn->rank,drawn->suit);
	} else {
		printf("No more cards in the deck.\n");
	}

	return drawn;
}

// Cycles through a linked list of cards and sums up the score of their ranks
// Ranks 10 to 13, inclusive, are 10; Ranks 1 to 9, inclusive, are worth their rank number
int total(card *hand){
	int sum = 0;
	card *current = hand;
	
	while (current){
		int score;
		
		// Score each card based on their rank
		if(current->rank >= 10){
			score = 10;
		} else {
			score = current->rank;
		}
		
		// Add score to total sum and then cycle to the next card
		sum += score;
		current = current->next;
	}

	return sum;
}

// Prints all the ranks and suits of the cards in a linked list of cards on a single line
void show(card *hand){
	card *current = hand;
	
	// Cycle through entire linked list and print their rank and then suit
	while(current) {
		printf("%d%c ",current->rank,current->suit);
		current = current->next;
	}

	printf("\n");
}
