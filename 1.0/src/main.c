#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HAND_SIZE 5

void printHands(int*, int*, int);
int handValue(int*);
void reset_game(int*, int*, int*, int*);
int get_input();
int newCard();

int playerHand[HAND_SIZE], dealerHand[HAND_SIZE];
int playerSize, dealerSize;

int main()
{
    int input, cont = 1, newGame = 0, playerValue, dealerValue;
    srand(time(NULL));
    while (cont) {
        reset_game(playerHand, dealerHand, &playerSize, &dealerSize);
        newGame = 0;
        while (!newGame) {
            printHands(playerHand, dealerHand, 1);
            input = get_input();
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
                    if (playerValue > 21) {
                        printf("Bust: You Lose :(\n");
                    } else if (dealerValue > 21) {
                        printf("Dealer Bust: You win!\n");
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
            aceCount = 1;
        }
        sum += hand[i++];
    }
    if (sum < 12 && aceCount) {
        sum += 10;
    }
    return sum;
}

void reset_game(int *pHand, int *dHand, int *pSize, int *dSize)
{
    int i;
    for (i = 0; i < HAND_SIZE; i++) {
        pHand[i] = -1;
        dHand[i] = -1;
    }
    pHand[0] = newCard();
    pHand[1] = newCard();
    dHand[0] = newCard();
    dHand[1] = newCard();
    *pSize = *dSize = 2;
}

int get_input()
{
    int input = -1;
    char buf[1024];
    printf("What would you like to do?\n");
    printf("1) Hit\n");
    printf("2) Stay\n");
    printf("3) Quit\n");
    while (1) {
        if (scanf("%d", &input) <= 0) {
            scanf("%1023s", buf);
            input = -1;           
        } else if (input >= 1 && input <= 3) {
            break;
        }
        printf("Please enter a valid option\n");
    }    
    return input;
}



