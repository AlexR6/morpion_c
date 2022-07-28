#ifndef LOGIC_H_
#define LOGIC_H_

#define EMPTY 0
#define PLAYER_O 1
#define PLAYER_X 2

#define RUNNING_STATE 0
#define PLAYER_O_WON_STATE 1
#define PLAYER_X_WON_STATE 2
#define TIE_STATE 3
#define QUIT_STATE 4
#define RETRY_STATE 5
#define RULES_STATE 6
#define FIRST_STATE 7

typedef struct 
{
    int board[9];
    int player;
    int state;
    int update_state[3];
} game_t;


int check_is_in_rect(SDL_Event e, SDL_Rect *rect, int length);
int check_is_rect(SDL_Event e, SDL_Rect rect[], int length);
int check_is_full(game_t *game);
int check_is_empty(int index, game_t *game);
int check_is_win(game_t *game);
int check_is_win(game_t *game);
int update_state(int index, game_t *game);

SDL_Rect *init_rect_game(int x, int y, int h, int w, int length);
SDL_Rect *init_rect_button(int x, int y, int h, int w, int length);

void update_player(game_t *game);
void new_box(int index, game_t *game);
void clean_board(game_t *game);

#endif