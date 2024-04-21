//
// Created by Giuseppe Stancanelli on 19/04/24.
//

#ifndef PROGRAMMAZIONE_2_CHECKERS_H
#define PROGRAMMAZIONE_2_CHECKERS_H
#include <iostream>
#include "Box.h"
#include "Color.h"
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
            round=1;
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

    bool movePawn(int y, int x, int offsetX) {
        Box *newBox=box[y][x];
        box[y][x]=box[y+1][x + offsetX];
        box[y+1][x + offsetX]=newBox;
        return true;
    }

    bool eatPawn(int posY, int posX, int direction) {
            int newPosY=posY+2;
            int newPosX=posX+ ((direction ==1 ) ? 2 : -2);
            int enemiesPosX=posX+ ((direction ==1 ) ? 1 : -1);
            if(checkExist(newPosY, newPosX)){
                if(checkItem(newPosY, newPosX, NOTHING)){
                    box[posY+1][enemiesPosX]->getPawn()->setDefeat();
                    return movePawn(posY+1,posX,newPosX-posX);
                }
            }
            return false;
    }

    bool move(int posX, int posY, bool move){
            posX=dim1-posX;//TODO controllare perché la matrice è invertita nella stampa e non so se il calcolo è giusto
            posY--;
            int newPosX=posX;
            int newPosY=posY+1;
            if(!checkItem(posY, posX,round)){
                return false;
            }

            if(move==1){
                newPosX++;
            }else{
                newPosX--;
            }

            if(checkExist(newPosY, newPosX))
                if(checkItem(newPosY, newPosX, NOTHING)){
                    movePawn(posX, posY, move);
                    return true;
                }
                if(checkItem(newPosY, newPosX, round)) {//you can't eat your pawn
                    return false;
                }else{
                    if(checkExist(newPosY + 1, newPosX + 1)){
                        if(checkItem(newPosY+1, newPosX+1, NOTHING)){
                            return eatPawn(posY, posX, move);
                        }
                    }
                    return true;
                }
            }

        int checkExist(int newPosY, int newPosX){
            return (0 <= newPosY && newPosY <= 8) && (0 <= newPosX && newPosX <= 8);
        }
        int checkItem(int y, int x, int color){
            if(box[y][x]->getPawn()->getColor() != color){
                cout<<"Bro hai sbagliato non è il tuo turno/ non puoi mangiare la tua casella";
            }
            return box[y][x]->getPawn()->getColor() == color;
        }
        int isEnd(){
            return true;
        }
        int getRound(){
            return round;
        }
        void printCheckers(){
            cout<<"Stampa----- White: ▣; Black: ▢; Nothing: #;"<<endl;
            for(int i=dim1-1; i>=0; i--){
                for(int j=0; j<dim2; j++){
                    cout<<"y:"<<i;
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
                    cout<<"x:"<<j;
                    cout<<" ";
                }
                cout<<""<<endl;
            }
        }
        int initialize(int i, int j){
            if(i==0 || i==2)
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
