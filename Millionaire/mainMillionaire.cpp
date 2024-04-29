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
        exit(-1);
    }
    return stream ;
}


Demand** demandCreate( ifstream *instream, int numberQuestions){
    Demand** demand=new Demand*[numberQuestions];;
    for(int i=0; i<numberQuestions; i++){
        demand[i] = new Demand(instream);
        string buffer;
        getline(*instream, buffer);
    }
    return demand;
}
int main(){
    int numberQuestions = 0;
    int answers[numberQuestions];
    int countCorrectAnswer=0;

    string buffer;

    ifstream *instream = openFile();
    getline(*instream, buffer);
    numberQuestions = stoi(buffer);

    Demand **demand= demandCreate(instream, numberQuestions);

    instream->clear();
    instream->seekg(0);
    instream->close();

    for(int i=0; i<numberQuestions; i++){
        demand[i]->readText();
        cin>>answers[i];
        if(demand[i]->guess(answers[i]))
            countCorrectAnswer++;
    }

    cout<<"You got "<<countCorrectAnswer<<" out of "<<numberQuestions<<" question right"<<endl;
    cout<<"Total: "<< 100*countCorrectAnswer/numberQuestions<<"%"<<endl;


    ofstream outstream("Millionaire/outputMilionaire.txt");
    if(!outstream){
        cerr << "Errore nell'apertura del file di output" << endl;
        return 0;
    }
    for(int i=0; i<numberQuestions; i++){
        outstream<<answers[i]<<" ";
    }
    outstream<<endl;
    outstream.close();


}