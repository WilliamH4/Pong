#include "C:\raylib\include\raylib.h"
#include <stdio.h>
#include <stdlib.h>

int updateBallPos(int ballpos[2],int radius,int width, int height,int playerBlockerY,int computtorBlockerY,int score){
    static int ballXVelo=15;
    static int ballYVelo=7;
    //ballpos[0]=ballpos[0]+1;
    static bool right=1;
    static bool up=1;
    if (ballpos[0]<radius){
        right=1;
        score=0;
        printf("hit left wall\n");
    }else if (ballpos[0]+radius>width){
        right=0;
        score+=1;
        printf("hit right wall\n");
    }

    if (ballpos[1]<radius){
        up=0;
    }else if(ballpos[1]+radius>height){
        up=1;
    }


    //add the check for the player blocker
    if (ballpos[1]>=playerBlockerY&&ballpos[1]<=playerBlockerY+152&&ballpos[0]<=115){
        right=1;
        if (ballpos[1]>playerBlockerY+19){
            ballYVelo-=4;
        }else if(ballpos[1]>playerBlockerY+19*2){
            ballYVelo-=3;
        }else if(ballpos[1]>playerBlockerY+19*2){
            ballYVelo-=2;
        }else if(ballpos[1]>playerBlockerY+19*3){
            ballYVelo-=1;
        }else if(ballpos[1]>playerBlockerY+19*4){
            ballYVelo+=0;
        }else if(ballpos[1]>playerBlockerY+19*5){
            ballYVelo+=1;
        }else if(ballpos[1]>playerBlockerY+19*6){
            ballYVelo+=2;
        }else if(ballpos[1]>playerBlockerY+19*7){
            ballYVelo+=3;
        }else if(ballpos[1]>playerBlockerY+19*8){
            ballYVelo+=4;
        }
    }
    //add the check for the other blocker
    if (ballpos[1]>=computtorBlockerY&&ballpos[1]<=computtorBlockerY+152&&ballpos[0]>=width-95){
        right=0;
    }
    

    //deales with the movn=ment of the ball
    if (right==1){
        ballpos[0]=ballpos[0]+abs(ballXVelo);
    }else if(right==0){
        ballpos[0]=ballpos[0]-ballXVelo;
    }
    if (up==1){
        ballpos[1]=ballpos[1]-abs(ballYVelo);
    }else if (up==0){
        ballpos[1]=ballpos[1]+abs(ballYVelo);
    }
    //printf("ballpos X:%d%s%d\n",ballpos[0]," Y:", ballpos[1]);
    return score;
}

int GetPlayerplayerBlockerY(int y,int height){
    if (IsKeyDown(KEY_DOWN)||IsKeyDown(KEY_S)){
        y+=6;
    }else if(IsKeyDown(KEY_UP)||IsKeyDown(KEY_W)){
        y-=6;
    }
    if(y<0){
        y=0;
    }
    if(y>height-152){
        y=height-152;
    }
    
    DrawRectangle(70,y,25,152,WHITE);
    return y;
}
int GetComputorBlockerY(int y,int ballpos[], int height, int width){
    //75 is to keep the ball in the middle of the blocker.
    if (ballpos[1]-76>y){
        y+=6;
    }else if (ballpos[1]-76<y){
        y-=6;
    }
    //printf("blocker y:%d\n",y);
    DrawRectangle(width-70,y,25,152,RED);

    return y;
}

int main() {
    // Initialize the window
    int width=1800;
    int height=1000;
    InitWindow(width, height, "pong rip off");
    int radius=25;
    int score =0;    
    int *ballpos =new int[2];
    ballpos[0]=width/2;ballpos[1]=height/2;//0 is the x and 1 is the y
    int playerBlockerY=0,computerBlockerY=0;
    //int* array =new int[2];
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        char string[50];
        sprintf(string,"%s%d","score: ",score);
        //printf("score:%d\n",score);
        DrawText(string,width/2,100, 20, DARKGRAY);



        //ballpos[0]=ballpos[0]+10;

        computerBlockerY=GetComputorBlockerY(computerBlockerY,ballpos,height,width);
        playerBlockerY=GetPlayerplayerBlockerY(playerBlockerY,height);

        score=updateBallPos(ballpos,radius,width,height,playerBlockerY,computerBlockerY,score);
        //printf("ballpos:%d%s%d\n",ballpos[0]," ",ballpos[1]);
        DrawCircle(ballpos[0],ballpos[1],radius,WHITE);



        WaitTime(.01);
        EndDrawing();
        
    }
    // De-Initialization
    CloseWindow(); // Close window and OpenGL context
    //delete[]array;
    delete[]ballpos;

    return 0;
}