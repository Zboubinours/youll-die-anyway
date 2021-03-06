#include "load_map.h"
#include "events.h"

static int is_on_ground(struct game_state *gs)
{
    int posy = gs->player->entity->pos.y;
    int posx = gs->player->entity->pos.x;
    return gs->map->block_type[posy + 1][posx] == ROCK
            || gs->map->block_type[posy + 1][posx + 1] == ROCK;
}

void game_events(struct game_state *game_state)
{
    SDL_Event e;
    SDL_PollEvent(&e);
    struct player *player = game_state->player;
    if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_UP:
            if (player->jump == 0 && is_on_ground(game_state))
            {
                Mix_PlayChannel(-1,game_state->win->jump,0);
                player->jump = 2.5;
            }
            break;
        case SDLK_q:
            game_state->quit = true;
            break;
        case SDLK_r:
            game_state->player->entity->pos = game_state->player->start;
            break;
        case SDLK_RIGHT:
            game_state->player->entity->dir = RIGHT;
            break;
        case SDLK_LEFT:
            game_state->player->entity->dir = LEFT;
            break;
        case SDLK_p:
            load_next_map(game_state);
        default:
            break;
        }
   }
}
