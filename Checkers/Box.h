//
// Created by Giuseppe Stancanelli on 19/04/24.
//

#ifndef PROGRAMMAZIONE_2_BOX_H
#define PROGRAMMAZIONE_2_BOX_H


#include "Pawn.h"

class Box {
    private:
        Pawn *pawn;
    public:
        Box(Pawn *pawn){
            this->pawn=pawn;
        }
        void setPawn(Pawn *pawn){
            this->pawn=pawn;
        }
        Pawn * getPawn(){
            return pawn;
        }
};


#endif //PROGRAMMAZIONE_2_BOX_H
