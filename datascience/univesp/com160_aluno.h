/*
    COM160: Estruturas de Dados

    Semana 5: Árvores Binárias de Busca
        -> 
            -: lógica (header): 
                L: classe Aluno: com160_aluno.h
                L: struct No: com160_arvore_busca.h
                L: classe ArvoreBusca: com160_arvore_busca.h
                
            -: implementação: 
                L: classe Aluno: com160_estruturas_dados_semana5.cpp
                L: árvore de busca: com160_estruturas_dados_semana5.cpp
            -: execução: com160_arvore_busca_main.cpp
*/


#include <iostream>
using namespace std;


class Aluno {
    private :
        int ra;
        std::string nome;  
    public:  
        Aluno();
        Aluno(int ra, std::string nome);
        string getNome() const;
        int getRa() const;
};

