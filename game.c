/* Contains main() and any desired helper functions to play the game as described in the instructions. Must not _define_ any of the 
 * card-related helper functions but must use thm at least as frequently as indicated below (hit means either player or dealer hit):
 * make_deck:1; shuffle:1; deal: 3+1/hit; total: 2+1/hit; show: 2; destroy_deck: 1
 */
 /* 15 points */

#include "card.h"

void printScore(card *hand);
//card *getLastNode(card *hand);
void printDemarcation(char demarker,int numStars, char *string);

int main(void) {
/* Your code goes here */

	// playGame controls is the outermost gameplay loop
	// Each loop in the outermost gameplay loop represents 1 round of blackjack
	int playGame = 1;
	while(playGame){
		
		// Make the deck and then shuffle it 5 times 
		card *deck = make_deck();
		for(int i = 0;i < 5; i++) {
			deck = shuffle(deck);
		}
		
		// Dealing the initial 2 cards to the player and 1 card to the dealer
		printDemarcation('=',5,"Dealing your cards");
		card *player = deal(deck);
		player->next = deal(deck);
		
		printDemarcation('=',5,"Dealing dealer's cards");
		card *dealer = deal(deck);
		
		// Showing the player and dealer's hands and score
		printDemarcation('*',10,"Your Hand");
		show(player);
		printScore(player);
		
		// playerTurn controls the player's turn loop
		// The player's turn loop ends when the player stands, the player's hand exceeds 21, or the deck is empty
		int playerTurn = 1;
		printDemarcation('=',20,"Your Turn");
		while(playerTurn && deck) {
			int validResponse = 0;
			char response[100];
			
			// This loops repeats until the player gives a valid response
			// Either "h", "H", "hit", or "Hit" to hit and be dealt a card
			// Or "s", "S", "stand", or "Stand" to stand and end their turn
			while(!validResponse){
				
				// Scanning player response
				printf("\nHit or stand?:\n");
				scanf("%s",response);
				
				// Either hit, stand, or force player to input another response based on what their response was
				if(!strcmp("h",response) || !strcmp("H",response) || !strcmp("hit",response) || !strcmp("Hit",response)){
					validResponse = 1;
					
					// Deals a card to the player's hand
					card *dealtCard = deal(deck);
					dealtCard->next = player;
					player = dealtCard;
					
					// Ends player's turn if their hand is over 21 and they automatically lose
					if (total(player) > 21) {
						playerTurn = 0;
					}
				} else if(!strcmp("s",response) || !strcmp("S",response) || !strcmp("stand",response) || !strcmp("Stand",response)){
					// End player's turn
					validResponse = 1;
					playerTurn = 0;
				} else {
					printf("Invalid response. Try again.\n");
				}
			}
			
			// Print their hand and score every time they hit a card
			printDemarcation('*',10,"Your Hand");
			show(player);
			printScore(player);	
		}
		printDemarcation('=',20,"Your Turn End");
		
		// Start dealer's turn or skip dealer's turn if player already lost having a hand score over 21.
		int playerWin = 0;
		if (total(player) <= 21) {
			printDemarcation('=',20,"Dealer's Turn");
			// Deal cards to the dealer until their score is 17 or higher
			while(total(dealer) < 16  && deck) {
				card *dealtCard = deal(deck);
				dealtCard->next = dealer;
				dealer = dealtCard;
			}
			printDemarcation('=',20,"Dealer's Turn End");
			
			// Decide who wins based on black jack rules
			if(total(dealer) > 21){
				playerWin = 1;
			} else if (total(dealer) == total(player)){
				playerWin = -1;
			} else if (total(dealer) > total(player)) {
				playerWin = -1;
			} else if (total (dealer) < total(player)) {
				playerWin = 1;
			}
		} else {
			playerWin = -1;
		}
		
		// Print player and dealer's hands and score at the end of round
		printDemarcation('=',20,"Scoreboard");
		printDemarcation('*',10,"Your Hand");
		show(player);
		printScore(player);

		printDemarcation('*',10,"Dealer's Hand");
		show(dealer);
		printScore(dealer);
		printDemarcation('=',20,"Scoreboard End");
		
		// Decide if player won or lost
		if(playerWin > 0){
			printDemarcation('+',20,"Won!");
		} else if (playerWin < 0) {
			printDemarcation('-',20,"Lost!");
		} else {
			printf("Error has occurred when checking win status\n");
		}
		
		// Destroy all cards made
		destroy_deck(deck);
		destroy_deck(player);
		destroy_deck(dealer);
		
		// Ask if the player wants to quit or play another round
		printDemarcation('=',20,"Round Over!");
		printf("Play again? Type 0 for no. Type anything else for yes.\n");
		scanf("%d",&playGame);
		
		if(playGame){
			printDemarcation('=',20,"New Round!");
		}
	}

	return 0;
}

// Prints the total score of the linked list of cards given.
void printScore(card *hand){
	printf("\tScore: %d\n",total(hand));
}

// card *getLastNode(card *hand) {
	// card *current = hand;

	// while(current->next){
		// current = current->next;
	// }

	// return current;
// }

// Prints a line with "numTimes" of the "demarker" before and after the "string"
void printDemarcation(char demarker,int numTimes,char* string) {
	printf("\n");
	for(int i = 0;i<numTimes;i++){
		printf("%c",demarker);
	}
	printf("%s",string);
	for(int i = 0;i<numTimes;i++){
		printf("%c",demarker);
	}
	printf("\n");
}
