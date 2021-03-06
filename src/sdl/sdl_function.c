#include "sdl.h"


void init_mywindow(struct game_state * gs)
{
    gs->win = malloc(sizeof(struct mywindow));
    gs->win->window = NULL;
    gs->win->window_surface = NULL;
    gs->win->bg_surface = NULL;
    gs->win->renderer = NULL;
    gs->win->textures = malloc(sizeof(struct textures));
}

void close_sdl(struct game_state *gs)
{
    SDL_FreeSurface(gs->win->window_surface);
    SDL_FreeSurface(gs->win->bg_surface);

    SDL_DestroyTexture(gs->win->textures->background);
    SDL_DestroyTexture(gs->win->textures->stone);
    SDL_DestroyTexture(gs->win->textures->hero);
    SDL_DestroyTexture(gs->win->textures->groomf);
    SDL_DestroyTexture(gs->win->textures->spike);
    SDL_DestroyTexture(gs->win->textures->rock);
    SDL_DestroyTexture(gs->win->textures->life);
    SDL_DestroyTexture(gs->win->textures->end);
    TTF_CloseFont(gs->win->font);
    TTF_Quit();

    Mix_FreeMusic(gs->win->music_bg);
    Mix_FreeMusic(gs->win->music_bg2);
    Mix_FreeChunk(gs->win->move);
    Mix_FreeChunk(gs->win->jump);
    Mix_FreeChunk(gs->win->die);
    Mix_FreeChunk(gs->win->enemy);
    Mix_FreeChunk(gs->win->stone_fall);
    Mix_FreeChunk(gs->win->pike);

    SDL_DestroyRenderer(gs->win->renderer);
    SDL_DestroyWindow(gs->win->window);
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    free(gs->win->textures);
    free(gs->win);
}

bool init_window(struct game_state *gs)
{
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
    {
        printf( "Error SDL init! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    else
    {
        gs->win->window = SDL_CreateWindow( "SDL Tutorial", 
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gs->win->window == NULL )
        {
            printf( "Error windows creation! SDL_Error: %s\n", SDL_GetError() );
            return false;
        }
        gs->win->renderer = SDL_CreateRenderer( gs->win->window, -1,
                SDL_RENDERER_ACCELERATED );
        if( gs->win->renderer == NULL )
        {
            printf( "Renderer not created!SDL Error: %s\n", SDL_GetError());
            return false;
        }
        SDL_SetRenderDrawColor( gs->win->renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            printf( "SDL_image not initialize!SDL_image Error: %s\n",
                    IMG_GetError() );
            return false;
        }

        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
                    Mix_GetError() );
        }
    }

    TTF_Init();
    gs->win->font = TTF_OpenFont("src/ressource/beauty.ttf", 1000);
    if(!gs->win->font)
        printf("error loading font\n");

    // initialization texture
    gs->win->textures->background =
        loadTexture("src/ressource/png_texture/background.png",gs);
    gs->win->textures->stone =
        loadTexture("src/ressource/png_texture/stone.png",gs);
    gs->win->textures->hero =
        loadTexture("src/ressource/png_texture/hero_christmas.png",gs);
    gs->win->textures->rock =
        loadTexture("src/ressource/png_texture/rock.png",gs);
    gs->win->textures->groomf =
        loadTexture("src/ressource/png_texture/groomf.png",gs);
    gs->win->textures->spike =
        loadTexture("src/ressource/png_texture/spike.png",gs);
    gs->win->textures->end =
        loadTexture("src/ressource/png_texture/end.png",gs);
     gs->win->textures->life =
        loadTexture("src/ressource/png_texture/cross.png",gs);   
 
    gs->win->music_bg = Mix_LoadMUS( "src/ressource/nicemusic.wav" );
    if( gs->win->music_bg  == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n",
            Mix_GetError() );
    }
    gs->win->music_bg2 = Mix_LoadMUS( "src/ressource/othernicemusic.wav" );
    gs->win->jump = Mix_LoadWAV("src/ressource/jump.wav");
    gs->win->die = Mix_LoadWAV("src/ressource/die.wav");
    gs->win->enemy = Mix_LoadWAV("src/ressource/stone_fallr.wav");
    gs->win->stone_fall = Mix_LoadWAV("src/ressource/stone_fall.wav");
    gs->win->pike = Mix_LoadWAV("src/ressource/fall.wav");
    return true;
}

SDL_Texture* loadTexture( char* path,struct game_state *gs )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path);
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path,
                IMG_GetError() );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( gs->win->renderer,
                loadedSurface);
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path,
                    SDL_GetError() );
        }
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

