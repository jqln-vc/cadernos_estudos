/*
    COM160: Estruturas de Dados

    Semana 3: Organização dos Dados na Memória (contíguo ou disperso)
        -> Lista Encadeada (Linked List)
        -> Pilha (pilhaEncadeada): lista encadeada
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



#ifndef NODETYPE_H 
#define NODETYPE_H   

    typedef char ItemType; // aceita somente tipo "char"

    /*
        -> PILHA: não será mais necessário usar a váriavel "tamanho" 
            -: a qual indicava o TOPO da PILHA
                L: o TOPO será indicado pelo ponteiro "estrutura"
                l: "proximo": NÓ ABAIXO
        -> FILA: mantidos os ponteiro para INICIO e FINAL
            -: ambos usados com o tipo ponteiro NodeType apontando para "proximo"
            -: INICIO: onde remover()
            -: FINAL: onde inserir()
    */ 
    struct NodeType {
        ItemType data;  // dado do nó
        NodeType* proximo; // ponteiro para próximo NÓ
    };

#endif