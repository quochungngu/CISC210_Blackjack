/* Contains main() and any desired helper functions to play the game as described in the instructions. Must not _define_ any of the 
 * card-related helper functions but must use thm at least as frequently as indicated below (hit means either player or dealer hit):
 * make_deck:1; shuffle:1; deal: 3+1/hit; total: 2+1/hit; show: 2; destroy_deck: 1
 */
 /* 15 points */

#include "card.h"

void printScore(card *hand);
card *getLastNode(card *hand);
void printDemarcation(char demarker,int numStars, char *string);

int main(void) {
/* Your code goes here */

	int playGame = 1;
	
	while(playGame){
		card *deck = make_deck();
		
		for(int i = 0;i < 5; i++) {
			deck = shuffle(deck);
		}
		
		printDemarcation('=',5,"Dealing your cards");
		card *player = deal(deck);
		player->next = deal(deck);
		
		printDemarcation('=',5,"Dealing dealer's cards");
		card *dealer = deal(deck);

		printDemarcation('*',10,"Your Hand");
		show(player);
		printScore(player);

		printDemarcation('*',10,"Dealer's Hand");
		show(dealer);
		printScore(dealer);

		int playerTurn = 1;
		printDemarcation('=',20,"Your Turn");
		while(playerTurn && deck) {
			int validResponse = 0;
			char response[100];

			while(!validResponse){
				printf("\nHit or stand?:\n");
				scanf("%s",response);

				if(!strcmp("h",response) || !strcmp("H",response) || !strcmp("hit",response) || !strcmp("Hit",response)){
					validResponse = 1;
					
					card *playerLast = getLastNode(player);
					playerLast->next = deal(deck);

					if (total(player) > 21) {
						playerTurn = 0;
					}
				} else if(!strcmp("s",response) || !strcmp("S",response) || !strcmp("stand",response) || !strcmp("Stand",response)){
					validResponse = 1;
					playerTurn = 0;
				} else {
					printf("Invalid response. Try again.\n");
				}
			}
			
			printDemarcation('*',10,"Your Hand");
			show(player);
			printScore(player);	
		}
		printDemarcation('=',20,"Your Turn End");
		
		int playerWin = -1;
		if (total(player) <= 21) {
			printDemarcation('=',20,"Dealer's Turn");
			while(total(dealer) < 16  && deck) {
				card *dealerLast = getLastNode(dealer);
				dealerLast->next = deal(deck);
			}
			printDemarcation('=',20,"Dealer's Turn End");
			
			if(total(dealer) > 21){
				playerWin = 1;
			} else if (total(dealer) == total(player)){
				playerWin = 0;
			} else if (total(dealer) > total(player)) {
				playerWin = 0;
			} else if (total (dealer) < total(player)) {
				playerWin = 1;
			}
		} else {
			playerWin = 0;
		}
		
		printDemarcation('=',20,"Scoreboard");
		printDemarcation('*',10,"Your Hand");
		show(player);
		printScore(player);

		printDemarcation('*',10,"Dealer's Hand");
		show(dealer);
		printScore(dealer);
		printDemarcation('=',20,"Scoreboard End");

		if(playerWin > 0){
			printDemarcation('+',20,"Won!");
		} else if (playerWin < 0) {
			printf("Error has occurred when checking win status\n");
		} else {
			printDemarcation('-',20,"Lost!");
		}
		
		destroy_deck(deck);
		destroy_deck(player);
		destroy_deck(dealer);
		
		printDemarcation('=',20,"Round Over!");
		printf("Play again? Type 0 for no. Type anything else for yes.\n");
		scanf("%d",&playGame);
		
		if(playGame){
			printDemarcation('=',20,"New Round!");
		}
	}

	return 0;
}

void printScore(card *hand){
	printf("\tScore: %d\n",total(hand));
}

card *getLastNode(card *hand) {
	card *current = hand;

	while(current->next){
		current = current->next;
	}

	return current;
}

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
