#include "card.h"
#include "utf8.h"
#include <stdio.h>
#include <stdlib.h>

char prints[14][10] = {"   ", "A","2","3","4","5","6","7","8","9","10","J","Q","K"};
char suits[4][4]; 

struct Card deck[DECK_SIZE];

struct Card initCard(int init)
{
	struct Card card;
    init = init % 52;
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
    toUtf8(0x2588, &prints[0][0]);
    toUtf8(0x2588, &prints[0][3]);
    toUtf8(0x2588, &prints[0][6]);
}

void initDeck()
{
    int i;
    for (i = 0; i < DECK_SIZE; i++) {
        deck[i] = initCard(i);
    }
    shuffleDeck(deck);
}


void shuffleDeck(struct Card *deck)
{
    int i;
    for (i = 0; i < DECK_SIZE; i++) {
        struct Card tmp = deck[i];
        int shuffle = rand() % DECK_SIZE;
        deck[i] = deck[shuffle];
        deck[shuffle] = tmp;
    }
}



