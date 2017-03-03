#ifndef __CARD_H__
#define __CARD_H__

#define SINGLE_SIZE 52
#define NUM_DECKS 1
#define DECK_SIZE SINGLE_SIZE * NUM_DECKS

struct Card {
	int type;
	int value;
	int suit;
};

extern char prints[14][10];
extern char suits[4][4];
extern struct Card deck[];

struct Card initCard(int);
void initSuits();
void initDeck();
void shuffleDeck(struct Card*);
#endif
