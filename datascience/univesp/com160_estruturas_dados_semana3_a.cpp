/*
    COM160: Estruturas de Dados

    Semana 3: Organização dos Dados na Memória (contíguo ou disperso)
        -> Lista Encadeada (Linked List)
        -> Pilha (Stack): lista encadeada
            -: lógica (header): com160_pilha_encadeada.h
                L: node type (header/struct): com160_lista_encadeada_nodetype.h
            -: implementação: com160_estruturas_dados_semana3_a.cpp
            -: execução: com160_pilha_encadeada_main.cpp


            !comando de compilação (certificar de estar no folder)
                g++ com160_pilha_encadeada_main.cpp com160_estruturas_dados_semana3_a.cpp -o pilha_encadeada
            !execução após compilação
                .\pilha_encadeada
*/
/*
    LISTA LINEAR:
        -> cada elemento tem 1 SUCESSOR e 1 PREDECESSOR, com exceção do primeiro e último elementos
        -> gera uma certa "ordenação" (INDEXAGEM) nos elementos
        -> as estruturas PILHA e FILA são listas lineares 
    
    LISTA LINEAR SEQUENCIAL (implementação de Pilha e Fila na semana 2)
        -> ORDEM LÓGICA (percebida pelo usuário) == ORDEM FÍSICA
        -> elementos vizinhos na lista estão em posições vizinhas de memória
        -> estrutura de VETOR
        -> ACESSO TEMPO CONSTANTE, a qualquer elemento, dado seu índice
        -> permite uso de BUSCA BINÁRIA
            -: O(log n)
        -> DESVANTAGENS:
            -: alocar espaço para todos os elementos de uma só vez
                L: caso falte espaço, é oneroso mover todos os elementos para uma nova posição
            -: manter a ORDEM é oneroso, necessário muitos deslocamentos em memória

    LISTA LINEAR ENCADEADA
        -> O(n)
            -: tanto para SINGLY (ponteiro sucessor) ou DOUBLY (ponteiro sucessor e predecessor)
        -> ORDEM LÓGICA (percebida pelo usuário) !== ORDEM FÍSICA
        -> elementos estão espalhados na memória
            -: cada elemento APONTA o endereço do seu SUCESSO
        -> para ACESSAR UM ELEMENTO é preciso percorrer TODOS SEUS PREDECESSORES (NÃO TEM ACESSO EM TEMPO CONSTANTE)
        -> VANTAGENS:
            -: número de elementos pode AUMENTAR ou DIMINUIR durante a EXECUÇÃO (desvantagem da lista sequencial)
                L: não é preciso deslocamento, só incluir/excluir um elemento
                    e mudar seus PONTEIROS para os NOVOS PREDECESSOR e SUCESSOR
            -: INSERÇÃO e REMOÇÃO em TEMPO CONSTANTE (isto é, independe do número de elementos na estrutura)

    
    PILHA (STACK): lista encadeada
        -> estrutura do NÓ
            -: dado + ponteiro
            -: definido com STRUCT:
                L: tipo de DADO personalizado
                L: contém bloco de VARIÁVEIS RELACIONADAS
            -: basta um ÚNICO PONTEIRO que aponta para o INÍCIO
        -> TEMPO CONSTANTE: todas as operaçõe são feitas no topo da pilha

*/


/*
    IMPLEMENTAÇÃO PILHA ENCADEADA
*/ 

#include "com160_pilha_encadeada.h"
#include <cstddef> // Para funcionar o NULL
#include <new>
#include <iostream>
using namespace std;

// construtor
PilhaEncadeada::PilhaEncadeada() {
    // a estrutura será inicializada sem apontar para nenhum local
    estrutura = NULL; // TOPO
}

/*
    destrutor
        -> a variável "estrutura" é o TOPO da PILHA ENCADEADA
        -> não podemos excluir "estrutura" sem antes excluir todos os nós encadeados
        -> ponteiroTemporário: recebe "estrutura", ou seja, o valor do NÓ e do PONTEIRO do próximo elemento, na base da pilha
            -: este ponteiro será apagado
        -> estrutura: passa a receber o NÓ, valor e ponteiro, de "proximo" (elemento abaixo)
        -> repete-se até que todos os NÓS da PILHA ENCADEADA sejam deletados
 */ 
PilhaEncadeada::~PilhaEncadeada() {
    NodeType* ponteiroTemporario;
    while (estrutura != NULL) {
        ponteiroTemporario = estrutura;
        estrutura = estrutura -> proximo; // o operador -> acessa a variável "proximo" do ponteiro NodeType*
        delete ponteiroTemporario;
    }
}

// método vazia()
bool PilhaEncadeada::vazia() const {
    return (estrutura == NULL); // não tem nenhum dado, nem aponta para lugar nenhum
}

/*
    método cheia()
        -> será realizado um teste de alocação de novo elemento
        -> caso seja possível (memória disponível), o elemento temporário será deletado
            -: retorna Falso
        -> caso esteja cheia, o erro "bad_alloc" será pego no catch
            -: retorna True
*/
bool PilhaEncadeada::cheia() const {
    NodeType* testeAlocacao;

    try {
        testeAlocacao = new NodeType;
        delete testeAlocacao;
        return false;
    } catch (std::bad_alloc exception) {
        return true;
    }
}

/*
  INSERÇÃO: método inserir()
    -> estrutura: TOPO
    -> proximo: NÓ ABAIXO
*/
void PilhaEncadeada::inserir(ItemType novoDado){
    if (!cheia()){
        NodeType* novaAlocacao; // NÓ TOPO
        novaAlocacao = new NodeType; // aloca um NOVO NÓ em qualquer lugar da memória
        novaAlocacao -> data = novoDado; // o NOVO NÓ recebe o dado
        novaAlocacao -> proximo = estrutura; // o NOVO NÓ recebe o PONTEIRO de "estrutura" (NÓ abaixo)
        estrutura = novaAlocacao; // TOPO: "estrutura" aponta o NOVO NÓ
    } else {
        throw "A pilha já está cheia!";
    }
}

/*
  REMOÇÃO: método remover()
    -> retorna o NÓ do TOPO DA PILHA
 */
ItemType PilhaEncadeada::remover(){
  if (!vazia()) {
    NodeType* ponteiroTemporario;
    ponteiroTemporario = estrutura;

    ItemType dadoTopo = estrutura -> data;
    estrutura = estrutura -> proximo;

    delete ponteiroTemporario;
    return dadoTopo;
  } else {
    throw "A pilha está vazia!";
  }
}

/*
    LAÇO DE IMPRESSÃO: TOPO -> FUNDO
        -> ponteiroTemporario: aponta para o TOPO, retorna o DADO
        -> ponteiroTemporario: recebe o ponteiro PROXIMO, aponta para o elemento ABAIXO
            -: imprime o DADO
            -: segue no loop até o FUNDO da pilha ("aponta para nada")
*/
void PilhaEncadeada::print() const {
    NodeType* ponteiroTemporario = estrutura; // início no TOPO

    while (ponteiroTemporario != NULL) {
        cout << ponteiroTemporario -> data; // imprime o dado
        ponteiroTemporario  = ponteiroTemporario -> proximo; // passa a apontar para o NÓ ABAIXO
    }  
    cout << endl;
}
