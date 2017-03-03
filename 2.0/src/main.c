#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"

#define HAND_SIZE 5

void printHands(struct Card*, struct Card*, int);
int handValue(struct Card*);
void reset_game(struct Card*, struct Card*, int*, int*);
int get_input();
struct Card newCard();

struct Card playerHand[HAND_SIZE], dealerHand[HAND_SIZE];
int playerSize, dealerSize;

int main()
{
    int input, cont = 1, newGame = 0, playerValue, dealerValue;
    initSuits();
    srand(time(NULL));
    initDeck();
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

void printHands(struct Card *player, struct Card *dealer, int hide)
{
    int i = 0;
    printf("Your hand:    ");
    for ( ; i < HAND_SIZE; i++) {
        if (player[i].type != -1) {
            printf("%2s%s ", prints[player[i].type], suits[player[i].suit]);
        }
    }
    printf("\nDealers hand: ");
    for (i = 0; i<HAND_SIZE; i++) {
        if (dealer[i].type != -1) {
            if (hide && i == 0) {
                printf("%s ", prints[0]);
            } else {
                printf("%2s%s ", prints[dealer[i].type], suits[dealer[i].suit]);
            }
        }
    }
    printf("\n");
}

struct Card newCard()
{
    static int current = 0;
    if (current < DECK_SIZE) {
        return deck[current++];
    } else {
        shuffleDeck(deck);
        current = 0;
        return deck[current++];
    }

}

int handValue(struct Card *hand)
{
    int i = 0, sum = 0, aceCount = 0;
    while (hand[i].type != -1 && i < HAND_SIZE) {
        if (hand[i].value == 1) {
            aceCount = 1;
        }
        sum += hand[i++].value;
    }
    if (sum < 12 && aceCount) {
        sum += 10;
    }
    return sum;
}

void reset_game(struct Card *pHand, struct Card *dHand, int *pSize, int *dSize)
{
    int i;
    for (i = 0; i < HAND_SIZE; i++) {
        pHand[i].type = -1;
        dHand[i].type = -1;
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



