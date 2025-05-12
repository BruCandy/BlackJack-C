#include "screen.h"
#include "hand.h"
#include "assets.h"
#include "types.h"


void render_start_screen(SDL_Renderer* renderer, Images* images, Texts* texts, bool flag) {
    SDL_Rect title_rect = {100, -50, 800, 800};
    SDL_Rect club_rect = {110, 700, 80, 100};
    SDL_Rect diamond_rect = {260, 700, 80, 100};
    SDL_Rect spade_rect = {410, 700, 80, 100};
    SDL_Rect heart_rect = {560, 700, 80, 100};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, images->title, NULL, &title_rect);
    SDL_RenderCopy(renderer, images->clubs[12], NULL, &club_rect);
    SDL_RenderCopy(renderer, images->diamonds[11], NULL, &diamond_rect);
    SDL_RenderCopy(renderer, images->spades[10], NULL, &spade_rect);
    SDL_RenderCopy(renderer, images->hearts[0], NULL, &heart_rect);
    for (int i = 0; i<7; i++) {
        if (i != 0) {
            SDL_RenderCopy(renderer, texts->start[i], NULL, &texts->start_rect[i]);
        } else {
            if (flag) {
                SDL_RenderCopy(renderer, texts->start[i], NULL, &texts->start_rect[i]);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

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
) {
    SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, images->hands[hand_frame_player], NULL, &(SDL_Rect){10, 600, 300, 300});
    SDL_RenderCopyEx(renderer, images->hands[hand_frame_dealer], NULL, &(SDL_Rect){600, -30, 300, 300}, 0, NULL, SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    SDL_RenderCopy(renderer, images->board, NULL, &(SDL_Rect){30, -40, 450, 350});
    SDL_RenderCopy(renderer, images->keys[0], NULL, &(SDL_Rect){410, 720, 200, 200});
    SDL_RenderCopy(renderer, images->keys[1], NULL, &(SDL_Rect){500, 600, 150, 150});
    SDL_RenderCopy(renderer, images->keys[2], NULL, &(SDL_Rect){410, 710, 200, 200});

    for (int i = 0; i < 8; i++) {
        SDL_RenderCopy(renderer, texts->play[i], NULL, &texts->play_rect[i]);
    }

    for (int i = 0; i < 2; i++) {
        SDL_RenderCopy(renderer, texts->score[i], NULL, &texts->score_rect[i]);
    }

    Hand* current = player_hand;
    while (current != NULL) {
        SDL_Rect card_rect = {current->x, 550, 80, 100};
        SDL_Texture* texture = get_card_texture(*images, current->value, current->suit, current->state);
        SDL_RenderCopy(renderer, texture, NULL, &card_rect);
        current = current->next;
    }

    if (result_flag == 0) {
        SDL_RenderCopy(renderer, texts->result[0], NULL, &texts->result_rect[0]);
    }
    if (state == RESULT && result_flag >= 1 && result_flag <= 7) {
        int index = (result_flag - 1) * 2 + 1; 
        SDL_RenderCopy(renderer, texts->result[index], NULL, &texts->result_rect[index]);
        SDL_RenderCopy(renderer, texts->result[index + 1], NULL, &texts->result_rect[index + 1]);
    }

    if(state == DEALER_ADD) {
        Hand* current_dealer = dealer_hand;
        while (current_dealer != NULL) {
            SDL_Rect card_rect = {current_dealer->x, 320, 80, 100};
            SDL_Texture* texture = get_card_texture(*images, current_dealer->value, current_dealer->suit, current_dealer->state);
            SDL_RenderCopy(renderer, texture, NULL, &card_rect);
            current_dealer = current_dealer->next;
        }
    } else if(state == DEALER_OPEN || state == RESULT) {
        Hand* current_dealer = dealer_hand;
        while (current_dealer != NULL) {
            SDL_Rect card_rect = {current_dealer->x, 320, 80, 100};
            SDL_Texture* texture = get_card_texture(*images, current_dealer->value, current_dealer->suit, current_dealer->state);
            SDL_RenderCopy(renderer, texture, NULL, &card_rect);
            current_dealer = current_dealer->next;
        }
    }

    SDL_RenderPresent(renderer);
}

