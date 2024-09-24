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


#include "com160_grafo.h"
#include <iostream>

int main() {
  Grafo grafo;
  Vertice a = Vertice("A"); grafo.adicionarVertice(a);
  Vertice b = Vertice("B"); grafo.adicionarVertice(b);
  Vertice c = Vertice("C"); grafo.adicionarVertice(c);
  Vertice d = Vertice("D"); grafo.adicionarVertice(d);
  Vertice e = Vertice("E"); grafo.adicionarVertice(e);
  
  grafo.adicionarAresta(a, b, 2);  
  grafo.adicionarAresta(a, c, 1);
  grafo.adicionarAresta(b, c, 3);  
  grafo.adicionarAresta(c, e, 4);
  grafo.adicionarAresta(d, e, 5);

  grafo.printMatriz(); 
  std::cout << std::endl;
}
