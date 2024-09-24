/*
    COM160: Estruturas de Dados

    Semana 3: Organização dos Dados na Memória (contíguo ou disperso)
        -> Fila (Queue): lista encadeada
            -: lógica (header): com160_fila_encadeada.h
                L: node type (header/struct): com160_lista_encadeada_nodetype.h
            -: implementação: com160_estruturas_dados_semana3_b.cpp
            -: execução: com160_fila_encadeada_main.cpp
*/
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
/*
    FILA (QUEUE): lista encadeada
            -> estrutura do NÓ
                -: dado + ponteiros
                -: definido com STRUCT:
                    L: tipo de DADO personalizado
                    L: contém bloco de VARIÁVEIS RELACIONADAS
                -: usados 2 ponteiros: INÍCIO (remover) e FINAL (inserir) da fila
            -> INSERÇÃO e REMOÇÃO em TEMPO CONSTANTE
            -> UTILIDADES:
                -: garantia de que processos acessarão recursos compartilhados de maneira justa
*/

/*
    FILA ENCADEADA 
     -> tendo sua implementação utilizada também na semana 6, com grafos, com o tipo de nó modificado
        L: comentar de acordo com o arquivo a ser utilizado
*/

#ifndef FILA_H 
#define FILA_H 

// #include "com160_lista_encadeada_nodetype.h"
#include "com160_grafo_nodetype.h"

class FilaEncadeada {
    public:
        FilaEncadeada();   // !Construtor
        ~FilaEncadeada();   // !Destrutor

        bool vazia() const; // !isEmpty
        bool cheia() const; // !isFull
        void print() const; // !visualização padrão (index 0-n)
  
        void inserir(ItemType); // !enqueue
        ItemType remover();    // !dequeue
    
    private:
        NodeType* inicio; 
        NodeType* final; 
};

#endif
