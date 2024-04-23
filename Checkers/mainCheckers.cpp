//
// Created by Giuseppe Stancanelli on 19/04/24.
//
#include <iostream>
#include "Box.h"
#include "Pawn.h"
#include "Checkers.h"
#include "Color.h"

using namespace std;




int main(){
    cout<<"White: ▣; Black: ▢; Nothing: # " <<endl;
    Checkers *checkers=new Checkers(8,8);
    int y,x;
    bool direction;
    do{
        cout<<((checkers->getRound()==0) ? "BLACK" : "WHITE" )<<" round x, y, direction "<< endl;
        cin>>x>>y>>direction;
        if(checkers->move(x, y, direction)){checkers->setRound();}
        checkers->printCheckers();

    }while(checkers->isEnd());
}
