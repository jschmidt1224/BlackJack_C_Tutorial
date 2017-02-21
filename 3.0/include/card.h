#ifndef __CARD_H__
#define __CARD_H__

#define HAND_SIZE 5

struct Card {
	int card;
	int type;
	int value;
	int suit;
};

extern char prints[13];
extern char suits[4][4];

struct Card initCard(int);
void initSuits();
int handSize(struct Card*);

void startGap();
void cardGap();
void top();
void topText(struct Card);
void mid();
void midText(struct Card);
void bot();
void botText(struct Card);
void printHand(struct Card *, int y);




#endif
