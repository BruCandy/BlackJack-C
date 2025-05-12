#ifndef ASSETS_H
#define ASSETS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "types.h"


void load_images(
    SDL_Renderer* renderer, 
    SDL_Texture** cards, 
    SDL_Texture** clubs, 
    SDL_Texture** diamonds, 
    SDL_Texture** spades, 
    SDL_Texture** hearts, 
    SDL_Texture** hands, 
    SDL_Texture** keys
);

SDL_Texture* get_card_texture(
    Images images, int value, int suit, int state
);

void load_text(
    SDL_Renderer* renderer, 
    int num,
    char text[],
    int x, 
    int y,
    TTF_Font* font,
    SDL_Color color,
    SDL_Texture** textures,
    SDL_Rect* rects
);

#endif