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
            for(int i=0; i<dim1; i++){
                box[i]= new Box*[dim2];
                for(int j=0; j<dim2; j++){
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

            printCheckers();
        }

    bool movePawn(int x, int y, int z) {
        Box *newBox=box[y][x];
        box[y][x]=box[y+1][x+z];
        box[y+1][x+z]=newBox;
        return false;
    }

    bool move(int posX, int posY, bool move){
            posX=dim1-posX+1;//TODO controllare perché la matrice è invertita nella stampa e non so se il calcolo è giust
            posY=dim2-posY+1;
            int newPosX=posX;
            int newPosY=posY+1;
            if(box[posX][posY]->getPawn()->getColor()!=round){
                return false;
            }
            if(move==1){//right
                newPosX++;
                if(check(newPosY, newPosX))
                    if(box[newPosY][newPosX]->getPawn()->getColor()==NOTHING){
                        movePawn(posX, posY, 1);
                        return true;
                    }
                    if(box[newPosY][newPosX]->getPawn()->getColor()==round) {//you can't eat your pawn
                        return false;
                    }else{
                        eatPawn(posY, posX, 1);
                        return true;
                    }
            }
            if(move==0){//left
                newPosX--;
                if(check(newPosY, newPosX))
                    if(box[newPosY][newPosX]->getPawn()->getColor()==NOTHING){
                        movePawn(posX, posY, 0);
                        return true;
                    }
                if(box[newPosY][newPosX]->getPawn()->getColor()==round) {//you can't eat your pawn
                    return false;
                }else{
                    eatPawn(posX, posY, 0);
                    return true;
                }
            }



        }
        int check(int newPosY, int newPosX){
            return (0 <= newPosY && newPosY <= 8) && (0 <= newPosX && newPosX <= 8)
        }
        int getRound(){
            return round;
        }
        void printCheckers(){
            cout<<"Stampa----- White: ▣; Black: ▢; Nothing: #;"<<endl;
            for(int i=dim1-1; i>=0; i--){
                for(int j=dim2-1; j>=0; j--){
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
