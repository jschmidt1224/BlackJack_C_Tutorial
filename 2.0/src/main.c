#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"
#include "utf8.h"


#define clear() printf("\033[H\033[J")

void printHands(struct Card*, struct Card*);
int handValue(struct Card*);

struct Card newCard();
void shuffleDeck(struct Card *);


struct Card playerHand[HAND_SIZE], dealerHand[HAND_SIZE];
struct Card deck[52];



int main()
{
	initSuits();
	

	int i, input, hand_size, cont = 1, playerValue, dealerValue;
	srand(time(NULL));
	for (i = 0; i < 52; i++) {
		deck[i] = initCard(i);
	}
	shuffleDeck(deck);
	while (cont) {
		for (i = 0; i < HAND_SIZE; i++) {
			playerHand[i].type = -1;
			dealerHand[i].type = -1;
		}
		playerHand[0] = newCard();
		playerHand[1] = newCard();
		dealerHand[0] = newCard();
		dealerHand[1] = newCard();
		while (1) {
			clear();
			printf("\n");
			printHands(playerHand, dealerHand);
			printf("What would you like to do?\n");
			printf("1) Hit\n");
			printf("2) Stay\n");
			printf("3) Quit\n");
			if (scanf("%d", &input) <= 0) {
				cont = 0;
				break;
			}
			if (input == 1) {
				// Actions for Hit
				if ((hand_size = handSize(playerHand)) < HAND_SIZE) {
					playerHand[hand_size] = newCard();
				} else {
					printf("You can't hit again: Too many cards\n");
				}
			} else if (input == 2) {
				// Action for Stay
				clear();
				while(handValue(dealerHand) < 17 && (hand_size = handSize(dealerHand)) < HAND_SIZE) {
					dealerHand[hand_size] = newCard();
				}
				playerValue = handValue(playerHand);
				dealerValue = handValue(dealerHand);
				if (dealerValue > 21) {
					printf("Dealer Bust: You Win!\n");
				} else if (playerValue > 21) {
					printf("Bust: You lose :(\n");
				} else if (playerValue > dealerValue) {
					printf("You Win!\n");
				} else if (playerValue < dealerValue) {
					printf("You lose :(\n");
				} else {
					printf("Push!\n");
				}
				printHands(playerHand, dealerHand);
				printf("\n\n\n\n");
				printf("What would you like to do?\n");
				printf("1) Continue\n");
				printf("2) Quit\n");
				if (scanf("%d", &input) <= 0) {
					cont = 0;
					break;
				}
				if (input != 1) {
					cont = 0;
				}
				break;
				
			} else {
				// Quit
				cont = 0; 
				break;
			}
		}

	}
	printf("Quitting...\n");
	return 0;
}

//void printHands(struct Card *player, struct Card *dealer, int showDealer)
//{/
//	clear();/
//	int i = 0, plen = handSize(player), dlen = handSize(dealer);
//	printf("\n");
//	printf("\E2\99\A0");
//}

void printHands(struct Card *player, struct Card *dealer)
{
	int i = 01;
	printHand(player);
	printf("\n\n");
	printHand(dealer);
	printf("\nYour hand: ");
	for (i = 0; i<HAND_SIZE; i++) {
		if (player[i].type != -1) {
			printf("%d ", player[i].type);
		}
	}
	printf(": %d\nDealers hand: ", handValue(player));
	for (i = 0; i<HAND_SIZE; i++) {
		if (dealer[i].type != -1) {
			printf("%d ", dealer[i].type);
		}
	}
	printf(": %d\n", handValue(dealer));
}



void shuffleDeck(struct Card *deck)
{
	int i;
	for (i = 0; i < 52; i++) {
		struct Card tmp = deck[i];
		int shuffle = rand() % 52;
		deck[i] = deck[shuffle];
		deck[shuffle] = tmp;
	}
}

struct Card newCard() 
{
	static int current = 0;
	if (current < 52) {
		return deck[current++];
	} else {
		shuffleDeck(deck);
		current = 0;
		return deck[current++];
	}

}

int handValue(struct Card *hand)
{
	int i = 0, sum = 0;
	while (hand[i].type != -1 && i < HAND_SIZE) {
		sum += hand[i++].value;
	}
	return sum;
}

