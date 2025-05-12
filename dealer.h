#ifndef DEALER_H
#define DEALER_H

#include <stdbool.h>
#include "deck.h"
#include "hand.h"


void dealer_add (
    Deck* deck, Hand** dealer_hand, int* dealer_score
);

#endif