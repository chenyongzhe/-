#include "SDL2/SDL.h"
#include<cstdio>
#include<vector>
#include <stdlib.h>
#include <iostream>

//#include "SDL_anigif.h"
//#include "SDL_anigif.c"
#include "SDL2/SDL_image.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
using namespace std;

int fen=0;

int life=2;

SDL_Point cen[10];

int angel=180;

int i1=0;

int i2=0;
int i3=0;
int i4=0;
int i=0;
int i9=0;
int i8=0;
bool birth=false;

typedef struct {
   int x;
   int y;
   int AIstate;//飞机是否被打中

   int speed;

}Spot;



void moveSpot(Spot *spot){


  spot->y=spot->y+spot->speed;
  if(spot->y>550)
    spot->y=20;



}


void drawSpot(Spot *spot,SDL_Renderer *rend1,SDL_Texture *rain,SDL_Point cen){

    SDL_Rect rect;
rect.x=spot->x;
rect.y=spot->y;
rect.w=67;
rect.h=50;
SDL_Rect cut3;
cut3.x=457;
cut3.y=93;
cut3.w=68;
cut3.h=50;
SDL_RenderCopyEx(rend1,rain,&cut3,&rect,angel,&cen,SDL_FLIP_NONE);

}


class Buttle{
public :

    int isrun=0;
  SDL_Rect boxbuttle;

 void  Buttlemove();
  void drawbuttle( SDL_Rect cut,SDL_Rect *box ,SDL_Renderer *rend1,SDL_Texture *Buttle);


};

void Buttle::Buttlemove(){


this->boxbuttle.y-=10;




}


void Buttle::drawbuttle(SDL_Rect cut,SDL_Rect *box ,SDL_Renderer *rend1,SDL_Texture *Buttle){



SDL_RenderCopy(rend1,Buttle,&cut,box);






}








int main(int argc,char**argv)
{
SDL_Event event;
bool g_bRunning = true;
int dir=0;
int  flystate=0;
int bomstate=0;

SDL_Init(SDL_INIT_EVERYTHING);
Mix_Init(MIX_INIT_OGG);
//Thread =SDL_CreateThread(EventThread,"1",(void*)NULL);

SDL_Window*gWin = SDL_CreateWindow("my fly",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_SHOWN);
SDL_Renderer*render = SDL_CreateRenderer(gWin,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
SDL_Surface *f=IMG_Load("fly12.png");
SDL_Surface *f1=IMG_Load("flydi.png");
SDL_Surface *back1=IMG_Load("background.png");//白色背景
SDL_Surface *b=IMG_Load("zd.png");
SDL_Surface *spacesurface =IMG_Load("78.jpg");
SDL_Surface *gameo =SDL_LoadBMP("over.bmp");



SDL_SetColorKey(gameo,SDL_TRUE ,SDL_MapRGB(gameo->format,255,255,255));



SDL_SetColorKey(b,SDL_TRUE ,SDL_MapRGB(b->format,255,255,255));
//SDL_SetColorKey(f,SDL_TRUE ,SDL_MapRGB(f->format,254,255,255));
SDL_SetColorKey(f1,SDL_TRUE ,SDL_MapRGB(f1->format,255,255,255));
SDL_SetColorKey(f,SDL_TRUE ,SDL_MapRGB(f->format,255,255,255));
SDL_Texture *fly=SDL_CreateTextureFromSurface(render,f);
SDL_Texture *background=SDL_CreateTextureFromSurface(render,back1);
SDL_Texture *bom=SDL_CreateTextureFromSurface(render,b);
SDL_Texture *AIfly=SDL_CreateTextureFromSurface(render,f1);
SDL_Texture *space1=SDL_CreateTextureFromSurface(render,spacesurface);


SDL_Texture *gameover=SDL_CreateTextureFromSurface(render,gameo);




SDL_SetTextureBlendMode(background,SDL_BLENDMODE_BLEND);

SDL_SetTextureAlphaMod(background,120);


TTF_Init();
TTF_Font *font;
SDL_Color Color2 = { 0, 255, 255 };
 font = TTF_OpenFont("Deng.ttf", 28 );

 SDL_Surface * pTextSurface = NULL;//鏂囨湰琛ㄩ潰
    SDL_Texture* pTextTexture = NULL;//鏂囨湰绾圭悊
    //鏂囨湰鏄剧ず鍖哄煙
    SDL_Rect rcText;
    rcText.x = 10;
    rcText.y = 10;
    rcText.w = 200;
    rcText.h = 50;

        char e[40];

SDL_Surface * lifeTextSurface = NULL;
    SDL_Texture* lifeTextTexture = NULL;


 SDL_Rect liferect;
    liferect.x = 10;
    liferect.y = 70;
    liferect.w = 200;
    liferect.h = 50;

        char lifebuffe[40];


















//Mix_Init(MIX_INIT_OGG);
Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,1,4096);
//Mix_Init(MIX_INIT_OGG);
Mix_Music *hun=Mix_LoadMUS("bullet.ogg");
Mix_Music *boom=Mix_LoadMUS("bombing1.wav");
Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,1,2048);

