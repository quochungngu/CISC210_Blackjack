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

card *make_deck(){
	card *first = (card *) malloc(sizeof(card));
	first->rank = 1;
	first->suit = C;
	
	card *current = first;
	for(int rank=2;rank<14;rank++){
		card *newCard = (card *) malloc(sizeof(card));
		newCard->rank = rank;
		newCard->suit = C;

		current->next = newCard;
		current = newCard;
	}

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

	current->next = 0;

	return first;
}

void destroy_deck(card *deck){
	if(deck) {
		card *current = deck;
		card *next = current->next;
	
		while(next){
			free(current);
			current = next;
			next = current->next;
		}
	
		free(current);
	} else {
		printf("\nDeck is empty\n");
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

card *deal(card *deck){
	card *drawn = 0;

	if (count_deck(deck)){
		card *current = deck;
		card *next = current->next;

		while(next->next != 0){
			current = next;
			next = current->next;
		}
	
		drawn = next;
		current->next = 0;
	
		printf("%d%c\n",drawn->rank,drawn->suit);
	} else {
		printf("No more cards in the deck.\n");
	}

	return drawn;
}

int total(card *hand){
	int sum = 0;
	card *current = hand;

	while (current){
		int score;

		if(current->rank >= 10){
			score = 10;
		} else {
			score = current->rank;
		}

		sum += score;
		current = current->next;
	}

	return sum;
}

void show(card *hand){
	card *current = hand;

	while(current) {
		printf("%d%c ",current->rank,current->suit);
		current = current->next;
	}

	printf("\n");
}
