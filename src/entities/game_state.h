#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

#include "entity.h"
#include "list.h"

struct textures
{
    SDL_Texture *background;
    SDL_Texture *stone;
    SDL_Texture *rock;
    SDL_Texture *hero;
    SDL_Texture *groomf;
    SDL_Texture *spike;
};

struct mywindow
{
    SDL_Window * window;
    SDL_Surface * window_surface;
    SDL_Surface * bg_surface;
    SDL_Renderer * renderer;
    struct textures *textures;
    TTF_Font * font;
};

struct game_state
{
    struct player *player;
    struct entity_list *list;
    struct pos end_pos;
    struct map *map;
    struct mywindow *win;
    bool quit;
    bool restart;
};


#include "sdl.h"

struct game_state *game_state_create(void);

void game_state_destroy(struct game_state *game_state);

#endif /* GAME_STATE_H */
