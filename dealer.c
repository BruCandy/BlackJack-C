#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "deck.h"
#include "hand.h"
#include "dealer.h"


void dealer_add (Deck* deck, Hand** dealer_hand, int* dealer_score) {
    while (*dealer_score <= 16) {
        int i = -1;
        int value;
        int suit;
        while (i == -1) {
            value = rand() % 13;   
            suit = rand() % 4;
            i = deck_search(value, suit, deck, 0);
        }
        deck_delete(value, suit, deck, i);
        *dealer_hand = hand_enqueue(value, suit, *dealer_hand, true);
        *dealer_score = hand_score(*dealer_hand);
    }
}
