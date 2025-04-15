#include "C:\raylib\include\raylib.h"
#include <stdio.h>
#include <stdlib.h>

int height=1000;
int width=1800;


class blocker{

    public:
    int ycord=0;
    int thickness=50;
    int blockerHeight=175;
    int xcord;
    int maxSpeed=7;
    void reciveInput(){
        if(IsKeyDown(KEY_UP)){
            ycord-=maxSpeed;
        }else if (IsKeyDown(KEY_DOWN)){
            ycord+=maxSpeed;
        }
        if(ycord+blockerHeight>height){
            ycord=height-blockerHeight;
        }else if (ycord<0){
            ycord=0;
        }
    }
    // void GenerateMovment(const ball& b){
    //     int middle=ycord+blockerHeight/2;
    //     int dif=b.pos[1]-middle;
    //     if(dif>5){
    //         dif=5;
    //     }else if(dif<-5){
    //         dif=-5;
    //     }
    //     ycord+=dif;
        // if (b.pos[1]>middle){
        //     ycord+=5;
        // }else if (b.pos[1]<middle){
        //     ycord-=5;
        // }
    //}
    void display(){
        DrawRectangle(xcord,ycord,thickness,blockerHeight,WHITE);
    }


};

class ball;

class ball{
    public:
    int radius=50;
    int velo[2]={-5,-8};
    int pos[2]={400,100};
    void updatepos(){
        pos[0]+=velo[0];
        pos[1]+=velo[1];
        DrawCircle(pos[0],pos[1],radius,WHITE);
    }
    void checkcollison(const blocker& b1, const blocker& b2){

        //for the player blocker
        if (b1.ycord<pos[1]&&b1.ycord+b1.blockerHeight>pos[1]&&pos[0]-radius<b1.xcord+b1.thickness){
            if (velo[0]<0){
                velo[0]=-velo[0];
            }
            return;
        }

        //for the opponet
        if (b2.ycord<pos[1]&&b2.ycord+b2.blockerHeight>pos[1]&&pos[0]+radius>b2.xcord){
            if (velo[0]>0){
                velo[0]=-velo[0];
            }
            return;
        }

        //for the top and bottom walls

        //top
        if (pos[1]-radius<0&&velo[1]<0){
            velo[1]=velo[1]*-1;

        //bottom
        }else if(pos[1]+radius>height&&velo[1]>0){
            velo[1]=-velo[1];
        }

        
    }

};

int main() {
    SetTraceLogLevel(LOG_NONE);

    ball ball1;
    blocker player;
    blocker opponet;
    player.xcord=50;
    opponet.xcord=width-125;

    InitWindow(width, height, "Pong");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ball1.checkcollison(player,opponet);
        ball1.updatepos();

        player.reciveInput();
        player.display();
        //opponet.GenerateMovment(ball1);
        opponet.display();
        ClearBackground(BLACK);
        DrawText("Hello, world!", 10, 10, 20, DARKGRAY);
        //DrawCircle(100,100,50,BLACK);
        EndDrawing();
    }
    printf("window closed");
    CloseWindow();
    return 0;
}