#ifndef BARMALEY_HPP
#define BARMALEY_HPP

#include <time.h>
#include <assert.h>
#include <SDL2/SDL.h>


#define REPORT_SDL_ERROR \
    printf("in file %s, function %s, line %d:\n\t", __FILE__, __PRETTY_FUNCTION__, __LINE__); \
    printf("%s\n", SDL_GetError());


static const int SCREEN_WIDTH  = 1000;
static const int SCREEN_HEIGHT = 720;

static const SDL_Rect DEFAULT_RECT = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

static const char *BARMALEY_PATH        = "barmaley.bmp";
static const int BARMALEY_MAX_HEALTH    = 10;
static const int MAX_BARMALEY_SHOW_TIME = 5;
static const char *CAT_PATH             = "cat.bmp";
static const char *GAME_TITLE           = "Barmaley";

enum Characters {
    CAT,
    BARMALEY
};

enum Result {
    LOSE,
    WIN
};


struct WinWithSurf {
    SDL_Window  *window;
    SDL_Surface *surface;
};

struct Creature {
    int health;
    SDL_Surface *surface;
    time_t begin_time;
    time_t end_time;
};

struct Game {
    int cur_creature_type;
    WinWithSurf      main_win;
    Creature         barmaley;
    Creature              cat;
    Creature    *cur_creature;
    time_t cur_time;
    int                result;
};


int  InitSDL();


int  SwitchCreature(Game *game);

int  HitCreature(Game *game);

int  UpdateCurCharachter(Game *game);

void DestructCreature(Creature *barmaley);


int  InitBarmaley(Creature *barmaley);

void UpdateBarmaleyTime(Creature *barmaley);


int  InitCat(Creature *cat);

void UpdateCatTime(Creature *cat);



int  InitMainWin(WinWithSurf *main_win);

int  UpdateMainWin(SDL_Surface *surface, WinWithSurf *main_win);

void DestructWinWithSurf(WinWithSurf *main_win);


int  InitGame(Game *game);

int  PlayGame(Game *game);

void UpdateGameTime(Game *game);

void DestructGame(Game *game);


int IncreaseRed(SDL_Surface *surface);

int DecreaseRed(SDL_Surface *surface);


#endif /* barmaley.hpp */
