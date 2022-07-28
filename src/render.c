#include <SDL2/SDL.h>
#include <h/logic.h>
#include <h/render.h>
#include <stdio.h>
#include <stdlib.h>

void renderer_base(SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
    SDL_Surface *surface = SDL_LoadBMP("img/render_bg.bmp");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);
}
void renderer_game(SDL_Renderer *renderer, game_t *game, SDL_Rect *rect)
{
    for (int i = 0; i < 9; i++)
    {
        if(game->board[i] != EMPTY)
        {
            if(game->board[i] == PLAYER_O)
            {
                SDL_Surface *surface = SDL_LoadBMP("img/circle.bmp");
                SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);
                SDL_RenderCopy(renderer, texture, NULL, &rect[i]);
                SDL_DestroyTexture(texture);
            }
            else
            {
                SDL_Surface *surface = SDL_LoadBMP("img/cross.bmp");
                SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);
                SDL_RenderCopy(renderer, texture, NULL, &rect[i]);
                SDL_DestroyTexture(texture);
            }
        }        
    }
    
    SDL_SetRenderDrawColor(renderer, 102, 102, 102, 255);

    for(int i = 0 ; i < 5; i++)
    {
        SDL_RenderDrawLine(renderer, 198 + i, 0, 198 + i, 600);
    }

    for(int i = 0 ; i < 5; i++)
    {
        SDL_RenderDrawLine(renderer, 398 + i, 0, 398 + i, 600);
    }

    for(int i = 0 ; i < 5; i++)
    {
        SDL_RenderDrawLine(renderer, 0, 198 + i, 600, 198 + i);
    }

    for(int i = 0 ; i < 5; i++)
    {
        SDL_RenderDrawLine(renderer, 0, 398 + i, 600, 398 + i);
    }

}

void display_score(SDL_Renderer *renderer, game_t *game, SDL_Rect rect_text ,SDL_Rect *rect)
{   
    SDL_Surface *surface = NULL;
    switch (game->state)
    {
        case PLAYER_O_WON_STATE:
            surface = SDL_LoadBMP("img/player_o_won.bmp");
            break;
        case PLAYER_X_WON_STATE:
            surface = SDL_LoadBMP("img/player_x_won.bmp");
            break;
        case TIE_STATE:
            surface = SDL_LoadBMP("img/tie.bmp");
            break;
        default:
            break;
    }
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect_text);
    SDL_DestroyTexture(texture);

    for(int i = 0; i < 3; i++)
    {
        SDL_Surface *surface = NULL;
        switch (i)
        {
            case 0:
                surface = (game->state != FIRST_STATE) ? SDL_LoadBMP("img/retry.bmp") : SDL_LoadBMP("img/play.bmp");
                break;
            case 1:
                surface = SDL_LoadBMP("img/rules.bmp");
                break;
            case 2:
                surface = SDL_LoadBMP("img/quit.bmp");
                break;
            default:
                break;
        }
        
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect[i]);
        SDL_DestroyTexture(texture);
    }
}

void display_rules(SDL_Renderer *renderer, SDL_Rect rect)
{
    SDL_Rect rect_text = {110, 88, 390, 423};
    SDL_Surface *surface_bg = SDL_LoadBMP("img/rules_text.bmp");
    SDL_Texture *texture_bg = SDL_CreateTextureFromSurface(renderer, surface_bg);
    SDL_FreeSurface(surface_bg);
    SDL_RenderCopy(renderer, texture_bg, NULL, &rect_text);
    SDL_DestroyTexture(texture_bg);

    SDL_Surface *surface = SDL_LoadBMP("img/return.bmp");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

void set_icon_window(SDL_Window *window)
{
    SDL_Surface *surface = SDL_LoadBMP("img/icon.bmp");
    SDL_SetWindowIcon(window, surface);
    SDL_FreeSurface(surface);
}