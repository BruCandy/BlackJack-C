#ifndef TYPES_H
#define TYPES_H

#include <SDL2/SDL.h>

typedef enum {
    START,
    PLAY
} ScreenState;

typedef enum {
    PLAYER_ADD,
    DEALER_ADD,
    DEALER_OPEN,
    RESULT
} PlayState;

typedef struct {
    SDL_Texture* title;
    SDL_Texture* board;
    SDL_Texture* cards[10];
    SDL_Texture* clubs[13];
    SDL_Texture* diamonds[13];
    SDL_Texture* spades[13];
    SDL_Texture* hearts[13];
    SDL_Texture* hands[4];
    SDL_Texture* keys[3];
} Images;

typedef struct {
    SDL_Texture* start[7];
    SDL_Rect start_rect[7];
    SDL_Texture* play[8];
    SDL_Rect play_rect[8];
    SDL_Texture* result[13];
    SDL_Rect result_rect[13];
    SDL_Texture* score[2];
    SDL_Rect score_rect[2];
} Texts;

#endif
