//
// Created by Giuseppe Stancanelli on 19/04/24.
//
#include <iostream>
#include <fstream>
#include "Demand.h"
using namespace std;
ifstream* openFile(){
    ifstream *stream= new ifstream;
    stream->open("Millionaire/inputMilionaire.txt");
    if(!stream->is_open()){
        cerr << "Errore nell'apertura del file di input" << endl;
        //exit(-1);
    }
    string elemento;

    return stream ;
}


Demand** demandCreate( ifstream *instream, int numberQuestions){
    Demand** demand=new Demand*[numberQuestions];;
    for(int i=0; i<numberQuestions; i++){
        demand[i] = new Demand(instream); // Chiamata al costruttore di default
        string buffer;
        getline(*instream, buffer);
    }
    return demand;
}
int main(){
    ifstream *instream = openFile();
    string buffer;
    getline(*instream, buffer);
    int numberQuestions = stoi(buffer);
    int answer=0;
    int countCorrectAnswer=0;
    Demand **demand= demandCreate(instream, numberQuestions);
    instream->clear();
    instream->seekg(0);
    instream->close();

    for(int i=0; i<numberQuestions; i++){
        demand[i]->readText();
        cin>>answer;
        if(demand[i]->guess(answer))
            countCorrectAnswer++;
    }
    cout<<"hai indovinato"<<countCorrectAnswer<<" su "<<numberQuestions<<endl;
    cout<<"totale "<< 100*countCorrectAnswer/numberQuestions<<"%"<<endl;




}