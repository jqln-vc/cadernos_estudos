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


#ifndef NODETYPE_H 
#define NODETYPE_H 

#include "com160_vertice.h"

typedef Vertice ItemType;

struct NodeType {
  ItemType dado;
  NodeType* proximo; // ponteiro para o próximo nó
};

#endif
