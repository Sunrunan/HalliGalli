#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string.h>
#include <stdbool.h>
#include "GameData.h"
#ifndef CONTROLFUNCTION_H_INCLUDED
#define CONTROLFUNCTION_H_INCLUDED
SDL_Surface* load_image(char* filename);
void apply_surface(int x,int y,SDL_Surface* source,SDL_Surface* destination,SDL_Rect *clip);
bool init();
bool load_files();
void clean_up();
bool end_game();
bool ring();
SDL_Surface* write1(int number);
#endif // CONTROLFUNCTION_H_INCLUDED
