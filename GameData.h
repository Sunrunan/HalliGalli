#ifndef GAMEDATA_H_INCLUDED
#define GAMEDATA_H_INCLUDED
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32
#define TOTAL 52
#define NX1 30
#define NX2 580
#define NX3 580
#define NX4 30
#define NY1 150
#define NY2 150
#define NY3 400
#define NY4 390
#define CX1 140
#define CY1 40
#define CX2 360
#define CY2 40
#define CX3 360
#define CY3 280
#define CX4 140
#define CY4 280
#define WIN true
#define LOSE false
SDL_Event event;
SDL_Surface* result;
SDL_Surface* help1;
SDL_Surface* help2;
SDL_Surface* screen;
SDL_Surface* background1;
SDL_Surface* background2;
SDL_Surface* card;
SDL_Surface* bell;
SDL_Surface* bell1;
SDL_Rect clip[7];
SDL_Surface *play_card_number;
SDL_Surface *computer1_card_number;
SDL_Surface *computer2_card_number;
SDL_Surface *computer3_card_number;
TTF_Font *font;
Mix_Music *bgm;
Mix_Chunk *ring_bell;
Mix_Chunk *deal;
Mix_Chunk *right;
Mix_Chunk *wrong;
Mix_Music *lose;
Mix_Music *win;
Mix_Chunk *press;
int switch1,switch2,player_number,number[4],player_card[TOTAL],computer1_card[TOTAL],computer2_card[TOTAL],computer3_card[TOTAL],table_card[TOTAL],head[5],tail[5],card_number[4];
bool game;
#endif // GAMEDATA_H_INCLUDED
