#include "C:\raylib\include\raylib.h"
#include <stdio.h>
#include <stdlib.h>

void updateBallPos(int ballpos[2],int radius,int width, int height,int playerBlockerY,int computtorBlockerY,int score[2]){
    int startingXVelo=10;
    int startingYVelo=0;
    static int ballXVelo=startingXVelo;
    static int ballYVelo=startingYVelo;
    static int clock=0;//used to speed up the game slowly
    static bool reset=0;


    if (reset==1){
        WaitTime(1);
        reset=0;
        ballXVelo=startingXVelo;
        ballYVelo=startingYVelo;
        clock=0;
        ballpos[0]=width/2;
        ballpos[1]=height/2;
    }

    //ballYVelo+=1;

    if (clock>=2){
        clock=0;
        if(ballXVelo>0){
            ballXVelo+=1;
        }else{
            ballXVelo-=1;
        }
    }

    if (ballYVelo>12){
        ballYVelo=12;
    }

    if (ballXVelo==0){
        ballXVelo+=1;
    }

    //left wall colision logic
    if (ballpos[0]<radius){
        if (ballXVelo<0){
            score[1]+=1;
            reset=1;
        }

        printf("hit left wall\n");

    //right wall collision logic
    }else if (ballpos[0]+radius>width){
        ballXVelo=startingXVelo;
        if (ballXVelo>0){
            ballXVelo=ballXVelo*-1;
            score[0]+=1;
            reset=1;
        }
        printf("hit right wall\n");
    }

    //top wall collision logic
    if (ballpos[1]<radius){
        if(ballYVelo<0){
            ballYVelo=-ballYVelo;
        }

    //bottom wall collision logic
    }else if(ballpos[1]+radius>height){
        if(ballYVelo>0){
            ballYVelo=-ballYVelo;
        }
    }


    //add the check for the player blocker

    //we check if the ball is in the same horisontal space as the blocker then we check if its x pos is less then the blockers if it is we deflect it
    if (ballpos[1]>=playerBlockerY&&ballpos[1]<=playerBlockerY+152&&ballpos[0]<=115){
        if (ballXVelo<0){
            ballXVelo=ballXVelo*-1;
            clock+=1;
            if (ballpos[1]<playerBlockerY+19){
                ballYVelo-=4;
            }else if(ballpos[1]<playerBlockerY+19*2){
                ballYVelo-=3;
            }else if(ballpos[1]<playerBlockerY+19*2){
                ballYVelo-=2;
            }else if(ballpos[1]<playerBlockerY+19*3){
                ballYVelo-=1;
            }else if(ballpos[1]<playerBlockerY+19*4){
                ballYVelo+=0;
            }else if(ballpos[1]<playerBlockerY+19*5){
                ballYVelo+=1;
            }else if(ballpos[1]<playerBlockerY+19*6){
                ballYVelo+=2;
            }else if(ballpos[1]<playerBlockerY+19*7){
                ballYVelo+=3;
            }else if(ballpos[1]<playerBlockerY+19*8){
                ballYVelo+=4;
            }
        }
    }
    //add the check for the other blocker
    if (ballpos[1]>=computtorBlockerY&&ballpos[1]<=computtorBlockerY+152&&ballpos[0]>=width-95){
        if (ballXVelo>0){
            ballXVelo=ballXVelo*-1;
            clock+=1;
            if (ballpos[1]<computtorBlockerY+19){
                ballYVelo-=4;
            }else if(ballpos[1]<computtorBlockerY+19*2){
                ballYVelo-=3;
            }else if(ballpos[1]<computtorBlockerY+19*2){
                ballYVelo-=2;
            }else if(ballpos[1]<computtorBlockerY+19*3){
                ballYVelo-=1;
            }else if(ballpos[1]<computtorBlockerY+19*4){
                ballYVelo+=0;
            }else if(ballpos[1]<computtorBlockerY+19*5){
                ballYVelo+=1;
            }else if(ballpos[1]<computtorBlockerY+19*6){
                ballYVelo+=2;
            }else if(ballpos[1]<computtorBlockerY+19*7){
                ballYVelo+=3;
            }else if(ballpos[1]<computtorBlockerY+19*8){
                ballYVelo+=4;
            }
        }


}


    ballpos[0]=ballpos[0]+ballXVelo;
   
    ballpos[1]=ballpos[1]+ballYVelo;
    //printf("ballpos X:%d%s%d\n",ballpos[0]," Y:", ballpos[1]);
}

int GetPlayerplayerBlockerY(int y,int height, int ballpos[]){
    if (IsKeyDown(KEY_DOWN)||IsKeyDown(KEY_S)){
        y+=8;
    }else if(IsKeyDown(KEY_UP)||IsKeyDown(KEY_W)){
        y-=8;
    }
    if(y<0){
        y=0;
    }
    if(y>height-152){
        y=height-152;
    }

    // int middle=y+76;

    // int startY=y;

    // y+=ballpos[1]-middle;

    // if (startY-y>7){
    //     y=startY-7;
    // }else if(y-startY>7){
    //     y=startY+7;
    // }
    
    DrawRectangle(70,y,25,152,WHITE);
    return y;
}
int GetComputorBlockerY(int y,int ballpos[], int height, int width){
    //75 is to keep the ball in the middle of the blocker.
    int middle=y+76;

    int startY=y;

    y+=ballpos[1]-middle;

    if (startY-y>7){
        y=startY-7;
    }else if(y-startY>7){
        y=startY+7;
    }
    

    //printf("blocker y:%d\n",y);
    DrawRectangle(width-70,y,25,152,PURPLE);

    return y;
}

int main() {
    // Initialize the window
    int width=1800;
    int height=1000;

    InitWindow(width, height, "pong rip off");

    int radius=25;
    int *ballpos =new int[2];
    ballpos[0]=width/2;ballpos[1]=height/2;//0 is the x and 1 is the y

    int *score =new int[2];
    score[0]=0,score[1]=0;    
   
    int playerBlockerY=height/2,computerBlockerY=height/2;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        char string[50];
        sprintf(string,"%s%d%s%d","score: ",score[0]," to ",score[1]);
        //printf("score:%d\n",score);
        DrawText(string,width/2,100, 20, DARKGRAY);




        computerBlockerY=GetComputorBlockerY(computerBlockerY,ballpos,height,width);
        playerBlockerY=GetPlayerplayerBlockerY(playerBlockerY,height,ballpos);

        updateBallPos(ballpos,radius,width,height,playerBlockerY,computerBlockerY,score);
        //printf("ballpos:%d%s%d\n",ballpos[0]," , ",ballpos[1]);
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