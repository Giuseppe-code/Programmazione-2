//
// Created by Giuseppe Stancanelli on 19/04/24.
//

#ifndef PROGRAMMAZIONE_2_PAWN_H
#define PROGRAMMAZIONE_2_PAWN_H
#include "Color.h"
class Pawn{
    private:
        int color;
        int posX;
        int posY;
    public:
        Pawn(int choose){
            color =choose; //0 null, 1 black, 2 white
        }
        int getColor(){
            return color;
        }
        void setDefeat(){
            color=NOTHING;
        }
        void setPosX(int posX){
            this->posX=posX;
        }
        void setPosY(int posY){
            this->posY=posY;
        }
        int getPosY(){
            return posY;
        }
        int getPosX(){
            return posX;
        }
};
#endif //PROGRAMMAZIONE_2_PAWN_H
