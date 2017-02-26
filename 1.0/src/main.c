#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HAND_SIZE 5

void printHands(int*, int*, int);
int handSize(int*);
int newCard();
int handValue(int*);

int playerHand[HAND_SIZE], dealerHand[HAND_SIZE];
int playerSize, dealerSize;

int main()
{
	int i, input, cont = 1, newGame = 0, playerValue, dealerValue;
	char buf[1024];

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
        playerSize = dealerSize = 2;
        newGame = 0;
		while (!newGame) {
			printHands(playerHand, dealerHand, 1);
			printf("What would you like to do?\n");
			printf("1) Hit\n");
			printf("2) Stay\n");
			printf("3) Quit\n");
			if (scanf("%d", &input) <= 0) {
                scanf("%1023s", buf);
                input = -1;
			}
            if (input > 3 || input < 1) {
                printf("Please enter a valid option\n");
                continue;
            }
            switch (input) {
			case 1: 
				// Actions for Hit
				if (playerSize < HAND_SIZE) {
                    playerHand[playerSize++] = newCard();
                    if (handValue(playerHand) < 21 && playerSize < HAND_SIZE) {
                        break;
                    }
				}
            case 2:
				// Action for Stay
				while(handValue(dealerHand) < 17 && dealerSize < HAND_SIZE) {
					dealerHand[dealerSize++] = newCard();
				}
				printHands(playerHand, dealerHand, 0);
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
				printf("\n\n");
                newGame = 1;
				break;
            default:
				// Quit
                newGame = 1;
				cont = 0; 
				break;
			}
		}
	}
	printf("Quitting...\n");
	return 0;
}

void printHands(int *player, int *dealer, int hide)
{
	int i = 0;
	printf("Your hand:    ");
	for ( ; i < HAND_SIZE; i++) {
		if (player[i] != -1) {
			printf("%-2d ", player[i]);
		}
	}
	printf("\nDealers hand: ");
	for (i = 0; i<HAND_SIZE; i++) {
		if (dealer[i] != -1) {
            if (hide && i == 0) {
                printf("** ");
            } else {
			    printf("%-2d ", dealer[i]);
            }
		}
	}
    printf("\n");
}

int newCard()
{
	return rand() % 10 + 1;
}

int handValue(int *hand)
{
	int i = 0, sum = 0, aceCount = 0;
	while (hand[i] != -1 && i < HAND_SIZE) {
		if (hand[i] == 1) {
			aceCount += 1;
		}
		sum += hand[i++];
	}
	while (sum < 12 && aceCount > 0) {
		sum += 10;
		aceCount -= 1;
	}
	return sum;
}


