
#include <SDL2/SDL.h>
#include <h/logic.h>
#include <stdio.h>
#include <stdlib.h>

int check_is_in_rect(SDL_Event e, SDL_Rect *rect, int length)
{
    int clickX = e.button.x;
    int clickY = e.button.y;
    for(int i = 0; i < length; i++)
    {
        if((clickX >= rect[i].x ) && (clickX <= rect[i].x + rect[i].w) && (clickY >= rect[i].y) && (clickY <= rect[i].y + rect[i].h))
            return 1;
    }
    return 0;
}

int check_is_rect(SDL_Event e, SDL_Rect *rect, int length)
{
    int clickX = e.button.x;
    int clickY = e.button.y;
    for(int i = 0; i < length; i++)
    {
        if((clickX >= rect[i].x ) && (clickX <= rect[i].x + rect[i].w) && (clickY >= rect[i].y) && (clickY <= rect[i].y + rect[i].h))
            return i;
    }
}

int check_is_full(game_t *game)
{
    int tmp = 0;
    for(int i = 0; i < 9; i++)
    {
        if(game->board[i] != EMPTY)
            tmp++;
    }

    return (tmp == 9)? 1 : 0;
}

int check_is_empty(int index, game_t *game)
{
    return (game->board[index] == EMPTY)? 1: 0;
}

int check_is_win(game_t *game)
{
    int player = (game->player == PLAYER_O)? 1 : 2;

    for(int i = 0; i <= 6; i += 3)
    {
        if(game->board[i] == player && game->board[i + 1] == player && game->board[i + 2] == player)
            return player;
    }

    for(int i = 0; i < 3; i++)
    {
        if(game->board[i] == player && game->board[i + 3] == player && game->board[i + 6] == player)
            return player;
    }

    if( game->board[0] == player && game->board[4] == player && game->board[8] == player || 
        game->board[2] == player && game->board[4] == player && game->board[6] == player )
            return player;

    return 0;
}

int update_state(int index, game_t *game)
{
    return game->update_state[index];
}

SDL_Rect *init_rect_game(int x, int y, int w, int h, const int length)
{
    SDL_Rect *rect = malloc(sizeof(SDL_Rect) * length);

    rect[0].x = 0;
    rect[0].y = 0;
    rect[0].h = h;
    rect[0].w = w;

    for(int i = 1; i < length; i++)
    {
        rect[i].x = rect[i - 1].x + x;
        rect[i].y = rect[i - 1].y;
        if(i % 3 == 0)
        {
            rect[i].x = 0;
            rect[i].y = rect[i - 1].y + y;
        }
        rect[i].h = h;
        rect[i].w = w;
    }
    return rect;
}

SDL_Rect *init_rect_button(int x, int y, int w, int h, const int length)
{
    SDL_Rect *rect = malloc(sizeof(SDL_Rect) * length);
    rect[0].x = x;
    rect[0].y = y;
    rect[0].h = h;
    rect[0].w = w;
    
    for(int i = 1; i < length; i++)
    {
        rect[i].x = x;
        rect[i].y = rect[i - 1].y + h + 50;
        rect[i].h = h;
        rect[i].w = w;
    }

    return rect;
    
}

void clean_board(game_t *game)
{
    for(int i = 0; i < 9; i++)
    {
        game->board[i] = EMPTY;
    }
}

void new_box(int index, game_t *game)
{
    game->board[index] = game->player;
}

void update_player(game_t *game)
{
    if(game->player == PLAYER_O)
        game->player = PLAYER_X;
    else
    {
        game->player = PLAYER_O;
    }
}



