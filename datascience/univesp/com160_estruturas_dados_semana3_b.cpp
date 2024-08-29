/*
    COM160: Estruturas de Dados

    Semana 3: Organização dos Dados na Memória (contíguo ou disperso)
        -> Fila (Queue): lista encadeada
            -: lógica (header): com160_fila_encadeada.h
                L: node type (header/struct): com160_lista_encadeada_nodetype.h
            -: implementação: com160_estrutura_dados_semana3_b.cpp
            -: execução: com160_fila_encadeada_main.cpp


            !comando de compilação (certificar de estar no folder)
                g++ com160_fila_encadeada_main.cpp com160_estrutura_dados_semana3_b.cpp -o fila_encadeada
            !execução após compilação
                .\fila_encadeada
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
        -> VANTAGENS:
            -: ACESSO TEMPO CONSTANTE, a qualquer elemento, dado seu índice
            -: permite uso de BUSCA BINÁRIA
            L: O(log n)
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
        -> DESVANTAGENS:
            -: para ACESSAR UM ELEMENTO é preciso percorrer TODOS SEUS PREDECESSORES (NÃO TEM ACESSO EM TEMPO CONSTANTE)
            -: BUSCA BINÁRIA já não faz sentido
        -> VANTAGENS:
            -: número de elementos pode AUMENTAR ou DIMINUIR durante a EXECUÇÃO (desvantagem da lista sequencial)
                L: não é preciso deslocamento, só incluir/excluir um elemento
                    e mudar seus PONTEIROS para os NOVOS PREDECESSOR e SUCESSOR
            -: INSERÇÃO e REMOÇÃO em TEMPO CONSTANTE (isto é, independe do número de elementos na estrutura)
            -: MANUTENÇÃO DA ORDEM LÓGICA não exige deslocamento de elementos


    
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
    IMPLEMENTAÇÃO FILA ENCADEADA
*/ 

#include "com160_fila_encadeada.h"
#include <cstddef> // Para funcionar o NULL
#include <new>
#include <iostream>
using namespace std;

// construtor
FilaEncadeada::FilaEncadeada() {
    // a estrutura será inicializada sem apontar para nenhum local
    // NULL auxilia para estabelecer as paradas de laços
    inicio = NULL;
    final = NULL;
}

/*
    destrutor
        -> a variável "inicio" é o TOPO da PILHA ENCADEADA
        -> não podemos excluir "inicio" sem antes excluir todos os nós encadeados
        -> ponteiroTemporário: recebe "inicio", ou seja, o valor do NÓ e do PONTEIRO do próximo elemento, na base da pilha
            -: este ponteiro será apagado
        -> inicio: passa a receber o NÓ, valor e ponteiro, de "proximo" (elemento abaixo)
        -> repete-se até que todos os NÓS da PILHA ENCADEADA sejam deletados
 */ 
FilaEncadeada::~FilaEncadeada() {
    NodeType* ponteiroTemporario;
    while (inicio != NULL) {
        ponteiroTemporario = inicio;
        inicio = inicio -> proximo; // o operador -> acessa a variável "proximo" do ponteiro NodeType*
        delete ponteiroTemporario;
    }
    // ao final do laço, o INÍCIO está NULL (último ponteiroTemporario já deletado)
    // e o final, estará apontando para um NÓ já desalocado/deletado, logo será definido como NULL
    final = NULL;
}

// método vazia()
bool FilaEncadeada::vazia() const {
    return (inicio == NULL); // não tem nenhum dado, nem aponta para lugar nenhum
}

/*
    método cheia()
        -> será realizado um teste de alocação de novo elemento
        -> caso seja possível (memória disponível), o elemento temporário será deletado
            -: retorna Falso
        -> caso esteja cheia, o erro "bad_alloc" será pego no catch
            -: retorna True
*/
bool FilaEncadeada::cheia() const {
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
    -> não muda o ponteiro INÍCIO
    -> FINAL: sempre aponta para NULL
*/
void FilaEncadeada::inserir(ItemType novoDado){
    if (!cheia()){
        NodeType* novaAlocacao; // NÓ TOPO
        novaAlocacao = new NodeType; // aloca um NOVO NÓ em qualquer lugar da memória
        novaAlocacao -> data = novoDado; // o NOVO NÓ recebe o dado
        novaAlocacao -> proximo = NULL; // o NOVO NÓ vai para o FINAL da fila, não aponta para lugar nenhum
        
        if (final == NULL) { // verifica se "existe" uma fila
            inicio = novaAlocacao; // se não, começa nova fila com a novaAlocacao no INÍCIO
        } else { // se sim, o FINAL da fila aponta para a novaALocacao
            final -> proximo = novaAlocacao;
        }
        final = novaAlocacao;
    } else {
        throw "A fila já está cheia!";
    }
}

/*
  REMOÇÃO: método remover()
    -> retorna o NÓ do INÍCIO DA FILA
 */
ItemType FilaEncadeada::remover(){
    if (!vazia()) {
        NodeType* ponteiroTemporario;
        ponteiroTemporario = inicio;

        ItemType dadoInicio = inicio -> data;
        inicio = inicio -> proximo; // INÍCIO aponta para o próximo NÓ da FILA

        // caso seja o último NÓ da fila, ajustamos o FINAL para apontar para NULL também
        if (inicio == NULL) {
            final = NULL;
        }

        delete ponteiroTemporario;
        return dadoInicio; // retorna o NÓ do INÍCIO
    } else {
        throw "A fila está vazia!";
    }
}

/*
    LAÇO DE IMPRESSÃO: INÍCIO -> FINAL
        -> ponteiroTemporario: aponta para o INÍCIO
            -: enquanto não for NULL (fila vazia), retorna o DADO
            -: aponta para o próximo NÓ da fila
*/
void FilaEncadeada::print() const {
    NodeType* ponteiroTemporario = inicio; // início no TOPO

    while (ponteiroTemporario != NULL) {
        cout << ponteiroTemporario -> data; // imprime o dado
        ponteiroTemporario  = ponteiroTemporario -> proximo; // passa a apontar para o NÓ seguinte na fila
    }  
    cout << endl;
}
