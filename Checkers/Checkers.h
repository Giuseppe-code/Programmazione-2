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
                    cout<<"y:"<<i;

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
                    cout<<"x:"<<j;
                    cout<<" ";
                }
                cout<<""<<endl;
            }

            printCheckers();
        }

    bool movePawn(int y, int x, int newPosY, int newPosX ) {
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

            box[enemiesPosY][enemiesPosX]->getPawn()->setDefeat();
            return movePawn(posY,posX, newPosY, newPosX);
    }

    bool move(int posX, int posY, bool move){
            //posX--;//TODO controllare perché la matrice è invertita nella stampa e non so se il calcolo è giusto
            //posY--;
            int newPosX=posX;
            int newPosY=posY +((round)? 1 : -1);
            if(!checkItem(posY, posX,round)){
                return false;
            }


            if(move){
                newPosX++;
            }else{
                newPosX--;
            }

            if(!checkExist(newPosY, newPosX)) return false;

            if(checkItem(newPosY, newPosX, NOTHING)){
                movePawn(posY, posX, newPosY, newPosX);
                return true;
            }
            if(checkItem(newPosY, newPosX, round)) return false;//you can't eat your pawnre

            //newPosY sarebbe la pos del pezzo da mangiare
            if(checkExist(newPosY+(newPosY-posY), newPosX+(newPosX-posX))){
                if(checkItem(newPosY+(newPosY-posY), newPosX+(newPosX-posX), NOTHING)){
                    return eatPawn(posY, posX, move);
                }
            }
            return false;
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
            if(numWhiteDefeat==12 || numBlackDefeat == 12)
                return false;
            if(isPath())
                return false;
            return true;
        }

        int whoWin(){
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
            if(numWhiteDefeat==12 && numBlackDefeat == 12)
                return NOTHING;
            if(numWhiteDefeat==12)
                return BLACK;
            if(numBlackDefeat==12)
                return WHITE;
            return NOTHING;
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
                    (DEBUG) ? (cout<<"x:"<<j) : 0;

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
                    (DEBUG) ? (cout<<"y:"<<i) : 0;
                    cout<<" ";
                }
                cout<<""<<endl;
            }
            cout<<"  0 1 2 3 4 5 6 7"<<endl;
        }
    private:
        bool isPath(){
            int numBlackNotStopped=0;
            int numWhiteNotStopped=0;
            for(int i=0; i<dim1; i++){
                for (int j=0; j<dim2; j++) {
                    if(box[i][j]->getPawn()->getColor()==BLACK){
                        if(checkExist(i-1, j-1)){
                            numBlackNotStopped++;
                            if(checkItem(i-1, j+1, NOTHING)){
                                numBlackNotStopped--;
                            }else if(checkItem(i-1, j+1, WHITE)) {
                                if(checkExist(i-2, j-2)){
                                    if(checkItem(i-2, j-2, NOTHING)){
                                        numBlackNotStopped--;
                                    }
                                }
                            }

                        }
                        if(checkExist(i-1, j+1)){
                            numBlackNotStopped++;
                            if(checkItem(i-1, j+1, WHITE) || checkItem(i-1, j+1, BLACK)){
                                numBlackNotStopped--;
                            }
                        }
                    }
                }
            }
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
