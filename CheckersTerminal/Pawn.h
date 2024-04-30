//
// Created by Giuseppe Stancanelli on 19/04/24.
//

#ifndef PROGRAMMAZIONE_2_PAWN_H
#define PROGRAMMAZIONE_2_PAWN_H
#include "Color.h"
class Pawn{
    private:
        int color;
    public:
        Pawn(int choose){
            color =choose; //0 null, 1 black, 2 white
        }
        int getColor(){
            return color;
        }
        int setDefeat(){
            color=NOTHING;
            return 0; //TODO Eseguire caso finale
        }
};
#endif //PROGRAMMAZIONE_2_PAWN_H
