#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "hand.h"
#include "types.h"


void render_start_screen(
    SDL_Renderer* renderer, 
    Images* images, 
    Texts* texts, 
    bool flag
);

void render_play_screen(
    SDL_Renderer* renderer, 
    Images* images, 
    Texts* texts,
    Hand* player_hand, 
    Hand* dealer_hand, 
    int hand_frame_player, 
    int hand_frame_dealer,
    int result_flag,
    PlayState state
);

#endif
