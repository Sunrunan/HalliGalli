#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "GameData.h"
#include "ControlFunction.h"
bool quit=false;
bool player=true,computer1=true,computer2=true,computer3=true;
int surface=0,inde=0;
int main( int argc, char* args[] )
{
    if(init()==false)
        return 1;
    if(load_files()==false)
        return 1;
   
    apply_surface(0,0,background1,screen,NULL);
    if(SDL_Flip(screen)==-1)
        return 1;
    if(Mix_PlayMusic(bgm,-1)==-1)
        return 1;
    while(quit==false)
    {
        while(SDL_PollEvent(&event))
        {
            if(player_number==2&&game==false)
                if(end_game()==false)
		{
                    return 1;
		    game=true;
		}
            if (event.type==SDL_KEYDOWN&&game==false)
            {
                if(surface==3)
                {
                    if(event.key.keysym.sym==SDLK_SPACE)
                    {
                        if(inde==0&&player)
                        {
			    if( Mix_PlayChannel( -1, deal, 0 ) == -1 )
                    	    {
                       		return 1;    
                    	    }
                            apply_surface(CX4,CY4,card,screen,&clip[player_card[head[0]]]);
                            apply_surface(NX4,NY4,screen,screen,&clip[3]);
                            table_card[head[4]++]=player_card[head[0]];
                            number[tail[4]]=player_card[head[0]]+1;
                            tail[4]=(tail[4]+1)%4;
                            head[0]=(head[0]+1)%52;
                            play_card_number=write1(--card_number[0]);
                            apply_surface(NX4,NY4,play_card_number,screen,NULL);
			    apply_surface(NX4+30,NY4,screen,screen,&clip[3]);
                            if (!card_number[0])
                            {
                                player=LOSE;
                                apply_surface(NX4,NY4,screen,screen,&clip[3]);
                                apply_surface(NX4,NY4,result,screen,&clip[4]);
                                player_number--;
                                if(SDL_Flip(screen)==-1)
                                    return 1;
                                if(end_game()==false)
                                    return 1;
                            }
                            if(SDL_Flip(screen)==-1)
                                return 1;
                        }
                        if(inde==1&&computer3)
                        {
			    if( Mix_PlayChannel( -1, deal, 0 ) == -1 )
                    	    {
                       		return 1;    
                    	    }	
                            apply_surface(CX3,CY3,card,screen,&clip[computer3_card[head[3]]]);
                            apply_surface(NX3,NY3,screen,screen,&clip[3]);
                            table_card[head[4]++]=computer3_card[head[3]];
                            number[tail[4]]=computer3_card[head[3]]+1;
                            tail[4]=(tail[4]+1)%4;
                            head[3]=(head[3]+1)%52;
                            computer3_card_number=write1(--card_number[3]);
                            apply_surface(NX3,NY3,computer3_card_number,screen,NULL);
			    apply_surface(NX3+30,NY3,screen,screen,&clip[3]);
                            if (!card_number[3])
                            {
                                computer3=LOSE;
                                apply_surface(NX3,NY3,screen,screen,&clip[3]);
                                apply_surface(NX3,NY3,result,screen,&clip[4]);
                                player_number--;
                            }
                            if(SDL_Flip(screen)==-1)
                                return 1;
                        }
                        if(inde==2&&computer2)
                        {
                            if( Mix_PlayChannel( -1, deal, 0 ) == -1 )
                    	    {
                       		return 1;    
                    	    }	
                            apply_surface(CX2,CY2,card,screen,&clip[computer2_card[head[2]]]);
                            apply_surface(NX2,NY2,screen,screen,&clip[3]);
                            table_card[head[4]++]=computer2_card[head[2]];
                            number[tail[4]]=computer2_card[head[2]]+1;
                            tail[4]=(tail[4]+1)%4;
                            head[2]=(head[2]+1)%52;
                            computer2_card_number=write1(--card_number[2]);
                            apply_surface(NX2,NY2,computer2_card_number,screen,NULL);
			    apply_surface(NX2+30,NY2,screen,screen,&clip[3]);
                            if (!card_number[2])
                            {
                                computer2=LOSE;
                                apply_surface(NX2,NY2,screen,screen,&clip[3]);
                                apply_surface(NX2,NY2,result,screen,&clip[4]);
                                player_number--;
                            }
                            if(SDL_Flip(screen)==-1)
                                return 1;
                        }
                        if(inde==3&&computer1)
                        {
			    if( Mix_PlayChannel( -1, deal, 0 ) == -1 )
                    	    {
                       		return 1;    
                    	    }	
                            apply_surface(CX1,CY1,card,screen,&clip[computer1_card[head[1]]]);
                            apply_surface(NX1,NY1,screen,screen,&clip[3]);
                            table_card[head[4]++]=computer1_card[head[1]];
                            number[tail[4]]=computer1_card[head[1]]+1;
                            tail[4]=(tail[4]+1)%4;
                            head[1]=(head[1]+1)%52;
                            computer1_card_number=write1(--card_number[1]);
                            apply_surface(NX1,NY1,computer1_card_number,screen,NULL);
			    apply_surface(NX1+30,NY1,screen,screen,&clip[3]);
                            if (!card_number[1])
                            {
                                computer1=LOSE;
                                apply_surface(NX1,NY1,screen,screen,&clip[3]);
                                apply_surface(NX1,NY1,result,screen,&clip[4]);
                                player_number--;
                            }
                            if(SDL_Flip(screen)==-1)
                                return 1;
                        }
                        inde=(inde+1)%4;
                        int sum=number[0]+number[1]+number[2]+number[3];
                    if(sum%2==0&&head[4]>0)
                    {
                        srand(time(0));
                        switch1=rand()%100;
                        switch2=rand()%3;
                        if(switch1>60)
                        {
                            if(switch2==0&&computer1)
                            {
                                SDL_Delay(200);
                                if(ring()==false)
                                    return 1;
                                SDL_Delay(200);
                                apply_surface(CX1,CY1,background2,screen,&clip[6]);
                                apply_surface(CX2,CY2,background2,screen,&clip[6]);
                                apply_surface(CX3,CY3,background2,screen,&clip[6]);
                                apply_surface(CX4,CY4,background2,screen,&clip[6]);
                                card_number[1]+=head[4];
                                computer1_card_number=write1(card_number[1]);
                                apply_surface(NX1,NY1,screen,screen,&clip[3]);
                                apply_surface(NX1,NY1,computer1_card_number,screen,NULL);
				apply_surface(NX1+30,NY1,screen,screen,&clip[3]);
                                if(SDL_Flip(screen)==-1)
                                    return 1;
                                int i=0;
                                while(i<head[4])
                                    computer1_card[(++tail[1])%52]=table_card[i++];
                                head[4]=0;
                                inde=3;
                                tail[4]=0;
                                for(i=0;i<4;i++) number[i]=0;
                            }
                            else if(switch2==1&&computer2)
                            {
                                SDL_Delay(200);
                                if(ring()==false)
                                    return 1;
                                SDL_Delay(200);
                                apply_surface(CX1,CY1,background2,screen,&clip[6]);
                                apply_surface(CX2,CY2,background2,screen,&clip[6]);
                                apply_surface(CX3,CY3,background2,screen,&clip[6]);
                                apply_surface(CX4,CY4,background2,screen,&clip[6]);
                                card_number[2]+=head[4];
                                computer2_card_number=write1(card_number[2]);
                                apply_surface(NX2,NY2,screen,screen,&clip[3]);
                                apply_surface(NX2,NY2,computer2_card_number,screen,NULL);
				apply_surface(NX2+30,NY2,screen,screen,&clip[3]);
                                if(SDL_Flip(screen)==-1)
                                    return 1;
                                int i=0;
                                while(i<head[4])
                                    computer1_card[(++tail[2])%52]=table_card[i++];
                                head[4]=0;
                                inde=2;
                                tail[4]=0;
                                for(i=0;i<4;i++) number[i]=0;
                            }
                            else if(computer3)
                            {
                                SDL_Delay(200);
                                if(ring()==false)
                                    return 1;
                                SDL_Delay(200);
                                apply_surface(CX1,CY1,background2,screen,&clip[6]);
                                apply_surface(CX2,CY2,background2,screen,&clip[6]);
                                apply_surface(CX3,CY3,background2,screen,&clip[6]);
                                apply_surface(CX4,CY4,background2,screen,&clip[6]);
                                card_number[3]+=head[4];
                                computer3_card_number=write1(card_number[3]);
                                apply_surface(NX3,NY3,screen,screen,&clip[3]);
                                apply_surface(NX3,NY3,computer3_card_number,screen,NULL);
				apply_surface(NX3+30,NY3,screen,screen,&clip[3]);
                                if(SDL_Flip(screen)==-1)
                                    return 1;
                                int i=0;
                                while(i<head[4])
                                    computer1_card[(++tail[3])%52]=table_card[i++];
                                head[4]=0;
                                inde=1;
                                tail[4]=0;
                                for(i=0;i<4;i++) number[i]=0;
                            }
                        }
                    }

                    }
                    else
                    {
                        if(ring()==false)
                                    return 1;
                        int sum=number[0]+number[1]+number[2]+number[3];
                        if(head[4]>0)
                        {
                            if(sum%2==0)
                            {
  				if( Mix_PlayChannel( -1, right, 0 ) == -1 )
                    	    	{
                       		    return 1;    
                    	    	}	
                                SDL_Delay(200);
                                apply_surface(CX1,CY1,background2,screen,&clip[6]);
                                apply_surface(CX2,CY2,background2,screen,&clip[6]);
                                apply_surface(CX3,CY3,background2,screen,&clip[6]);
                                apply_surface(CX4,CY4,background2,screen,&clip[6]);
                                card_number[0]+=head[4];
                                play_card_number=write1(card_number[0]);
                                apply_surface(NX4,NY4,screen,screen,&clip[3]);
                                apply_surface(NX4,NY4,play_card_number,screen,NULL);
				apply_surface(NX4+30,NY4,screen,screen,&clip[3]);
                                if(SDL_Flip(screen)==-1)
                                    return 1;
                                int i=0;
                                while(i<head[4])
                                    player_card[(++tail[0])%52]=table_card[i++];
                                head[4]=0;
                                inde=0;
                                tail[4]=0;
                                for(i=0;i<4;i++) number[i]=0;
                            }
                            else
                            {
                                    if( Mix_PlayChannel( -1, wrong, 0 ) == -1 )
                    	  	    {
                       			return 1;    
                    	   	    }	
                                    SDL_Delay(200);
                                    if(card_number[0]>=4)
                                    {
                                        card_number[0]-=(player_number-1);
                                        if(computer1)
                                        {
                                            card_number[1]+=1;
                                            computer1_card_number=write1(card_number[1]);
                                            apply_surface(NX1,NY1,screen,screen,&clip[3]);
                                            apply_surface(NX1,NY1,computer1_card_number,screen,NULL);
					    apply_surface(NX1+30,NY1,screen,screen,&clip[3]);
                                            computer1_card[(++tail[1])%52]=player_card[(head[0]++)%52];
                                        }
                                        if(computer2)
                                        {
                                            card_number[2]+=1;
                                            computer2_card_number=write1(card_number[2]);
                                            apply_surface(NX2,NY2,screen,screen,&clip[3]);
                                            apply_surface(NX2,NY2,computer2_card_number,screen,NULL);
					    apply_surface(NX2+30,NY2,screen,screen,&clip[3]);
                                            computer2_card[(++tail[2])%52]=player_card[(head[0]++)%52];
                                        }
                                        if(computer3)
                                        {
                                            card_number[3]+=1;
                                            computer3_card_number=write1(card_number[3]);
                                            apply_surface(NX3,NY3,screen,screen,&clip[3]);
                                            apply_surface(NX3,NY3,computer3_card_number,screen,NULL);
					    apply_surface(NX3+30,NY3,screen,screen,&clip[3]);
                                            computer3_card[(++tail[3])%52]=player_card[(head[0]++)%52];
                                        }
                                        play_card_number=write1(card_number[0]);
                                        apply_surface(NX4,NY4,screen,screen,&clip[3]);
                                        apply_surface(NX4,NY4,play_card_number,screen,NULL);
					apply_surface(NX4+30,NY4,screen,screen,&clip[3]);
                                        if(SDL_Flip(screen)==-1)
                                            return 1;
                                    }
                                    else
                                    {
                                        player=LOSE;
                                        apply_surface(NX4,NY4,screen,screen,&clip[3]);
                                        apply_surface(NX4,NY4,result,screen,&clip[4]);
                                        player_number--;
                                        if(SDL_Flip(screen)==-1)
                                        return 1;
                                        if(end_game()==false)
                                            return 1;
                                    }
                                    /*if(!card_number[0])
                                    {
                                        player=LOSE;
                                        apply_surface(NX4,NY4,screen,screen,&clip[3]);
                                        apply_surface(NX4,NY4,result,screen,&clip[4]);
                                        player_number--;
                                        if(SDL_Flip(screen)==-1)
                                        return 1;
                                        if(end_game()==false)
                                            return 1;
                                    }*/
                            }
                        }
                    }
                  //  (event.key.keysym.sym==SDLK_ENTER)*/
                }
                else if(surface==2)
                {
                    if(event.key.keysym.sym==SDLK_SPACE)
                    {
			if( Mix_PlayChannel( -1,press, 0 ) == -1 )
                    	{
                            return 1;    
                        }
                        apply_surface(0,0,background2,screen,NULL);
                        apply_surface(0,0,bell,screen,NULL);
			play_card_number=write1(card_number[0]);
    			computer1_card_number=write1(card_number[1]);
    			computer2_card_number=write1(card_number[2]);
    			computer3_card_number=write1(card_number[3]);
                        apply_surface(NX4,NY4,play_card_number,screen,NULL);
                        apply_surface(NX1,NY1,computer1_card_number,screen,NULL);
                        apply_surface(NX2,NY2,computer2_card_number,screen,NULL);
                        apply_surface(NX3,NY3,computer3_card_number,screen,NULL);
                        if(SDL_Flip(screen)==-1)
                        return 1;
                        surface=3;
                    }

                }
                else if(surface==1)
                {
		    if( Mix_PlayChannel( -1,press, 0 ) == -1 )
                    {
                        return 1;    
                    }
                    apply_surface(0,0,help2,screen,NULL);
                    if(SDL_Flip(screen)==-1)
                        return 1;
                    surface=2;
                }
                else if(surface==0)
                {
	            if( Mix_PlayChannel( -1,press, 0 ) == -1 )
                    {
                        return 1;    
                    }
                    apply_surface(0,0,help1,screen,NULL);
                    if(SDL_Flip(screen)==-1)
                        return 1;
                    surface=1;
                }
            }
            else if(event.type==SDL_QUIT)
            {
                quit=true;
            }
        }

    }
    //quit the game
    clean_up();
    return 0;
}
int main(){
	return 0;
}
