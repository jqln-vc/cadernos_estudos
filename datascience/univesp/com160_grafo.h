/*
    COM160: Estruturas de Dados

    Semana 6: Árvores AVL e Grafos
      -> Grafos
            -: lógica (header): 
                L: classe Fila Encadeada: com160_fila_encadeada.h
                L: classe Vértice: com160_vertice.h
                L: classe Grafo: com160_grafo.h
                L: struct Vertice Nodetype: com160_grafo_nodetype.h
            -: implementação: com160_estruturas_dados_semana6_b.cpp
            -: execução: com160_grafo_main.cpp


            -: comando de compilação (certificar-se de estar no folder)
                g++ com160_grafo_main.cpp com160_estruturas_dados_semana6_b.cpp -o grafo
            -: execução após compilação
                .\grafo
*/


#ifndef GRAFO_H 
#define GRAFO_H 

#include "com160_fila_encadeada.h"

class Grafo {  
    private:  
        int NULL_ARESTA; // Constante para representar arestas nulas
        int maxVertices; // Número máximo de vértices
        int numVertices; // Número de vértices adicionados
        Vertice* vertices; // Array com todos os vértices
        int** adjacencias; // Matriz de adjacências -> sintaxe ** é um ponteiro para ponteiro
        bool* marcasVertices; // marcasVertices[i] marca se vertices[i] foi usado.
        int getIndex(Vertice); // Acessa o índice do vértice na matriz 
    
    public:
        Grafo(int max = 50, int null = 0);  // construtor
        ~Grafo(); // destrutor

        void adicionarVertice(Vertice);
        void adicionarAresta(Vertice, Vertice, int); // int: peso da aresta

        int getPeso(Vertice, Vertice);
        void getAdjacencias(Vertice, FilaEncadeada&); // adiciona as adjacências de um vértice em uma fila encadeada
        
        void limparMarcasVertices();
        void marcarVertice(Vertice);
        bool marcado(Vertice);
        void printMatriz();
};

#endif