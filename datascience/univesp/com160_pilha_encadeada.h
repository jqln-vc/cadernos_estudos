/*
    COM160: Estruturas de Dados

    Semana 3: Organização dos Dados na Memória (contíguo ou disperso)
        -> Lista Encadeada (Linked List)
        -> Pilha (Stack): lista encadeada
            -: lógica (header): com160_pilha_encadeada.h
                L: node type (header/struct): com160_lista_encadeada_nodetype.h
            -: implementação: com160_estruturas_dados_semana3_a.cpp
            -: execução: com160_pilha_encadeada_main.cpp
*/
/*
    PILHA (STACK): lista encadeada
        -> estrutura do NÓ
            -: dado + ponteiro
            -: definido com STRUCT:
                L: tipo de DADO personalizado
                L: contém bloco de VARIÁVEIS RELACIONADAS
            -: basta um ÚNICO PONTEIRO que aponta para o INÍCIO
        -> TEMPO CONSTANTE: todas as operaçõe são feitas no topo da pilha
*/

#include "com160_lista_encadeada_nodetype.h"

class PilhaEncadeada {
    public:
        PilhaEncadeada();   // !Construtor
        ~PilhaEncadeada();   // !Destrutor

        bool vazia() const; // !isEmpty
        bool cheia() const; // !isFull
        void print() const; // !visualização padrão (index 0-n)
  
        void inserir(ItemType); // !push
        ItemType remover();    // !pop
    
    private:
        NodeType* estrutura; 
};

