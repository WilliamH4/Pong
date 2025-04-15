#include "C:\raylib\include\raylib.h"
#include <stdio.h>
#include <stdlib.h>

int height=1000;
int width=1800;
int score[2]={0,0};

class ball;

class blocker{

    public:
    int ycord=0;
    int thickness=25;
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
    void GenerateMovment(const ball& b);

    void display(){
        DrawRectangle(xcord,ycord,thickness,blockerHeight,WHITE);
    }


};


class ball{
    public:
    int radius=25;
    int velo[2]={-5,0};
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
                int middle=b1.ycord+b1.blockerHeight/2;
                float placeholder = ((pos[1] - middle) / (b1.blockerHeight / 2.0f)) * 10.0f;             
                printf("pholder: %f\n",placeholder);
                velo[1]+=placeholder;
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

        //for the right and left walls

        //left
        if ((pos[0]-radius<0&&velo[0]<0)){
            velo[0]=-velo[0];
            printf("scored");
            score[0]+=1;

        //left
        }else if (pos[0]+radius>width&&velo[0]>0){
            velo[0]=velo[0]*-1;
            printf("scored");
            score[1]+=1;

        }


    }

};

void blocker::GenerateMovment(const ball& b){
        int middle=ycord+blockerHeight/2;
        int dif=b.pos[1]-middle;
        int maxSpeed=5;
        //right now the code just trys to match the y cordnits of the blocker with that of the ball but it has a limitid speed to make it beatable
        if(dif>maxSpeed){
            dif=maxSpeed;
        }else if(dif<-maxSpeed){
            dif=-maxSpeed;
        }
        ycord+=dif;
    }

int main() {
    SetTraceLogLevel(LOG_NONE);

    ball ball1;

    blocker player;
    blocker opponet;

    player.xcord=50;
    opponet.xcord=width-125;


    InitWindow(width, height, "Pong");
    SetTargetFPS(120);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        ball1.checkcollison(player,opponet);
        ball1.updatepos();


        player.reciveInput();
        player.display();


        opponet.GenerateMovment(ball1);
        opponet.display();

        char text[20];

        sprintf(text,"%s%d%s%d","score: ",score[0]," to ",score[1]);

        DrawText(text,width/2,height/8,40,GRAY);

        EndDrawing();
    }
    printf("window closed");
    CloseWindow();
    return 0;
}