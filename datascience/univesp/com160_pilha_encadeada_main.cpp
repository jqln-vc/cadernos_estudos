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



#include "com160_pilha_encadeada.h"
#include <iostream>
using namespace std;

/*
    TESTE DE ALINHAMENTO DE ESCOPO DE SINTAXE
        -> UTILIDADES DA PILHA:
            -: garante o alinhamento de componentes em processos
            -: uso para chamada de funções em programas
            -: análise de sintaxe de linguagens de programação, devido aos "escopos"
        
        -> EXEMPLOS DE TESTE:
            -: a{b[c]b}d  ->> bem pareada
            -: a{b[c]d  ->> mal pareada, o escopo de "b" não foi fechado
        
        -> EXPLICAÇÃO DO CÓDIGO:
            -: somente serão testados os delimitadores de escopo {} ou [] ou ()
            -: quaisquer outros caracteres serão ignorados
            -: sempre que um ESCOPO é ABERTO: { ou [ ou (
                L: é inserido na PILHA
            -: assim que um ESCOPO é FECHADO: } ou ] ou )
                L: verifica se está ALINHADO com o ÚLTIMO ESCOPO ABERTO (topo da pilha)
            -: cada novo caractere é verificado
            -: sintaxeAlinhada == FALSE
                L: caso um ESCOPO seja FECHADO, mas
                    L: não possua sua ABERTURA PAREADA na pilha
                    L: o próximo delimitador da pilha não seja correspondente
*/

int main() {
    ItemType caractere;
    PilhaEncadeada pilhaEncadeada;  
    ItemType itemPilhaEncadeada;
    
    cout << "Adicione uma sequência para teste de alinhamento de escopos de sintaxe. Pressione ENTER para FINALIZAR e SAIR: " << endl;
    cin.get(caractere);
    
    bool sintaxeAlinhada = true;  

    while (sintaxeAlinhada && caractere != '\n') {
        if (caractere == '{' || caractere== '(' || caractere==  '[') {  
            pilhaEncadeada.inserir(caractere);
        }

        if(caractere == '}' || caractere == ')' || caractere==  ']') {    
            if (pilhaEncadeada.vazia()) {
             sintaxeAlinhada = false;
            } else {
                itemPilhaEncadeada = pilhaEncadeada.remover();
                sintaxeAlinhada = (
                    (caractere == '}' && itemPilhaEncadeada == '{')
                    || (caractere == ')' && itemPilhaEncadeada == '(')
                    || (caractere == ']' && itemPilhaEncadeada == '[')
                );
            }
        }
        // continua recebendo caracteres na string
        cin.get(caractere);
    }
        

    if (sintaxeAlinhada && pilhaEncadeada.vazia()) {
        cout << "Sintaxe pareada e bem formada \n";
    } else {
        cout << "Sintaxe não pareada e mal formada \n";
    }
}

