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
        Demand(string A_answer, string B_answer, string C_answer, string D_answer, int correct){
            answers[0]=A_answer;
            answers[1]=B_answer;
            answers[2]=C_answer;
            answers[3]=D_answer;
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
            return index-1==correct;
        }
};

#endif //PROGRAMMAZIONE_2_DEMAND_H
