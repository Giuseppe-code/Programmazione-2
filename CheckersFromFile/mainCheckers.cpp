//
// Created by Giuseppe Stancanelli on 19/04/24.
// La scacchiera è formata da una matrice di caselle, dove ogni casella contiene
// un punatore a NULL o un puntatore ad un pedone. Se il pedone viene sconfitto il pedone avrà colore
// color :Nothing; mentre il box che lo conteneva avrà puntatore NULL.
// Ogni pedone contiene le coordinate della casella dove esso è contenuto.
// Es. il pedone 3 biano, contenuto nella box[2][1] avrà coordinate y=2, x=1
// la lettura delle mosse include lo 0, la scacchiera va da 0 a 7
#include <iostream>
#include "Checkers.h"
#include <fstream>
#define DEBUG 0
using namespace std;




int main(int argv, char **argc){
    Checkers *checkers=new Checkers();
    int direction;
    int numberPawnToMove=0;
    int winner=4;

    ifstream instream("CheckersFromFile/move.txt");
    if(!instream){
        cout<<"Error in the open of the file"<<endl;
        exit(-1);
    }

    ofstream outstream("CheckersFromFile/output.txt");
    if(!outstream){
        cout<<"Error in the open of the file"<<endl;
        exit(-1);
    }

    outstream<<"           "<<endl;

    while((!instream.eof()) && winner==4){
        instream>>numberPawnToMove>>direction;
        if(checkers->move(numberPawnToMove, direction)){
            checkers->setRound();//turno del giocatore
            outstream<<"("<<numberPawnToMove<<","<<direction<<") ";
        }

        if(DEBUG){
            cout<<((checkers->getRound()==0) ? "BLACK" : "WHITE" )<<" round x, y, direction "<< endl;
            checkers->printCheckers();
        }
        winner=checkers->isEnd();//se qualcuno vince, il gioco non va più avanti

    };
    winner=checkers->whoWin();//finito il file o la partita verifica chi ha vinto


    outstream.seekp(0, ios::beg);
    switch (winner) {
        case WHITE:
            outstream<<"WHITE wins"<<endl;
            break;
        case BLACK:
            outstream<<"Black wins"<<endl;
            break;
        case NOTHING:
            outstream<<"PAWN"<<endl;
            break;
        default:
            outstream<<"error in switch at the end"<<endl;
            break;
    }

    instream.close();
    outstream.close();


}
