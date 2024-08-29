/*
    COM160: Estruturas de Dados

    Semana 3: Organização dos Dados na Memória (contíguo ou disperso)
        -> Fila (fila): lista encadeada
            -: lógica (header): com160_fila_encadeada.h
                L: node type (header/struct): com160_lista_encadeada_nodetype.h
            -: implementação: com160_estruturas_dados_semana3_b.cpp
            -: execução: com160_fila_encadeada_main.cpp


            !comando de compilação (certificar de estar no folder)
                g++ com160_fila_encadeada_main.cpp com160_estruturas_dados_semana3_b.cpp -o fila_encadeada
            !execução após compilação
                .\fila_encadeada
*/



#include "com160_fila_encadeada.h"
#include "com160_pilha_encadeada.h"
#include <iostream>
using namespace std;


int main() {
    char caractereTeste1;
    FilaEncadeada filaEncadeada;
    char itemFilaEncadeada;

    cout << "Adicione uma sequência de caracteres. Pressione ENTER para FINALIZAR e SAIR: " << endl;
    cin.get(caractereTeste1);
    while (caractereTeste1 != '\n' and !filaEncadeada.cheia()) {
        filaEncadeada.inserir(caractereTeste1);
        cin.get(caractereTeste1);
    }
    
    while (!filaEncadeada.vazia()) {
        itemFilaEncadeada = filaEncadeada.remover();
        cout << itemFilaEncadeada;
    }
    cout << endl;

    /*
        TESTE DE PALÍNDROMO
            -> A string contém 0 ou mais caracteres
            -> A leitura é a mesma nos dois sentidos:  ESQUERDA <-> DIREITA
                -: ovo, arara, a dor roda
            -> Implementação em FILA e PILHA:
                -: 1. Cada caractere inputado será adicionado em uma FILA e uma PILHA
                -: 2. Ao término, fazer um laço para comparar os caracteres removidos de ambas:
                    L: PILHA: último caractere == FILA: primeiro caractere
                
    */

    bool palindromo = true;
    
    char caractereTeste2;
    char pilhaCaractere;
    char listaCaractere;
    
    PilhaEncadeada pilha;
    FilaEncadeada fila;    
    cout << "Teste de Palíndromo: Adicione uma sequência de caracteres. Pressione ENTER para FINALIZAR e SAIR: " << endl;    
    cin.get(caractereTeste2);

    while (caractereTeste2 != '\n') {
        pilha.inserir(caractereTeste2);
        fila.inserir(caractereTeste2);
        cin.get(caractereTeste2);
    }

    while (palindromo && !fila.vazia()) {
        pilhaCaractere = pilha.remover();
        listaCaractere = fila.remover();
        
        if (pilhaCaractere != listaCaractere) {
            palindromo = false;
        }
    }

    if (palindromo) {
        cout << "A string é um palíndromo." << endl;
    } else {
        cout << "A string não é um palíndromo." << endl;
    }

    return 0; 
}

