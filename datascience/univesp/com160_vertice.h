#ifndef Vertice_H 
#define Vertice_H 

#include <iostream>

class Vertice {
    public:
    Vertice(){
        this -> nome = "";
    }
    Vertice(std::string nome){
        this -> nome = nome;
    }
    std::string getNome() const {
        return nome;    
    }  
    private :
    std::string nome;
};

#endif