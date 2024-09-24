/*
    COM160: Estruturas de Dados

    Semana 6: Árvores AVL e Grafos
      -> Árvore AVL
            -: lógica (header): 
                L: classe Aluno: com160_aluno.h
                L: classe Árvore AVL: com160_arvore_avl.h
            -: implementação: com160_estruturas_dados_semana6_a.cpp
            -: execução: com160_arvore_avl_main.cpp


            -: comando de compilação (certificar-se de estar no folder)
                g++ com160_arvore_avl_main.cpp com160_estruturas_dados_semana6_a.cpp -o arvore_avl
            -: execução após compilação
                .\arvore_avl
*/


#include "com160_arvore_avl.h"
using namespace std;

const int NUM_ALUNOS = 15;

int main() {
    arvoreBuscaAVL arvoreBuscaAVL;

    int ras[NUM_ALUNOS] = {
        41, 27, 74,  4, 29,
        65, 90,  2,  6, 28,
        30, 60, 73, 80, 92};
    
    string nomes[NUM_ALUNOS] = {
        "Enelton", "Cristhof", "Danielle",
        "Meira", "Guilherme", "Juliana", 
        "Pedro", "Raul", "Paulo",
        "Carlos", "Lucas", "Maria",
        "Samanta", "Ulisses", "Carlos"};
    Aluno alunos[NUM_ALUNOS];

    for (int i = 0; i < NUM_ALUNOS; i++){
        Aluno aluno = Aluno(ras[i], nomes[i]);
        alunos[i] = aluno;
        arvoreBuscaAVL.inserirAluno(aluno);
    }

    cout << "Pre:  ";
    arvoreBuscaAVL.printPreOrdem();
    cout << endl;
    cout << "In:   ";
    arvoreBuscaAVL.printInOrdem();
    cout << endl;
    cout << "Pos: ";
    arvoreBuscaAVL.printPosOrdem();
    cout << endl;

    // Removendo alguns alunos
    arvoreBuscaAVL.removerAluno(alunos[0].getRa());
    arvoreBuscaAVL.removerAluno(alunos[11].getRa());
    arvoreBuscaAVL.removerAluno(alunos[5].getRa());
    arvoreBuscaAVL.removerAluno(alunos[12].getRa());
    
    cout << "********" << endl;
    cout << "Pre:  ";
    arvoreBuscaAVL.printPreOrdem();
    cout << endl;
    cout << "In:   ";
    arvoreBuscaAVL.printInOrdem();
    cout << endl;
    cout << "Pos: ";
    arvoreBuscaAVL.printPosOrdem();
    cout << endl;
}