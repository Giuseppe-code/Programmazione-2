//
// Created by Giuseppe Stancanelli on 19/04/24.
//

#ifndef PROGRAMMAZIONE_2_CHECKERS_H
#define PROGRAMMAZIONE_2_CHECKERS_H
#include <iostream>
#include "Box.h"
#include "Color.h"
#define DEBUG 0
using namespace std;
class Checkers{
    private:
        Box ***box;
        bool round;//0 black, 1 white
        Pawn **whitePawn;
        Pawn **blackPawn;
        int dim1;
        int dim2;
    public:
        Checkers(int dim1, int dim2){
            whitePawn= new Pawn*[12];
            blackPawn= new Pawn*[12];
            round=true;
            int countWhite=0;
            int countBlack=0;
            this->dim1=dim1;
            this->dim2=dim2;
            for(int i=0; i<12; i++){
                whitePawn[i] =new Pawn(WHITE);
                blackPawn[i] =new Pawn(BLACK);

            }

            box= new Box**[dim1];
            for(int i=dim1-1; i>=0; i--){
                box[i]= new Box*[dim2];
                for(int j=dim2-1; j>=0; j--){
                    switch(initialize(i,j)){
                        case WHITE:
                            box[i][j]= new Box(whitePawn[countWhite]);
                            countWhite++;
                            cout<<"▣";
                            break;
                        case BLACK:
                            box[i][j]= new Box(blackPawn[countBlack]);
                            countBlack++;
                            cout<<"▢";
                            break;
                        default:
                            box[i][j]= new Box(new Pawn(NOTHING));
                            cout<<"#";
                    }
                    cout<<" ";
                }
                cout<<""<<endl;
            }
            cout<<"\n\n\n"<<endl;
            printCheckers();
        }

    bool movePawn(int y, int x, int direction ) {
        int newPosY=y;
        int newPosX=x+ ((direction ==1 ) ? 1 : -1);
        if(checkColor(y, x, BLACK)){
            newPosY--;
        } else if(checkColor(y, x, WHITE)){
            newPosY++;
        }
        if(!checkExist(newPosY, newPosX)) return false;
        if(!checkColor(newPosY,newPosX, NOTHING) ) return false;

        Box *newBox=box[y][x];
        box[y][x]=box[newPosY][newPosX];
        box[newPosY][newPosX]=newBox;
        return true;
    }

    bool eatPawn(int posY, int posX, int direction) {
        int newPosY=posY;
        int enemiesPosY=posY;
        if(box[posY][posX]->getPawn()->getColor()==BLACK){
            newPosY-=2;
            enemiesPosY--;
        }else{
            newPosY+=2;
            enemiesPosY++;
        }

        int newPosX=posX+ ((direction ==1 ) ? 2 : -2);
        int enemiesPosX=posX+ ((direction ==1 ) ? 1 : -1);


        if(!checkExist(newPosY, newPosX)) return false;
        if(!checkExist(enemiesPosY, enemiesPosX)) return false;
        if(!checkColor(newPosY,newPosX, NOTHING) ) return false;

        box[enemiesPosY][enemiesPosX]->getPawn()->setDefeat();

        Box *newBox=box[posY][posX];
        box[posY][posX]=box[newPosY][newPosX];
        box[newPosY][newPosX]=newBox;
        return true;
    }

    bool move(int posX, int posY, bool direction){
            //posX--;
            //posY--;
            int newPosX=posX+ ((direction ==1 ) ? 1 : -1);
            int newPosY=posY +((round)? 1 : -1);
            if(!checkExist(posY, posX)) return false;
            if(!checkItem(posY, posX,round))   return false;


            if(!checkExist(newPosY, newPosX)) return false;

            if(checkItem(newPosY, newPosX, NOTHING)){
                movePawn(posY, posX, direction);
                return true;
            }
            if(checkItem(newPosY, newPosX, box[posY][posX]->getPawn()->getColor()) ) return false;//you can't eat your pawnre
            return eatPawn(posY, posX, direction);
    }

