#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "assets.h"
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
) {
    for (int i = 0; i < 10; i++) {
        char filename[64];
        sprintf(filename, "data/images/cards/card%d.gif", i + 1);
        SDL_Surface* surf = IMG_Load(filename);
        cards[i] = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }

    for (int i = 0; i < 13; i++) {
        char filename[64];
        sprintf(filename, "data/images/cards/club/club%d.gif", i + 1);
        SDL_Surface* surf = IMG_Load(filename);
        clubs[i] = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }

    for (int i = 0; i < 13; i++) {
        char filename[64];
        sprintf(filename, "data/images/cards/diamond/diamond%d.gif", i + 1);
        SDL_Surface* surf = IMG_Load(filename);
        diamonds[i] = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }

    for (int i = 0; i < 13; i++) {
        char filename[64];
        sprintf(filename, "data/images/cards/spade/spade%d.gif", i + 1);
        SDL_Surface* surf = IMG_Load(filename);
        spades[i] = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }

    for (int i = 0; i < 13; i++) {
        char filename[64];
        sprintf(filename, "data/images/cards/heart/heart%d.gif", i + 1);
        SDL_Surface* surf = IMG_Load(filename);
        hearts[i] = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }

    for (int i = 0; i < 4; i++) {
        char filename[64];
        sprintf(filename, "data/images/hand/hand%d.gif", i + 1);
        SDL_Surface* surf = IMG_Load(filename);
        hands[i] = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }

    for (int i = 0; i < 3; i++) {
        char filename[64];
        sprintf(filename, "data/images/key/key%d.gif", i + 1);
        SDL_Surface* surf = IMG_Load(filename);
        keys[i] = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }
}

SDL_Texture* get_card_texture(Images images, int value, int suit, int state) {
    if (state == 10) {
        switch (suit) {
            case 0: return images.clubs[value];
            case 1: return images.diamonds[value];
            case 2: return images.spades[value];
            case 3: return images.hearts[value];
        } 
    } else {
        switch (state) {
            case 0: return images.cards[0];
            case 1: return images.cards[1];
            case 2: return images.cards[2];
            case 3: return images.cards[3];
            case 4: return images.cards[4];
            case 5: return images.cards[5];
            case 6: return images.cards[6];
            case 7: return images.cards[7];
            case 8: return images.cards[8];
            case 9: return images.cards[9];
        }
    }
    return NULL;
}

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
) {
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect rect = {x, y, 0, 0};
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

    textures[num] = texture;
    rects[num] = rect;
}