#ifndef __CARD_H__
#define __CARD_H__

struct Card {
	int card;
	int type;
	int value;
	int suit;
};

struct Card initCard(int);




#endif