/* Contains main() and any desired helper functions to play the game as described in the instructions. Must not _define_ any of the 
 * card-related helper functions but must use thm at least as frequently as indicated below (hit means either player or dealer hit):
 * make_deck:1; shuffle:1; deal: 3+1/hit; total: 2+1/hit; show: 2; destroy_deck: 1
 */
 /* 15 points */
 #include "card.h"

void printScore(card *hand);
card *getLastNode(card *hand);

int main(void) {
/* Your code goes here */

	int playGame = 1;
	
	while(playGame){
		card *deck = make_deck();
		card *deck = shuffle(deck);

		card *player = deal(deck);
		card *player->next = deal(deck);

		card *dealer = deal(deck);

		show(player);
		printScore(player);
		int playerTurn = 1;
		while(playerTurn && deck) {
			int validResponse = 0;
			char *response;

			while(!validResponse){
				printf("\nHit or stand?:\n");
				scanf("%s\n",response);

				if(reponse == "h" || response == "H" || response == "hit" || reponse == "Hit"){
					validResponse = 1;

					card *playerLast = getLastNode(player);
					playerLast->next = deal(deck);

					if (total(player) > 21) {
						playerTurn = 0;
					}
				} else if(reponse == "s" || response == "S" || reponse == "stand" || reponse == "Stand"){
					validResponse = 1;
					playerTurn = 0;
				} else {
					printf("Invalid response. Try again.\n")
				}
			}

			show(player);
			printScore(player);	
		}

		if (total(player) <= 21) {
			while(total(player) <= 21 && total(dealer) < 16  && deck) {
				card *dealerLast = getLastNode(player);
				dealerLast->next = deal(deck);
			}

			show(dealer);
			printScore(dealer);

			if(total(dealer) > 21){
				printf("\nWon!\n");
			} else if (total(dealer) == total(player)){
				printf("\nLost!\n");
			} else if (total(dealer) > total(player)) {
				printf("\nLost!\n");
			} else if (total (dealer) < total(player)) {
				printf("\nWon!\n");
			}
		} else {
			show(dealer);
			printScore(dealer);

			printf("\nLost!\n");
		}

		destroy_deck(deck);
		destroy_deck(player);
		destroy_deck(dealer);

		printf("\nPlay again?\n");
		scanf("%d\n",&playGame);
	}
}

void printScore(card *hand){
	printf("\tScore: %d\n",total(hand);
}

card *getLastNode(card *hand) {
	card *current = hand;

	while(current->next){
		current = current->next;
	}

	return current;
}
