#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hand.h"


#define MAX_SCORE_NUM 100

Hand* hand_enqueue(int value, int suit, Hand* hand, bool is_dealer) {
    Hand* new_hand = malloc(sizeof(Hand));
    new_hand->value = value;
    new_hand->suit = suit;
    new_hand->x = 900;
    new_hand->next = NULL;
    if (is_dealer) {
        new_hand->state = 0;
    } else {
        new_hand->state = 10;
    }

    if (hand == NULL) {
        return new_hand;
    }

    Hand* tmp = hand;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = new_hand;
    return hand;
}

void hand_updateX(Hand* hand) {
    int i = 0;
    int speed = 10;

    while (hand != NULL) {
        int target_x = 50 + i * 60;
        int dx = target_x - hand->x;

        if (abs(dx) <= speed) {
            hand->x = target_x;
        } else {
            hand->x += (dx > 0) ? speed : -speed;
        }

        hand = hand->next;
        i++;
    }
}

void hand_clear(Hand* deck) {
    while (deck != NULL) {
        Hand* tmp = deck;
        deck = deck->next;
        free(tmp);
    }
}

Hand* hand_select(Hand* hand, int i) {
    int j = 0;
    while(j < i) {
        if (hand == NULL) {
            return NULL;
        }
        j += 1;
        hand = hand->next;
    }
    return hand;
}

void calculate_score_combinations (Hand* hand, int* scores, int* score_count, int index, int sum) {
    if (hand == NULL) {
        scores[*score_count] = sum;
        (*score_count)++;
        return;
    }

    if (hand->value == 0) {
        calculate_score_combinations(hand->next, scores, score_count, index + 1, sum + 1);
        calculate_score_combinations(hand->next, scores, score_count, index + 1, sum + 11);
    } else {
        int value = (hand->value + 1 > 10) ? 10 : hand->value + 1;
        calculate_score_combinations(hand->next, scores, score_count, index + 1, sum + value);
    }
}

int hand_score (Hand* hand) {
    int score = -1; 
    int* scores = malloc(sizeof(int) * MAX_SCORE_NUM);
    int score_count = 0;
    calculate_score_combinations(hand, scores, &score_count, 0, 0);
    for (int i = 0; i < score_count; i++) {
        int tmp_score = scores[i];
        if (tmp_score <= 21) {
            if (score == -1 || tmp_score > score) {
                score = tmp_score;
            }
        } else if (score == -1) {
            score = tmp_score;
        } else if (tmp_score > 21 && tmp_score < score && score > 21) {
            score = tmp_score;
        }
    }
    free(scores);
    return score;
}

void hand_open(Hand* hand) {
    Hand* tmp = hand;
    while (tmp != NULL) {
        if (tmp->state < 10) {
            tmp->state += 1;
        } else {
            tmp->state = 10;
        }
        tmp = tmp->next;
    }
}
