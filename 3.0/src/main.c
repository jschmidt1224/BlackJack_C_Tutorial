#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"
#include "utf8.h"
#include <curses.h>
#include "test.h"


void printHands(struct Card*, struct Card*);
int handValue(struct Card*);

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

struct Card newCard();
void shuffleDeck(struct Card *);


struct Card playerHand[HAND_SIZE], dealerHand[HAND_SIZE];
struct Card deck[52];


int main(int argc, char *argv[])
{	WINDOW *my_win;
	int startx, starty, width, height;
	int ch;

	initscr();			/* Start curses mode 		*/
	cbreak();			/* Line buffering disabled, Pass on
					 * everty thing to me 		*/
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/

	height = 3;
	width = 10;
	starty = (LINES - height) / 2;	/* Calculating for a center placement */
	startx = (COLS - width) / 2;	/* of the window		*/
	printw("Press F1 to exit");
	refresh();
	my_win = create_newwin(height, width, starty, startx);

	while((ch = getch()) != KEY_F(1))
	{	switch(ch)
		{	case KEY_LEFT:
				destroy_win(my_win);
				my_win = create_newwin(height, width, starty,--startx);
				break;
			case KEY_RIGHT:
				destroy_win(my_win);
				my_win = create_newwin(height, width, starty,++startx);
				break;
			case KEY_UP:
				destroy_win(my_win);
				my_win = create_newwin(height, width, --starty,startx);
				break;
			case KEY_DOWN:
				destroy_win(my_win);
				my_win = create_newwin(height, width, ++starty,startx);
				break;
		}
	}

	endwin();			/* End curses mode		  */
	return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void destroy_win(WINDOW *local_win)
{
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners
	 * and so an ugly remnant of window.
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window
	 * 3. rs: character to be used for the right side of the window
	 * 4. ts: character to be used for the top side of the window
	 * 5. bs: character to be used for the bottom side of the window
	 * 6. tl: character to be used for the top left corner of the window
	 * 7. tr: character to be used for the top right corner of the window
	 * 8. bl: character to be used for the bottom left corner of the window
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}


int main3()
{
    WINDOW *table;
    char ch;
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    table = newwin(5, 5, 1, 1);
    box(table, '*', '*');
    wrefresh(table);
    //refresh();

    //printw("Type any character to see it in bold\n");
    //ch = getch();

    //printw("The pressed key is ");
    //attron(A_BOLD);
    //printw("%c", ch);
    //attroff(A_BOLD);

    //refresh();
    getch();
    endwin();

    return 0;
}



int main2()
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
			//clear();
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
	printHand(player);
	printf("\n\n");
	printHand(dealer);
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
