#include "card.h"


struct Card initCard(int init)
{
	struct Card card;
	card.card = init;
	card.suit = init / 13;
	card.type = init % 13 + 1;
	card.value = (card.type > 10) ? 10 : card.type;
	return card;
}