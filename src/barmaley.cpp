#include "../include/barmaley.hpp"


int InitSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	return 0;
}


int UpdateMainWin(SDL_Surface *surface, WinWithSurf *main_win) {
    assert(surface);
    assert(main_win);

    if (SDL_BlitSurface(surface, NULL, main_win->surface, NULL)) {
        REPORT_SDL_ERROR
        return 1;
    }

    if (SDL_UpdateWindowSurface(main_win->window)) {
        REPORT_SDL_ERROR
        return 1;
    }
    return 0;
}

void UpdateGameTime(Game *game) {
    assert(game);

    game->cur_time = time(NULL);
}


int InitMainWin(WinWithSurf *main_win) {
	if (!(main_win->window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0))) {
        REPORT_SDL_ERROR
        return 1;
    }

    if (!(main_win->surface = SDL_GetWindowSurface(main_win->window))) {
        REPORT_SDL_ERROR
        return 1;
    }

    return 0;
}

void DestructWinWithSurf(WinWithSurf *main_win) {
    SDL_FreeSurface(main_win->surface);
    SDL_DestroyWindow(main_win->window);
}


int InitBarmaley(Creature *barmaley) {
    assert(barmaley);

    if (!(barmaley->surface = SDL_LoadBMP(BARMALEY_PATH))) {
        REPORT_SDL_ERROR
        return 1;
    }
    barmaley->begin_time = 0;
    barmaley->end_time = 0;
    barmaley->health = 1 + rand() % BARMALEY_MAX_HEALTH;
    return 0;
};

void UpdateBarmaleyTime(Creature *barmaley) {
    assert(barmaley);

    barmaley->begin_time = time(NULL);
    barmaley->end_time = barmaley->begin_time + 1 + rand() % MAX_BARMALEY_SHOW_TIME;
}

void DestructCreature(Creature *barmaley) {
    SDL_FreeSurface(barmaley->surface);
}


int InitCat(Creature *cat) {
    assert(cat);

    if (!(cat->surface = SDL_LoadBMP(CAT_PATH))) {
        REPORT_SDL_ERROR
        return 1;
    }
    cat->begin_time = 0;
    cat->end_time   = 0;
    cat->health = 1;
    return 0;
}

void UpdateCatTime(Creature *cat) {
    assert(cat);

    cat->begin_time = time(NULL);
    cat->end_time = cat->begin_time + 1;
}

void SwitchCreature(Game *game) {
    assert(game);

    switch (game->cur_creature_type) {
        case CAT:
            game->cur_creature_type = BARMALEY;
            game->cur_creature = &game->barmaley;
            UpdateBarmaleyTime(&game->barmaley);
            break;
        case BARMALEY:
            game->cur_creature_type = CAT;
            game->cur_creature = &game->cat;
            UpdateCatTime(&game->cat);
            break;
        default:
            break;
    }

    UpdateMainWin(game->cur_creature->surface, &game->main_win);
}


int InitGame(Game *game) {
	assert(game);

	if (InitSDL()) {
		return 1;
	}

    srand(time(NULL));

    game->cur_creature_type = rand() % 2;

    if (InitMainWin(&game->main_win)) {
        return 1;
    }

    if (InitBarmaley(&game->barmaley)) {
        return 1;
    }

    if (InitCat(&game->cat)) {
        return 1;
    }

    SwitchCreature(game);
    UpdateGameTime(game);
    game->result = LOSE;
    return 0;
}


void DestructGame(Game *game) {
    assert(game);

    DestructWinWithSurf(&game->main_win);
    DestructCreature(&game->barmaley);
    DestructCreature(&game->cat);
    SDL_Quit();
}


int IncreaseRed(SDL_Surface *surface) {
    assert(surface);

    if (SDL_LockSurface(surface)) {
        REPORT_SDL_ERROR
        return 1;
    }

    int w = surface->w,
        h = surface->h;
    Uint8 *pixels = (Uint8 *)surface->pixels;
    Uint8 *pixel  = pixels;
    
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            pixel += 3;
            pixel[2] = pixel[2] ? pixel[2] + (255 - pixel[2]) / 2 : 128;
        }
    }

    SDL_UnlockSurface(surface);
    return 0;
}


int DecreaseRed(SDL_Surface *surface) {
    assert(surface);

    if (SDL_LockSurface(surface)) {
        REPORT_SDL_ERROR
        return 1;
    }

    int w = surface->w,
        h = surface->h;
    Uint8 *pixels = (Uint8 *)surface->pixels;
    Uint8 *pixel  = pixels;
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            pixel += 3;
            pixel[2] -= 255 - pixel[2];
        }
    }

    SDL_UnlockSurface(surface);
    return 0;
}





int HitCreature(Game *game) {
    assert(game);

    Creature *stricken = game->cur_creature;
    stricken->health--;

    if (IncreaseRed(stricken->surface)) {
        return 1;
    }

    if (UpdateMainWin(stricken->surface, &game->main_win)) {
        return 1;
    }

    SDL_Delay(100);

    if (DecreaseRed(stricken->surface)) {
        return 1;
    }

    return 0;
}



void UpdateCurCharachter(Game *game) {
    assert(game);

    UpdateGameTime(game);
    if (game->cur_time >= game->cur_creature->end_time) {
        SwitchCreature(game);
    }
}



int PlayGame(Game *game) {
    if (InitGame(game)) {
        return 1;
    }

	SDL_Event event = {};
	bool quit = false;

    while (!quit) {
        UpdateCurCharachter(game);
        while (SDL_PollEvent(&event) && !quit) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    HitCreature(game);
                    if (game->cat.health <= 0) {
                        game->result = LOSE;
                        quit = true;
                    } else if (game->barmaley.health <= 0) {
                        game->result = WIN;
                        quit = true;
                    }
                    break;
                default:
                    break;
            }
        }

        if (UpdateMainWin(game->cur_creature->surface, &game->main_win)) {
            return 1;
        }
    }

    switch (game->result) {
        case LOSE:
            printf("YOU KILLED MY CAT!!!\nLOSE\n");
            break;
        case WIN:
            printf("WIN\n");
            break;
        default:
            break;
    }

    DestructGame(game);
	return 0;
}
