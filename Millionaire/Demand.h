//
// Created by Giuseppe Stancanelli on 19/04/24.
//

#ifndef PROGRAMMAZIONE_2_DEMAND_H
#define PROGRAMMAZIONE_2_DEMAND_H

#include <fstream>
#include <iostream>
using namespace std;

class Demand{
    private:
        string text;
        string answers[4];
        int correct;
    public:
        Demand(istream *input){
            getline(*input, text);
            for(int i=0; i<4; i++){
                getline(*input, answers[i]);
            }
            string buffer;
            getline(*input, buffer);
            correct=stoi(buffer);
        }
        Demand(string answers[4], int correct){
            for(int i=0; i<4; i++){
                this->answers[i]=answers[i];
            }
            this->correct=correct;
        }
        Demand(string text, string answers[4], int correct){
            this->text=text;
            this->correct=correct;
            for(int i=0; i<4; i++){
                this->answers[i]=answers[i];
            }
        }
        void readText(){
            cout<<text<<endl;
            for(int i=0; i<4; i++){
                cout<<i+1<<")"<<answers[i]<<endl;
            }
        };
        bool guess(int index){
            //cout<<((index-1==correct) ? ("correct") : ("not correct")) <<endl;
            return index-1==correct;
        }
};

#endif //PROGRAMMAZIONE_2_DEMAND_H
