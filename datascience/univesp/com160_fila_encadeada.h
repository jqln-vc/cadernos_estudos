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

#include "com160_lista_encadeada_nodetype.h"

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

