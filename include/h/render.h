#ifndef RENDER_H_
#define RENDER_H_

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

#define RECT_WIDTH 200
#define RECT_HEIGTH 200

void display_score(SDL_Renderer *renderer, game_t *game, SDL_Rect rect_text, SDL_Rect *rect);
void display_rules(SDL_Renderer *renderer, SDL_Rect rect);
void renderer_base(SDL_Renderer *renderer);
void renderer_game(SDL_Renderer *renderer, game_t *game, SDL_Rect *rect);
void set_icon_window(SDL_Window *window);

#endif