Mix_Chunk *ab=Mix_LoadWAV("bg_music.wav");
Mix_PlayChannel(-1,ab,20);
 //Mix_PlayMusic(mu,1);


SDL_Rect cut1;//剪切我方飞机
cut1.x=169;
cut1.y=159;
cut1.w=139;
cut1.h=119;
SDL_Rect box1;//我方飞机大小，位置
box1.x=300;
box1.y=450;
box1.w=133;
box1.h=119;
SDL_Rect box2;//背景
box2.x=0;
box2.y=0;
box2.w=800;
box2.h=600;
SDL_Rect box3;//子弹大小方向
box3.w=25;
box3.h=50;

Spot spot[10];//敌机

for(i=0;i<10;i++){
spot[i].x=rand()%700+100;
spot[i].y=rand()%20+4;
spot[i].speed=rand()%5 +2;
spot[i].AIstate=0;
}



SDL_Rect box5;//太空背景

box5.x=0;
box5.y=-700;
box5.h=1300;
box5.w=1600;


SDL_Rect cut3;
cut3.x=287;
cut3.y=176;
cut3.w=36;
cut3.h=104;


SDL_Rect gameoverrect;
gameoverrect.x=250;
gameoverrect.y=200;
gameoverrect.w=gameo->w;
gameoverrect.h=gameo->h;



bool endgame=false;


Buttle buttle[4];