        bool checkColor(int y, int x, int z){
            return box[y][x]->getPawn()->getColor()==z;
        }
        int checkExist(int newPosY, int newPosX){
            return (0 <= newPosY && newPosY < dim1) && (0 <= newPosX && newPosX < dim2);
        }
        int checkItem(int y, int x, int color){
            return box[y][x]->getPawn()->getColor() == color;
        }

        int isEnd(){
            int numBlackDefeat=0;
            int numWhiteDefeat=0;
            for(int i=0; i<12; i++){
                if(blackPawn[i]->getColor()!=NOTHING) break;
                numBlackDefeat++;
            }
            for(int i=0; i<12; i++){
                if(whitePawn[i]->getColor()!=NOTHING) break;
                numWhiteDefeat++;
            }
            if(isPath())
                return NOTHING;
            if(numWhiteDefeat==12){
                return BLACK;
            }
            if(numBlackDefeat == 12)
                return WHITE;
            return 4;
        }

        bool getRound(){
            return round;
        }
        void setRound(){
            round=!round;
        }
        void printCheckers(){
            cout<<"White: ▣; Black: ▢; Nothing: #;"<<endl;
            for(int i=dim1-1; i>=0; i--){
                cout<< i<<" ";
                for(int j=0; j<dim2; j++){
                    switch(box[i][j]->getPawn()->getColor()){
                        case BLACK:
                            cout<<"▢";
                            break;
                        case WHITE:
                            cout<<"▣";
                            break;
                        default:
                            cout<<"#";
                    }
                    cout<<" ";
                }
                cout<<""<<endl;
            }
            cout<<"  0 1 2 3 4 5 6 7"<<endl;
        }
    private:
        bool isPath(){
            int numBlackStopped=0;
            int numWhiteStopped=0;
            for(int i=0; i<dim1; i++){
                for (int j=0; j<dim2; j++) {
                    if(box[i][j]->getPawn()->getColor()==BLACK){
                        numBlackStopped++;
                        if(existMoveToDo(i,j,BLACK))
                            numBlackStopped--;
                    }
                    if(box[i][j]->getPawn()->getColor()==WHITE){
                        numWhiteStopped++;
                        if(existMoveToDo(i,j,WHITE))
                            numWhiteStopped--;
                    }
                }
            }
            if(numBlackStopped==12 && numBlackStopped==numWhiteStopped)
                return true;
            return false;
        }
        bool existMoveToDo(int y, int x, int colorOfPawn){
            int colorEnemies=0;
            if(colorOfPawn==0)  colorEnemies=1;
            int newPosY=y +((colorOfPawn==WHITE)? 1 : -1);

            int posJump=newPosY;
            //x+1
            if(checkExist(newPosY, x+1)){
                if(checkItem(newPosY, x+1, NOTHING)){
                    return true;
                }
                if(checkItem(newPosY, x+1, colorEnemies)) {
                    posJump= newPosY +((colorOfPawn==WHITE)? 1 : -1);
                    if(checkExist(posJump, x+2)){
                        if(checkItem(posJump, x+2, NOTHING)){
                            return true;
                        }
                    }
                }
            }


            //x-1
            if(checkExist(newPosY, x-1)){
                if(checkItem(newPosY, x-1, NOTHING)){
                    return true;
                }
                if(checkItem(newPosY, x-1, colorEnemies)) {
                    posJump= newPosY +((colorOfPawn==WHITE)? 1 : -1);
                    if(checkExist(posJump, x-2)){
                        if(checkItem(posJump, x-2, NOTHING)){
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        int initialize(int i, int j){
            if(i==0 || i==2)//TODO ridurre
                if(j%2==1)
                    return WHITE;
            if(i==1)
                if(j%2==0)
                    return WHITE;

            if(i==5 || i==7)
                if(j%2==0)
                    return BLACK;
            if(i==6)
                if(j%2==1)
                    return BLACK;
            return NOTHING;
        }
};

#endif //PROGRAMMAZIONE_2_CHECKERS_H
