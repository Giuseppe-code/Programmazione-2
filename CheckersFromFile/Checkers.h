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
        Checkers(){
            dim1=8;
            dim2=8;
            whitePawn= new Pawn*[12];
            blackPawn= new Pawn*[12];
            round=true;
            int countWhite=0;
            int countBlack=0;
            for(int i=0; i<12; i++){
                whitePawn[i] =new Pawn(WHITE);
                blackPawn[i] =new Pawn(BLACK);
            }

            //TODO inserire colore delle box, casella bianca o nera
            box= new Box**[dim1];
            for(int i=dim1-1; i>=0; i--){
                box[i]= new Box*[dim2];
                for(int j=dim2-1; j>=0; j--){

                    switch(initialize(i,j)){
                        case WHITE:
                            whitePawn[countWhite]->setPosY(i);
                            whitePawn[countWhite]->setPosX(j);
                            box[i][j]= new Box(whitePawn[countWhite]);
                            countWhite++;
                            break;
                        case BLACK:
                            blackPawn[countWhite]->setPosY(i);
                            blackPawn[countWhite]->setPosX(j);
                            box[i][j]= new Box(blackPawn[countBlack]);
                            countBlack++;
                            break;
                        default:
                            box[i][j]= new Box(NULL);
                    }
                    box[i][j]->setColorBox(colorBox(i,j));
                }
            }
            printCheckers();//far vedere la posizione di partenza della scacchiera
        }

    bool movePawn(int y, int x, int direction ) {
        int newPosY=y;
        int newPosX=x+ ((direction ==1 ) ? 1 : -1);
        if(checkColor(y, x, BLACK)){
            newPosY--;
        } else if(checkColor(y, x, WHITE)){
            newPosY++;
        }
        if(!checkExistCoordinate(newPosY, newPosX)) return false;
        if(!checkIsNull(newPosY,newPosX)) return false;

        Pawn *pawnBuffer=box[y][x]->getPawn();
        //new Coordinate
        pawnBuffer->setPosX(newPosX);
        pawnBuffer->setPosY(newPosY);

        box[y][x]->freePawn();
        box[newPosY][newPosX]->setPawn(pawnBuffer);
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


        if(!checkExistCoordinate(newPosY, newPosX)) return false;
        if(!checkExistCoordinate(enemiesPosY, enemiesPosX)) return false;
        if(!checkIsNull(newPosY,newPosX) ) return false;

        box[enemiesPosY][enemiesPosX]->getPawn()->setDefeat();

        Pawn *pawnBuffer=box[posY][posX]->getPawn();
        box[posY][posX]->freePawn();
        //new Coordinate
        pawnBuffer->setPosX(newPosX);
        pawnBuffer->setPosY(newPosY);

        box[newPosY][newPosX]->setPawn(pawnBuffer);
        return true;
    }

    bool move(int numberPawn, int direction){
        int posX=0;
        int posY=0;
        if(!existPawn(numberPawn)) return false;
        if(!(direction==0 || direction==1)) return false;
        if(round==WHITE){
            posX=whitePawn[numberPawn]->getPosX();
            posY=whitePawn[numberPawn]->getPosY();
        }else{
            posX=blackPawn[numberPawn]->getPosX();
            posY=blackPawn[numberPawn]->getPosY();
        }

        int newPosX=posX+ ((direction ==1 ) ? 1 : -1);
        int newPosY=posY +((round)? 1 : -1); //nella dama le pedine bianche "salgono" le pedine nere "scendono"

        if(!checkExistCoordinate(newPosY, newPosX)) return false;

        if(checkIsNull(newPosY, newPosX)){
            movePawn(posY, posX, direction);
            return true;
        }
        if(checkColorItem(newPosY, newPosX, box[posY][posX]->getPawn()->getColor()) ) return false;//you can't eat your pawnre
        return eatPawn(posY, posX, direction);
    }

    int existPawn(int numberPawn){
            if(!(numberPawn<12 && numberPawn>=0)) return false;
            if(round==WHITE){
                return whitePawn[numberPawn]->getColor()!=NOTHING;
            }
            return blackPawn[numberPawn]->getColor()!=NOTHING;
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
        if(numWhiteDefeat==12){
            return BLACK;
        }
        if(numBlackDefeat == 12)
            return WHITE;
        return 4;
    }

    int whoWin(){
        int numBlackDefeat=0;
        int numWhiteDefeat=0;
        for(int i=0; i<12; i++){
            if(blackPawn[i]->getColor()==NOTHING)
                numBlackDefeat++;
        }
        for(int i=0; i<12; i++){
            if(whitePawn[i]->getColor()==NOTHING)
                numWhiteDefeat++;
        }
        if(numWhiteDefeat==numBlackDefeat)
            return NOTHING;
        if(numWhiteDefeat>numBlackDefeat){
            return BLACK;
        }
        return WHITE;
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
                if(checkIsNull(i,j)){ cout<<"#";}
                else {
                    switch (box[i][j]->getPawn()->getColor()) {
                        case BLACK:
                            cout <<"▢";
                            break;
                        case WHITE:
                            cout <<"▣";
                            break;
                        default:
                            cout<<"#";
                            break;
                    }
                }
                cout<<" ";
            }
            cout<<" "<<endl;
        }
        cout<<"  0 1 2 3 4 5 6 7"<<endl;
    }
    private:
        bool checkColor(int y, int x, int z){
            return box[y][x]->getPawn()->getColor()==z;
        }
        int checkExistCoordinate(int newPosY, int newPosX){
            return (0 <= newPosY && newPosY < dim1) && (0 <= newPosX && newPosX < dim2);
        }
        int checkColorItem(int y, int x, int color){
            return box[y][x]->getPawn()->getColor() == color;
        }
        int checkIsNull(int y, int x){
            return box[y][x]->getPawn()==NULL;
        }
        Color colorBox(int y, int x){
            //ricordiamo che y e x partono da 0, per comodità grafiche aumento di uno
            y++;
            x++;
            if((x+y)%2==0){
                return BLACK;
            }
            return WHITE;
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
