#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"

#define HAND_SIZE 5

#define clear() printf("\033[H\033[J")

void printHands(struct Card*, struct Card*);
int handValue(struct Card*);
int handSize(struct Card*);
struct Card newCard();
void shuffleDeck(struct Card *);

struct Card playerHand[HAND_SIZE], dealerHand[HAND_SIZE];
struct Card deck[52];

int main()
{
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
					printHands(playerHand, dealerHand);
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

void printHands(struct Card *player, struct Card *dealer)
{
	clear();
	int i = 0;
	printf("Your hand: ");
	for ( ; i<HAND_SIZE; i++) {
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

int handSize(struct Card *hand)
{
	int i;
	for (i = 0; i < HAND_SIZE; i++) {
		if (hand[i].type == -1) {
			return i;
		}
	}
	return HAND_SIZE;
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
		printf("NEW DECK!!\n\n\n\n\n\n\n\n\n\n\n");
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
