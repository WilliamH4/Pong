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
    int maxSpeed=8;
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
    void GenerateMovment(const ball& b,int type);

    void display(){
        DrawRectangle(xcord,ycord,thickness,blockerHeight,WHITE);
    }


};


class ball{
    public:
    int radius=25;
    int startingVelo[2]={10,1};
    int velo[2]={startingVelo[0],startingVelo[1]};
    int pos[2]={400,175/2};
    int clock=0;
    void updatepos(){
        clock+=1;
        if (clock>500){
            clock=0;
            if (velo[0]>0){
                velo[0]+=1;
            }else {
                velo[0]-=1;
            }
        }
        pos[0]+=velo[0];
        pos[1]+=velo[1];

        DrawCircle(pos[0],pos[1],radius,WHITE);
    }
    void reset(){
        velo[0]=startingVelo[0];
        velo[1]=startingVelo[1];
        pos[0]=width/2;
        pos[1]=height/2;

    }
    
    void checkcollison(const blocker& b1, const blocker& b2){

        //for the player blocker
        if (b1.ycord<pos[1]&&b1.ycord+b1.blockerHeight>pos[1]&&pos[0]-radius<b1.xcord+b1.thickness){
            if (velo[0]<0){
                float ydif = ((pos[1] - (b1.ycord+b1.blockerHeight/2)) / (b1.blockerHeight / 2.0f)) * 10.0f;             
                printf("pholder: %f\n",ydif);
                velo[1]+=ydif;
                velo[0]=-velo[0];
            }
            return;
        }

        //for the opponet
        if (b2.ycord<pos[1]&&b2.ycord+b2.blockerHeight>pos[1]&&pos[0]+radius>b2.xcord){
            if (velo[0]>0){

                //the math to find out how much to change the y velo by
                float ydif = ((pos[1] - (b2.ycord+b2.blockerHeight/2)) / (b2.blockerHeight / 2.0f)) * 10.0f;             
                printf("pholder: %f\n",ydif);
                velo[1]+=ydif;


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
            reset();
            score[1]+=1;

        //left
        }else if (pos[0]+radius>width&&velo[0]>0){
            velo[0]=velo[0]*-1;
            printf("scored");
            reset();
            score[0]+=1;

        }


    }

};

void blocker::GenerateMovment(const ball& b,int type){
        int middle=ycord+blockerHeight/2;
        int maxSpeed=3;

        int yvelo=b.velo[1];

        int target=middle;
        int dif;
        int endy=height/2;
        int endSign;

        type=1;


        if (b.velo[0]>0){

            if (b.velo[1]>0){
                endSign=1;
            }else if (b.velo[1]<0){
                endSign=-1;
            }

            
            
            int deltaX=xcord-(b.pos[0]+b.radius);

            int framesTillContact=deltaX/b.velo[0];

            endy=b.pos[1]+b.velo[1]*framesTillContact;

            while (endy<b.radius||endy>height-b.radius){

                if (endy<b.radius){
                    endy=b.radius-(endy-b.radius);
                    endSign=1;
                }else if (endy>height-b.radius){
                    endy=(height-b.radius)-(endy-(height-b.radius));
                    endSign=-1;
                }
            }
            
            //printf("endy: %d\n",endy);
        }


        if (type==1){
        
            target = -(blockerHeight / 2.0f) * ((endSign*abs(b.velo[1]) / 10.0f) - 1.0f);



            //ycord=5;

            
            //printf("nycord: %d%s%d%s%d\n",nycord, " delta: ",delta," yvelo: ",b.velo[1]);
            //ycord=nycord;


            //right now the code just trys to match the y cordnits of the blocker with that of the ball but it has a limitid speed to make it beatable

            dif=(endy-target)-ycord;
            //int dif=b.pos[1]-middle;
        }else if (type==0){

            dif =endy-middle;

        }



        if(dif>maxSpeed){
            dif=maxSpeed;
        }else if(dif<-maxSpeed){
            dif=-maxSpeed;
        }
        ycord+=dif;

        // ycord=b.pos[1]-target;

        //printf("target:%d%s%d%s%d%s%d\n",target," dif: ",dif," yvelo: ",b.velo[1]," ycord: ",ycord);


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
    int type=0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        ball1.checkcollison(player,opponet);
        ball1.updatepos();


        player.reciveInput();
        player.display();

        if (score[0]>score[1]){
            type=1;
        }else if(score[0]<score[1]){
            type=0;
        }


        opponet.GenerateMovment(ball1,type);
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