SDL_Rect boxbuttle[4];
















      while(g_bRunning)
   {
      while(SDL_PollEvent(&event))
    {
       switch(event.type)
       {
         case SDL_QUIT:
         g_bRunning = false;
          break;
        }

      if(event.type==SDL_KEYDOWN){
       if(event.key.keysym.sym==SDLK_RIGHT&&endgame==false){

            dir=1;
            flystate=1;

         }

      if(event.key.keysym.sym==SDLK_LEFT&&endgame==false){

            dir=2;
            flystate=1;

         }
       if(event.key.keysym.sym==SDLK_SPACE&&bomstate==0&&endgame==false){
            box3.x=box1.x+55;
            box3.y=box1.y-15;
            bomstate=1;
           Mix_PlayMusic(hun,1);

       }

       if(event.key.keysym.sym==SDLK_z&&endgame==false){
           if(buttle[i8].isrun==0){
            buttle[i8].boxbuttle.x=box1.x+55;
            buttle[i8].boxbuttle.y=box1.y-15;
            buttle[i8].boxbuttle.w=25;
            buttle[i8].boxbuttle.h=50;
            buttle[i8].isrun=1;
          i8++;
          if(i8==4){
                i8=0;

               }

           }

         }

      }
    if(event.type==SDL_KEYUP){

    flystate=0;




    }

   if(endgame==true){

    if(event.button.button==SDL_BUTTON_LEFT)
    {

    if(event.motion.x>315&&event.motion.x<500&&event.motion.y>350&&event.motion.y<400){

        life=2;
        endgame=false;



    }






    }





   }



    }
if(flystate==1){
    switch(dir){

   case 1:
       box1.x+=10;
       break;
   case 2:
       box1.x-=10;
       break;

    }
    //flystate=0;
}
    if(bomstate==1){
        box3.y-=15;
        if(box3.y<20){
           bomstate=0;

        }
    }
    else {
        box3.x=990;
        box3.y=450;
}



  SDL_Delay(50);
SDL_RenderClear(render);

   //SDL_RenderCopy(render,background,NULL,&box2);
   SDL_RenderCopy(render,space1,NULL,&box5);
   box5.y=box5.y+1;
   if(box5.y>-20){

    box5.y=-700;
   }

   SDL_RenderCopy(render,background,NULL,&box2);
   if(bomstate==1){

     SDL_RenderCopy(render,bom,&cut3,&box3);

   }
  for(i=0;i<10;i++){
        cen[i].x=0;
        cen[i].y=0;
   if(spot[i].AIstate==0&&spot[i].AIstate==0){
 drawSpot(&spot[i],render,AIfly,cen[i]);
    moveSpot(&spot[i]);
   }

  }
for (i1=0;i1<10;i1++){
    if(spot[i1].x-box3.x>0&&spot[i1].x-box3.x<80&&spot[i1].y-box3.y>-20&&spot[i1].y-box3.y<10){

        spot[i1].AIstate=1;
        spot[i1].x=990;
        spot[i1].y=-100;
        bomstate=0;
  Mix_PlayMusic(boom,1);


     fen=fen+100;
     if(fen%600==0&&fen!=0){

        life=life+1;


     }

  // Mix_PlayMusic(boom,1);




  }




}





for (i1=0;i1<10;i1++){
    if(spot[i1].x-box1.x>10&&spot[i1].x-box1.x<180&&spot[i1].y-box1.y>35&&spot[i1].y-box1.y<200){



  life=life-1;
  spot[i1].AIstate=1;
  spot[i1].x=990;
  spot[i1].y=-100;

Mix_PlayMusic(boom,1);



  }









}














 for (i3=0;i3<10;i3++){

       if( spot[i3].AIstate==1)  {

        i2++;
       }

    }
//cout<<i2;





 if(i2==10){
        birth=true;

        for(i4=0;i4<10;i4++){

        spot[i4].AIstate=0;

        }

      }
if(birth==true){

  for(i=0;i<10;i++){
spot[i].x=rand()%700+100;
spot[i].y=rand()%100+4;
spot[i].speed=rand()%4 +2;
spot[i].AIstate=0;
}
    birth=false;
}










i2=0;

   SDL_RenderCopy(render,fly,&cut1,&box1);

  //SDL_RenderCopy(render,bom,NULL,&box3);

  sprintf(e,"score %d",fen);
   pTextSurface=TTF_RenderUTF8_Blended(font,e,Color2);

  pTextTexture = SDL_CreateTextureFromSurface(render, pTextSurface);



  sprintf(lifebuffe,"life %d",life);
   lifeTextSurface=TTF_RenderUTF8_Blended(font,lifebuffe,Color2);

  lifeTextTexture = SDL_CreateTextureFromSurface(render, lifeTextSurface);




    SDL_RenderCopy(render, lifeTextTexture, NULL, &liferect);


   SDL_RenderCopy(render, pTextTexture, NULL, &rcText);


   if(life<=0){
  endgame=true;


 SDL_RenderCopy(render, gameover, NULL, &gameoverrect);



}
   for(int i=0;i<4;i++){

    if(buttle[i].isrun==1){

     buttle[i].Buttlemove();
     buttle[i].drawbuttle(cut3,&buttle[i].boxbuttle,render,bom);
     if(buttle[i].boxbuttle.y<0){

        buttle[i].isrun=0;
     }

    }






   }


   for(int i=0;i<4;i++){




for (i1=0;i1<10;i1++){
    if(spot[i1].x-buttle[i].boxbuttle.x>0&&spot[i1].x-buttle[i].boxbuttle.x<80&&spot[i1].y-buttle[i].boxbuttle.y>-20&&spot[i1].y-buttle[i].boxbuttle.y<10){

        spot[i1].AIstate=1;
        spot[i1].x=990;
        spot[i1].y=-100;
        buttle[i].isrun=0;
        buttle[i].boxbuttle.x=2000;
  Mix_PlayMusic(boom,1);


     fen=fen+100;
     if(fen%600==0&&fen!=0){

        life=life+1;


     }

  // Mix_PlayMusic(boom,1);




  }




}












   }







if(box1.x<=0){
    box1.x=0;


}
if(box1.x>=687){

    box1.x=687;

}




   SDL_RenderPresent(render);

   //SDL_Delay(50);
  }


return 0;


}


