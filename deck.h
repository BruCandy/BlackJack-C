#ifndef DECK_H
#define DECK_H


typedef struct Deck {
    int value;
    int suit;
    struct Deck* next;
} Deck;

Deck* deck_enqueue(
    int value, int suit, Deck* hand
);

Deck* deck_init(Deck* deck);

int deck_search(
    int value, int suit, Deck* deck, int i
);

Deck* deck_delete(
    int value, int suit, Deck* deck, int i
);

void deck_clear(Deck* deck);

#endif