#include "card.h"
#include "utf8.h"
#include <stdio.h>
#include <ncursesw/ncurses.h>

char prints[13] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
char suits[4][4];
char lr[4], ud[4], rd[4], ru[4], ld[4], lu[4]; 

struct Card initCard(int init)
{
	struct Card card;
	card.card = init;
	card.suit = init / 13;
	card.type = init % 13 + 1;
	card.value = (card.type > 10) ? 10 : card.type;
	return card;
}

void initSuits()
{
	toUtf8(0x2660, suits[0]);
	toUtf8(0x2663, suits[1]);
	toUtf8(0x2665, suits[2]);
	toUtf8(0x2666, suits[3]);
	toUtf8(0x2551, ud);
	toUtf8(0x2550, lr);
	toUtf8(0x2554, rd);
	toUtf8(0x255A, ru);
	toUtf8(0x2557, ld);
	toUtf8(0x255D, lu);
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

void startGap()
{
	printf("  ");
}

void cardGap()
{
	printf("  ");
}

void top()
{
	startGap();
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s", rd,lr,lr,lr,lr,lr,lr,lr,lr,lr,lr,lr,ld);
	cardGap();
}

void topText(struct Card card)
{
	startGap();
	printf("%s%2s         %s", ud,prints[card.type-1],ud);
	cardGap();
}

void mid()
{
	startGap();
	printf("%s           %s", ud,ud);
	cardGap();
}

void midText(struct Card card)
{
	startGap();
	printf("%s     %s     %s", ud,suits[card.suit],ud);
	cardGap();
}

void bot()
{
	startGap();
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s", ru,lr,lr,lr,lr,lr,lr,lr,lr,lr,lr,lr,lu);
	cardGap();
}

void botText(struct Card card)
{
	startGap();
	printf("%s         %-2s%s",ud,prints[card.type-1],ud);
	cardGap();
}

void printHand(struct Card *hand, int y)
{
    int i, len = handSize(hand);
    int height = 9;
    int width = 13;

    for (i = 0; i < len; i++) {
        WINDOW *card;
        card = newwin(height, width, 3 + 11 * y, 5 + i * 16);
        if (has_colors()) {
            init_pair(1, COLOR_BLACK, COLOR_WHITE);
        }
        wbkgd(card, COLOR_PAIR(1));
        box(card, 0, 0);
        if (hand[i].suit == 2 || hand[i].suit == 3) {
            init_pair(2, COLOR_RED, COLOR_WHITE);
            wattron(card, COLOR_PAIR(2));
        }
        mvwaddch(card, 1, 1, prints[hand[i].type - 1] | A_BOLD);
        mvwprintw(card, 4, 6, "%s", suits[hand[i].suit]);
        mvwaddch(card, 7, 11, prints[hand[i].type - 1] | A_BOLD);
        wrefresh(card);
    }
}
/*void printHand(struct Card *hand)
{
	int len = handSize(hand), i;
	for (i = 0; i < len; i++) {
		top();
	}
	printf("\n");
	for (i = 0; i < len; i++) {
		topText(hand[i]);
	}
	printf("\n");
	for (i = 0; i < len; i++) {
		mid();
	}
	printf("\n");
	for (i = 0; i < len; i++) {
		mid();
	}
	printf("\n");
	for (i = 0; i < len; i++) {
		midText(hand[i]);
	}
	printf("\n");
	for (i = 0; i < len; i++) {
		mid();
	}
	printf("\n");
	for (i = 0; i < len; i++) {
		mid();
	}
	printf("\n");
	for (i = 0; i < len; i++) {
		botText(hand[i]);
	}
	printf("\n");
	for (i = 0; i < len; i++) {
		bot();
	}
}*/
