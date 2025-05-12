#ifndef HAND_H
#define HAND_H


typedef struct Hand {
    int value;
    int suit;
    float x;
    int state;
    struct Hand* next;
} Hand;

Hand* hand_enqueue (
    int value, int suit, Hand* hand, bool is_dealer
);

int hand_score (Hand* hand);

void hand_updateX(Hand* hand);

void hand_clear(Hand* deck);

Hand* hand_select(Hand* hand, int i);

void hand_open (Hand* hand);

#endif