/*
    COM160: Estruturas de dadosAlunos

    Semana 5: Árvores Binárias de Busca
        -> 
            -: lógica (header): 
                L: classe Aluno: com160_aluno.h
                L: struct No: com160_arvore_busca.h
                L: classe ArvoreBusca: com160_arvore_busca.h
                
            -: implementação: 
                L: classe Aluno: com160_estruturas_dadosAlunos_semana5.cpp
                L: árvore de busca: com160_estruturas_dadosAlunos_semana5.cpp
            -: execução: com160_arvore_busca_main.cpp
*/

#include <cstddef>
#include <iostream>
#include "com160_aluno.h"


// ESTRUTURA DO NÓ: recursiva ->> cada Nó da esquerda/direita possui a mesma estrutura
struct EstruturaNo { //NodeType
    Aluno aluno;
    EstruturaNo* esquerda;
    EstruturaNo* direita;
};



class ArvoreBusca { // SearchTree
    // interface pública MÉTODOS RECURSIVOS, invocando métodos PRIVADOS (com acesso à RAÍZ)
    public:  
        ArvoreBusca() { // construtor
            raiz = NULL; 
        }  
        ~ArvoreBusca() { // destrutor
            deletarArvore(raiz); 
        }
        bool vazia() const; // isEmpty
        bool cheia() const; // isFull

        void obterAluno(Aluno& item, bool& found) const {
            obterAluno(raiz, item, found);
        }
        void inserirAluno(Aluno item) { 
            inserirAluno(raiz, item); 
        }  
        void removerAluno(int item) { 
            removerAluno(raiz, item); 
        }
        void printPreOrdem() const { 
            printPreOrdem(raiz); 
        }
        void printInOrdem() const { 
            printInOrdem(raiz); 
        }
        void printPosOrdem() const { 
            printPosOrdem(raiz); 
        }
        
    private:
        void deletarArvore(EstruturaNo*& tree); //destroyTree
        void obterAluno(EstruturaNo* tree, Aluno& item, bool& found) const; // retrieveAluno
        void inserirAluno(EstruturaNo*& tree, Aluno item);
        void removerAluno(EstruturaNo*& tree, int item);     
        void removerNo(EstruturaNo*& tree); 
        void getSucessor(EstruturaNo* tree, Aluno& data); // obter sucessor lógico
        void printPreOrdem(EstruturaNo* tree)  const; // preOrder
        void printInOrdem(EstruturaNo* tree)   const; // inOrder
        void printPosOrdem(EstruturaNo* tree) const;  // postOrder

        //  RAÍZ DA ÁRVORE BINÁRIA DE BUSCA
        EstruturaNo* raiz;
};
