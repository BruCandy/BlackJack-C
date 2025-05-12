#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "screen.h"
#include "assets.h"
#include "types.h"
#include "deck.h"
#include "hand.h"
#include "dealer.h"


int main(int argc, char* argv[]) {
    // 初期化
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    srand((unsigned int)time(NULL));

    SDL_Window* window = SDL_CreateWindow("Black Jack",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 880, 860, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    // 画像の準備
    Images images;

    SDL_Surface* surface = IMG_Load("data/images/title.gif");
    images.title = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Surface* board_surf = IMG_Load("data/images/board.gif");
    images.board = SDL_CreateTextureFromSurface(renderer, board_surf);
    SDL_FreeSurface(board_surf);

    load_images(
        renderer, images.cards, images.clubs, images.diamonds, images.spades, images.hearts, images.hands, images.keys
    );


    // テキストの準備
    Texts texts;

    TTF_Font* font_start1 = TTF_OpenFont("data/fonts/NotoSans-Regular.ttf", 33);
    TTF_Font* font_start2 = TTF_OpenFont("data/fonts/NotoSans-Regular.ttf", 28);
    TTF_Font* font_play1 = TTF_OpenFont("data/fonts/NotoSans-Regular.ttf", 18);
    TTF_Font* font_play2 = TTF_OpenFont("data/fonts/NotoSans-Regular.ttf", 20);
    TTF_Font* font_play3 = TTF_OpenFont("data/fonts/NotoSans-Regular.ttf", 15);
    TTF_Font* font_play4 = TTF_OpenFont("data/fonts/NotoSans-Regular.ttf", 21);
    TTF_Font* font_result = TTF_OpenFont("data/fonts/NotoSans-Regular.ttf", 25);
    SDL_Color color_white = {255, 255, 255, 255};
    SDL_Color color_yellow = {255, 255, 0, 255};
    SDL_Color color_black = {0, 0, 0, 255};

    // スタート画面の固定テキストの準備
    load_text(
        renderer, 0, "Press SPACE to Start the Game!!", 180, 550, font_start1, color_yellow, texts.start, texts.start_rect
    );
    load_text(
        renderer, 1, "Press SPACE to add a card, and Press UP to challenge!", 100, 605, font_start2, color_white, texts.start, texts.start_rect
    );
    load_text(
        renderer, 2, "K, J, Q are worth 10, and A is worth 1 or 11", 150, 650, font_start2, color_white, texts.start, texts.start_rect
    );
    load_text(
        renderer, 3, "= 10", 180, 730, font_start2, color_white, texts.start, texts.start_rect
    );
    load_text(
        renderer, 4, "= 10", 330, 730, font_start2, color_white, texts.start, texts.start_rect
    );
    load_text(
        renderer, 5, "= 10", 480, 730, font_start2, color_white, texts.start, texts.start_rect
    );
    load_text(
        renderer, 6, "= 1 or 11", 630, 730, font_start2, color_white, texts.start, texts.start_rect
    );

    // プレイ画面の固定テキストの準備
    load_text(
        renderer, 0, "Press SPACE to add a card", 620, 710, font_play2, color_white, texts.play, texts.play_rect
    );
    load_text(
        renderer, 1, "Press UP to challenge", 620, 755, font_play2, color_white, texts.play, texts.play_rect
    );
    load_text(
        renderer, 2, "Press DOWN to return to title", 620, 790, font_play3, color_white, texts.play, texts.play_rect
    );
    load_text(
        renderer, 3, "(You can press after the game ends)", 620, 810, font_play3, color_white, texts.play, texts.play_rect
    );
    load_text(
        renderer, 4, "Try to get as close to 21 as possible", 90, 120, font_play4, color_black, texts.play, texts.play_rect
    );
    load_text(
        renderer, 5, "without going over!", 90, 150, font_play4, color_black, texts.play, texts.play_rect
    );
    load_text(
        renderer, 6, "Dealer: ", 760, 280, font_play1, color_white, texts.play, texts.play_rect
    );
    load_text(
        renderer, 7, "Plyer: ", 760, 530, font_play1, color_white, texts.play, texts.play_rect
    );

    //リザルト画面の固定テキストの準備
    load_text(
        renderer, 0, "Player Burst! Press UP to see the result.", 100, 440, font_result, color_yellow, texts.result, texts.result_rect
    );
    load_text(
        renderer, 1, "Both Burst! It's a Tie!", 100, 440, font_result, color_yellow, texts.result, texts.result_rect
    );
    load_text(
        renderer, 2, "Press DOWN to return to Title", 100, 470, font_result, color_white, texts.result, texts.result_rect
    );
    load_text(
        renderer, 3, "Player Burst!", 100, 440, font_result, color_yellow, texts.result, texts.result_rect
    );
    load_text(
        renderer, 4, "Press DOWN to return to Title", 100, 470, font_result, color_white, texts.result, texts.result_rect
    );
    load_text(
        renderer, 5, "Dealer Burst!", 100, 440, font_result, color_yellow, texts.result, texts.result_rect
    );
    load_text(
        renderer, 6, "Press DOWN to return to Title", 100, 470, font_result, color_white, texts.result, texts.result_rect
    );
    load_text(
        renderer, 7, "Player Wins!", 100, 440, font_result, color_yellow, texts.result, texts.result_rect
    );
    load_text(
        renderer, 8, "Press DOWN to return to Title", 100, 470, font_result, color_white, texts.result, texts.result_rect
    );
    load_text(
        renderer, 9, "Dealer Wins!", 100, 440, font_result, color_yellow, texts.result, texts.result_rect
    );
    load_text(
        renderer, 10, "Press DOWN to return to Title", 100, 470, font_result, color_white, texts.result, texts.result_rect
    );
    load_text(
        renderer, 11, "It's a Tie!", 100, 440, font_result, color_yellow, texts.result, texts.result_rect
    );
    load_text(
        renderer, 12, "Press DOWN to return to Title", 100, 470, font_result, color_white, texts.result, texts.result_rect
    );



    // 状態管理 & ゲームシステムの実装
    ScreenState current = START;
    PlayState state = PLAYER_ADD;
    int running = 1;
    SDL_Event e;
    int hand_frame_player = 0;
    int hand_frame_dealer = 0;
    Uint32 lastTime = SDL_GetTicks();
    bool flag = true;
    bool is_burst = false;
    bool is_finished = false;
    int player_score = 0;
    int dealer_score = 0;
    int result = -1;
    Deck* deck = NULL;
    Hand* player_hand = NULL;
    Hand* dealer_hand = NULL;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = 0;

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && current == START) {
                current = PLAY;
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && current == PLAY && !is_burst && state == PLAYER_ADD) {
                int i = -1;
                int value;
                int suit;
                while (i == -1) {
                    value = rand() % 13;   
                    suit = rand() %4;
                    i = deck_search(value, suit, deck, 0);
                }
                deck_delete(value, suit, deck, i);
                player_hand = hand_enqueue(value, suit, player_hand, false);
                player_score = hand_score(player_hand);
                if (player_score > 21) {
                    is_burst = true;
                    result = 0;
                }
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP && current == PLAY && state == PLAYER_ADD) {
                state = DEALER_ADD;
                dealer_add(deck, &dealer_hand, &dealer_score);
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN && current == PLAY && is_finished) {
                current = START;
                state = PLAYER_ADD;
                hand_clear(player_hand);
                player_hand = NULL;

                hand_clear(dealer_hand);
                dealer_hand = NULL;
            }
        }

        if (current == START) {
            player_score = 0;
            dealer_score = 0;
            deck = deck_init(deck);
            is_burst = false;
            is_finished = false;
            Uint32 now = SDL_GetTicks();
            if ((now - lastTime) >= 500) {
                flag = !flag;
                lastTime = now;
            }
            render_start_screen(renderer, &images, &texts, flag);
        } else if (current == PLAY) {
            //プレイ画面の点数テキストの準備
            char player_score_text[16];
            sprintf(player_score_text, "%d", player_score);
            load_text(
                renderer, 0, player_score_text, 820, 530, font_play1, color_white, texts.score, texts.score_rect
            );
            char dealer_score_text[16];
            if(state != RESULT) {
                strcpy(dealer_score_text, "?");
            } else {
                sprintf(dealer_score_text, "%d", dealer_score);
            }
            load_text(
                renderer, 1, dealer_score_text, 830, 280, font_play1, color_white, texts.score, texts.score_rect
            );

            Uint32 now = SDL_GetTicks();
            if (now - lastTime >= 10) {
                hand_frame_player = (hand_frame_player + 1) % 4;
                hand_frame_dealer = (hand_frame_dealer + 1) % 4;
                lastTime = now;
            }
            
            for (int  i = 0; i<3; i++) {
                hand_updateX(player_hand);
                hand_updateX(dealer_hand);
            }

            if (state == DEALER_ADD) {
                bool all_reached = true;
                Hand* tmp = dealer_hand;
                int index = 0;
                while (tmp != NULL) {
                    int target_x = 50 + index * 60;
                    if (abs(tmp->x - target_x) > 1) {
                        all_reached = false;
                        break;
                    }
                    tmp = tmp->next;
                    index++;
                }
                if (all_reached) {
                    state = DEALER_OPEN; 
                }
            } else if (state == DEALER_OPEN) {
                bool all_opened = true;

                Hand* tmp = dealer_hand;
                while (tmp != NULL) {
                    if (tmp->state == 10) {
                        all_opened = true; 
                    } else {
                        all_opened = false;
                    }
                    tmp = tmp->next;
                }
                if (!all_opened) {
                    hand_open(dealer_hand);
                } else {
                    state = RESULT; 
                }
            } else if (state == RESULT) {
                if (player_score > 21 && dealer_score > 21) {
                    result = 1;
                } else if (player_score > 21 && dealer_score <= 21) {
                    result = 2;
                } else if (player_score <= 21 && dealer_score > 21) {
                    result = 3;
                } else if (player_score > dealer_score) {
                    result = 4;
                } else if (player_score < dealer_score) {
                    result = 5;
                } else if (player_score == dealer_score) {
                    result = 6;
                }
                is_finished = true;
            }
            render_play_screen(renderer, &images, &texts, player_hand, dealer_hand, hand_frame_player, hand_frame_dealer, result, state);
        }
    }

    // 後始末
    SDL_DestroyTexture(images.title);
    for (int i = 0; i < 10; i++) {
        SDL_DestroyTexture(images.cards[i]);
    }
    for (int i = 0; i < 13; i++) {
        SDL_DestroyTexture(images.clubs[i]);
        SDL_DestroyTexture(images.diamonds[i]);
        SDL_DestroyTexture(images.spades[i]);
        SDL_DestroyTexture(images.hearts[i]);
    }
    for (int i = 0; i < 4; i++) {
        SDL_DestroyTexture(images.hands[i]);
    }
    for (int i = 0; i < 3; i++) {
        SDL_DestroyTexture(images.keys[i]);
    }
    
    TTF_CloseFont(font_start1);
    TTF_CloseFont(font_start2);
    TTF_CloseFont(font_play1);
    TTF_CloseFont(font_play2);
    TTF_CloseFont(font_play3);
    TTF_CloseFont(font_play4);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
