#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "card.h"
#include "utf8.h"
#include <ncursesw/ncurses.h>
#include "test.h"


void printHands(struct Card*, struct Card*);
int handValue(struct Card*);

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

struct Card newCard();
void shuffleDeck(struct Card *);


struct Card playerHand[HAND_SIZE], dealerHand[HAND_SIZE];
struct Card deck[52];


int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");
	initscr();
    cbreak();
    start_color();
    init_pair(1, -1, -1);
    wbkgdset(stdscr, COLOR_PAIR(1));
    //attron(COLOR_PAIR(0));
    initSuits();
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    refresh();

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
			//clear();
			printf("\n");
			printHands(playerHand, dealerHand);
			printw("What would you like to do?\n");
			printw("1) Hit\n");
			printw("2) Stay\n");
			printw("3) Quit\n");
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
				//clear();
				while(handValue(dealerHand) < 17 && (hand_size = handSize(dealerHand)) < HAND_SIZE) {
					dealerHand[hand_size] = newCard();
				}
				playerValue = handValue(playerHand);
				dealerValue = handValue(dealerHand);
				printf("\n");
				printHands(playerHand, dealerHand);
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
    endwin();
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
	//printf("\n");
    WINDOW *table;
    table = newwin(24, 82, 0, 2);
    wbkgd(table, COLOR_PAIR(3));
    box(table, 0, 0);
    wrefresh(table);
	printHand(player, 0);
	printf("\n\n");
	printHand(dealer, 1);
	printf("\n\n");
	/*
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
	*/
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
	int i = 0, sum = 0, aceCount = 0;
	while (hand[i].type != -1 && i < HAND_SIZE) {
		if (hand[i].value == 1) {
			aceCount += 1;
		}
		sum += hand[i++].value;
	}
	while (sum < 12 && aceCount > 0) {
		sum += 10;
		aceCount -= 1;
	}
	return sum;
}
