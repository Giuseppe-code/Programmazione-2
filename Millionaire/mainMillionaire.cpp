//
// Created by Giuseppe Stancanelli on 19/04/24.
//
#include <iostream>
#include <fstream>
#include "Demand.h"
using namespace std;
ifstream openFile(){
    ifstream instream("inputMilionaire.txt");
    if(!instream){
        cerr << "Errore nell'apertura del file di input" << endl;
        exit(-1);
    }
    return instream ;
}


Demand **demandCreate(fstream instream, int numberQuestions){
    Demand** demand= new Demand*[numberQuestions];
    for(int i=0; i<numberQuestions; i++){
        demand[i] = new Demand(instream); // Chiamata al costruttore di default
    }
    return demand;
}
int main(){
    ifstream instream = openFile();
    string buffer;
    getline(instream, buffer);
    int numberQuestions = stoi(buffer);

    Demand **demand= demandCreate(instream, numberQuestions);





    instream.clear();
    instream.seekg(0);

}