#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "ControlFunction.h"
#include "GameData.h"
SDL_Color textColor={255,255,0};
SDL_Surface* write1(int number)
{
    SDL_Surface* ans=NULL;
    char cnumber[2];
    if(number>9)
    {
	cnumber[0]=48+number/10;
	cnumber[1]=48+number%10;
    }
    else 
    {
	cnumber[0]=48+number%10;
    }
    ans=TTF_RenderText_Solid(font,cnumber,textColor);
    return ans;
}

SDL_Surface* load_image(char* filename)
{
    SDL_Surface* loadedImage=NULL;
    SDL_Surface* optimizedImage=NULL;
    loadedImage=IMG_Load(filename);
    if(loadedImage!=NULL)
    {
        optimizedImage=SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
    }
    if(optimizedImage!=NULL)
    {
        Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 255, 255, 255 );
        SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
    }
    return optimizedImage;
}
void apply_surface(int x,int y,SDL_Surface* source,SDL_Surface* destination,SDL_Rect *clip)
{
    SDL_Rect offset;
    offset.x=x;
    offset.y=y;
    SDL_BlitSurface(source,clip,destination,&offset);
}
bool init()
{
    if(SDL_Init( SDL_INIT_EVERYTHING )==-1)
        return false;
    screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);
    if(screen==NULL)
        return false;
    SDL_WM_SetCaption("Halli Galli",NULL);
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }
    if(TTF_Init()==-1)
        return false;
    game=false;
    clip[0].x=10;
    clip[0].y=10;
    clip[0].w=120;
    clip[0].h=140;

    clip[1].x=10;
    clip[1].y=160;
    clip[1].w=120;
    clip[1].h=140;

    clip[2].x=10;
    clip[2].y=320;
    clip[2].w=120;
    clip[2].h=140;

    clip[3].x=100;
    clip[3].y=100;
    clip[3].w=50;
    clip[3].h=30;

    clip[4].x=30;
    clip[4].y=25;
    clip[4].w=100;
    clip[4].h=50;

    clip[5].x=130;
    clip[5].y=25;
    clip[5].w=100;
    clip[5].h=50;

    clip[6].x=CX1;
    clip[6].y=CY1;
    clip[6].w=120;
    clip[6].h=140;
    player_number=4;

    for(int i=0; i<5; i++)
    {
        head[i]=0;
        tail[i]=12;
	if(i<4)
        	card_number[i]=13;
    }
    tail[4]=0;
    srand(time(0));
    for(int i=0; i<13; i++)
    {
        player_card[i]=rand()%3;
        computer1_card[i]=rand()%3;
        computer2_card[i]=rand()%3;
        computer3_card[i]=rand()%3;
    }
    for(int i=0; i<4; i++)
        number[i]=0;
    return true;
}
bool load_files()
{
    background1=load_image("images/UI.jpg");
    if(background1==NULL)
        return false;
    bgm=Mix_LoadMUS("music/bgm.mp3");

    if (bgm==NULL)

        return false;
    result=load_image("images/Result.jpg");
    if(result==NULL)
        return false;
    background2=load_image("images/UI2.jpg");
    if(background2==NULL)
        return false;
    help1=load_image("images/HELP3.jpg");
    if(help1==NULL)
        return false;
    help2=load_image("images/HELP4.jpg");
    if(help2==NULL)
        return false;
    card=load_image("images/CARD1.jpg");
    if(card==NULL)
        return false;
    bell=load_image("images/BELL.jpg");
    if(bell==NULL)
        return false;
    bell1=load_image("images/BELL1.jpg");
    if(bell1==NULL)
        return false;
    font=TTF_OpenFont("images/lazy.ttf",28);
    if(font==NULL)
        return false;
    
    ring_bell=Mix_LoadWAV("music/ring.wav");
    if(ring_bell==NULL)
        return false;
    win=Mix_LoadMUS("music/win.mp3");
    if(win==NULL)
        return false;
    lose=Mix_LoadMUS("music/lose.mp3");
    if(lose==NULL)
        return false;
    right=Mix_LoadWAV("music/right.wav");
    if(right==NULL)
        return false;
    wrong=Mix_LoadWAV("music/wrong.wav");
    if(wrong==NULL)
        return false;
    deal=Mix_LoadWAV("music/deal.wav");
    if(deal==NULL)
        return false;
    press=Mix_LoadWAV("music/press.wav");
    if(press==NULL)
        return false;
    return true;
}
bool ring()
{
    if( Mix_PlayChannel( -1, ring_bell, 0 ) == -1 )
    {
        return 1;    
    }
    apply_surface(0,0,bell1,screen,NULL);
    if(SDL_Flip(screen)==-1)
        return false;
    SDL_Delay(200);
    apply_surface(0,0,bell,screen,NULL);
    if(SDL_Flip(screen)==-1)
        return false;
    return true;
}
bool end_game()
{
    SDL_Delay(200);
    game=true;
    if(card_number[0]>=card_number[1]&&card_number[0]>=card_number[2]&&card_number[0]>=card_number[3])
    {
	if(Mix_PlayMusic(win,0)==-1)
        	return 1;
        apply_surface(NX4,NY4,screen,screen,&clip[3]);
        apply_surface(NX4,NY4,result,screen,&clip[5]);
        if(card_number[1])
        {
            apply_surface(NX1,NY1,screen,screen,&clip[3]);
            apply_surface(NX1,NY1,result,screen,&clip[4]);
        }
        if(card_number[2])
        {
            apply_surface(NX2,NY2,screen,screen,&clip[3]);
            apply_surface(NX2,NY2,result,screen,&clip[4]);
        }
        if(card_number[3])
        {
            apply_surface(NX3,NY3,screen,screen,&clip[3]);
            apply_surface(NX3,NY3,result,screen,&clip[4]);
        }
    }
    else
    {
        if(Mix_PlayMusic(lose,0)==-1)
        	return 1;
        apply_surface(NX4,NY4,screen,screen,&clip[3]);
        apply_surface(NX4,NY4,result,screen,&clip[4]);
        if(card_number[1])

        {
            apply_surface(NX1,NY1,screen,screen,&clip[3]);
            apply_surface(NX1,NY1,result,screen,&clip[5]);
        }
        if(card_number[2])
        {
            apply_surface(NX2,NY2,screen,screen,&clip[3]);
            apply_surface(NX2,NY2,result,screen,&clip[5]);
        }
        if(card_number[3])
        {
            apply_surface(NX3,NY3,screen,screen,&clip[3]);
            apply_surface(NX3,NY3,result,screen,&clip[5]);
        }
    }
    if(SDL_Flip(screen)==-1)
        return false;
    return true;
}
void clean_up()
{
    SDL_FreeSurface(background1);
    SDL_FreeSurface(background2);
    SDL_FreeSurface(help1);
    SDL_FreeSurface(help2);
    SDL_FreeSurface(card);
    SDL_FreeSurface(bell);
    SDL_FreeSurface(bell1);
    Mix_FreeChunk(ring_bell);
    Mix_FreeChunk(right);
    Mix_FreeChunk(wrong);
    Mix_FreeChunk(deal);
    Mix_FreeMusic(win);
    Mix_FreeMusic(lose);
    Mix_FreeMusic(bgm);
    Mix_FreeChunk(press);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    Mix_CloseAudio();
}
