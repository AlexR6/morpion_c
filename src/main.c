#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <h/logic.h>
#include <h/render.h>

//gcc src/*.c -o bin/Morpion -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

int main(int argc, char *argv[])
{   
    


    SDL_Rect *rect_game = init_rect_game(200, 200, RECT_WIDTH, RECT_HEIGTH, 9);
    SDL_Rect *rect_menu = init_rect_button(205, 150, 190, 80, 3);
    SDL_Rect rect_text = {100, 25, 400, 90};
    SDL_Rect rect_return = {25, 25, 50, 50};

    SDL_Event e;    

    game_t game = {
        .board =  {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        .player = PLAYER_O,
        .state = FIRST_STATE,
        .update_state = {RETRY_STATE, RULES_STATE, QUIT_STATE}
    };

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erreur sur SDL_Init %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("Morpion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "Erreur sur SDL_CreateWindow %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    set_icon_window(window);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
        fprintf(stderr, "Erreur sur SDL_CreateWindow %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    while(game.state != QUIT_STATE)
    {
        while(SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    switch (game.state)
                    {
                    case RUNNING_STATE:
                        if(check_is_empty(check_is_rect(e, rect_game, 9), &game) && !check_is_full(&game))
                        {
                            new_box(check_is_rect(e, rect_game, 9), &game);
                            
                            if(check_is_win(&game) != 0)
                            {
                                renderer_game(renderer, &game, rect_game);
                                SDL_RenderPresent(renderer);                
                                game.state = (game.player == PLAYER_O)? PLAYER_O_WON_STATE : PLAYER_X_WON_STATE;
                                SDL_Delay(500);
                            }
                            else
                                update_player(&game);

                            if(check_is_full(&game) && game.state != PLAYER_O_WON_STATE && game.state != PLAYER_X_WON_STATE)
                                game.state = TIE_STATE;
                        }
                        break;

                    case PLAYER_O_WON_STATE:
                    case PLAYER_X_WON_STATE:
                    case TIE_STATE:
                    case FIRST_STATE:
                        if(check_is_in_rect(e, rect_menu, 3))
                        {
                            game.state = update_state(check_is_rect(e, rect_menu, 3), &game);
                            if(game.state == RETRY_STATE)
                            {
                                clean_board(&game);
                                game.player = PLAYER_O;
                                game.state = RUNNING_STATE;
                            }
                        }
                        break;

                    case RULES_STATE:
                        if(check_is_in_rect(e, &rect_return, 1))
                        {
                            game.state = FIRST_STATE;
                            clean_board(&game);
                            game.player = PLAYER_O;
                        }
                        break;

                    default:
                        break;
                    }

                    break;
                case SDL_QUIT:
                    game.state = QUIT_STATE;
                    break;
                default:
                    break;
            }
        }
        switch (game.state)
        {
            case RUNNING_STATE:
                renderer_base(renderer);
                renderer_game(renderer, &game, rect_game);                    
                break;
            case PLAYER_O_WON_STATE:
            case TIE_STATE:
            case PLAYER_X_WON_STATE:
                renderer_base(renderer);
                display_score(renderer, &game, rect_text, rect_menu);
                break;
            case FIRST_STATE:
                renderer_base(renderer);
                display_score(renderer, &game, rect_text, rect_menu);
                break;
            case RULES_STATE:
                renderer_base(renderer);
                display_rules(renderer, rect_return);
                break;
            default:
                break;
        }  
        SDL_RenderPresent(renderer);

    }
    free(rect_menu);
    free(rect_game);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}


