//
// Created by Giuseppe Stancanelli on 19/04/24.
//
#include <iostream>
#include "Checkers.h"

using namespace std;




int main(){
    cout<<"White: ▣; Black: ▢; Nothing: # " <<endl;
    Checkers *checkers=new Checkers(8,8);
    int y,x;
    bool direction;
    int winner=0;
    do{
        cout<<((checkers->getRound()==0) ? "BLACK" : "WHITE" )<<" round x, y, direction "<< endl;
        cin>>x>>y>>direction;
        if(checkers->move(x, y, direction)){checkers->setRound();}
        checkers->printCheckers();
        winner=checkers->isEnd();
    }while(winner ==4);
    switch (winner) {
        case WHITE:
            cout<<"WHITE wins"<<endl;
            break;
        case BLACK:
            cout<<"Black wins"<<endl;
            break;
        case NOTHING:
            cout<<"PAWN wins"<<endl;
            break;
        default:
            cout<<"error in switch at the end"<<endl;
            break;
    }
}
