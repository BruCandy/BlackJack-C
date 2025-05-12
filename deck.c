#include <stdio.h>
#include <stdlib.h>
#include "deck.h"


Deck* deck_enqueue(int value, int suit, Deck* hand) {
    Deck *tmp = malloc(sizeof(Deck));
    tmp->value = value;
    tmp->suit = suit;
    tmp->next = hand;

    return tmp;
}

Deck* deck_init(Deck* deck) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            deck = deck_enqueue (j, i, deck);
        }
    }
    return deck;
}

int deck_search(int value, int suit, Deck* deck, int i) {
    if (deck != NULL) {
        if (deck->value == value && deck->suit == suit) {
            return i;
        }
        return deck_search(value, suit, deck->next, i+1);
    }
    return -1;
}

Deck* deck_delete(int value, int suit, Deck* deck, int i) {
    Deck* prev = deck;
    Deck* target;
    Deck* next;
    if (i == 0) {
        Deck* tmp = deck->next;
        free(deck);
        return tmp;
    }
    while (i > 1) {
        prev = prev->next;
        i--;
    }
    target = prev->next; 
    next = target->next;
    free(target);
    prev->next = next;

    return deck;
}

void deck_clear(Deck* deck) {
    while (deck != NULL) {
        Deck* tmp = deck;
        deck = deck->next;
        free(tmp);
    }
}