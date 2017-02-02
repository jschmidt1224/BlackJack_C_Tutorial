#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"

#define HAND_SIZE 5

void printHands(int*, int*);
int handSize(int*);
int newCard();
int handValue(int*);

int playerHand[HAND_SIZE], dealerHand[HAND_SIZE];

int main()
{
	struct Card deck[52];
	int i;
	srand(time(NULL));
	for (i = 0; i < 52; i++) {
		deck[i] = initCard(i);
	}

	for (i = 0; i < 52; i++) {
		struct Card tmp = deck[i];
		int shuffle = rand() % 52 + 1;
		deck[i] = deck[shuffle];
		deck[shuffle] = tmp;
	}

	for (i = 0; i < 52; i++) {
		printf("%d, %d\n", deck[i].suit, deck[i].type);
	}
}







int main2()
{
	int i, input, hand_size, cont = 1, playerValue, dealerValue;
	srand(time(NULL));
	while (cont) {
		for (i = 0; i < HAND_SIZE; i++) {
			playerHand[i] = -1;
			dealerHand[i] = -1;
		}
		playerHand[0] = newCard();
		playerHand[1] = newCard();
		dealerHand[0] = newCard();
		dealerHand[1] = newCard();
		while (1) {
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
				while(handValue(dealerHand) < 17 && (hand_size = handSize(dealerHand)) < HAND_SIZE) {
					dealerHand[hand_size] = newCard();
				}
				printHands(playerHand, dealerHand);
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
				printf("\n\n\n\n");
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

void printHands(int *player, int *dealer)
{
	int i = 0;
	printf("Your hand: ");
	for ( ; i<HAND_SIZE; i++) {
		if (player[i] != -1) {
			printf("%d ", player[i]);
		}
	}
	printf("\nDealers hand: ");
	for (i = 0; i<HAND_SIZE; i++) {
		if (dealer[i] != -1) {
			printf("%d ", dealer[i]);
		}
	}
	printf("\n");
}

int handSize(int *hand)
{
	int i;
	for (i = 0; i < HAND_SIZE; i++) {
		if (hand[i] == -1) {
			return i;
		}
	}
	return HAND_SIZE;
}

int newCard()
{
	return rand() % 10 + 1;
}

int handValue(int *hand)
{
	int i = 0, sum = 0;
	while (hand[i] != -1) {
		sum += hand[i++];
	}
	return sum;
}