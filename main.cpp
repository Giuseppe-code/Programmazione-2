//
// Created by Giuseppe Stancanelli on 18/04/24.
//
#include <iostream>

const int dim=100;

using namespace std;
class Animal{
    private:
        int fame; //da 0 a 100
        string name;
    public:

        Animal(string name){
            this->name=name;
            this->fame=50;
        }

        Animal(){//costruttore di default
            this->name="noname";
            this->fame=50;
        }
        void mangia(int quantita){
            if(fame + quantita> 100)
                fame =100;
            else
                fame +=quantita;
        };
        int get_fame() const{
            return fame;
        }
        string get_name(){
            return name;
        }
        string set_name(string name){
            this->name=name;
        }
};

int main(int argc, char **argv){
    Animal *leone=new Animal("leone");
    cout<<leone->get_name()<<endl;

}