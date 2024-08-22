/*
COM160: Estruturas de Dados

Semana 2: As visões das estruturas de dados
    -> Fila (fila): vetor
        -: lógica (header): com160_fila.h
        -: implementação: com160_estruturas_dados_semana2_c.cpp
        -: execução: com160_fila_main.cpp

        -: ESTRUTURAÇÃO FEITA COMO VETOR

        !comando de compilação (certificar de estar no folder)
            ?g++ com160_fila_main.cpp com160_estruturas_dados_semana2_c.cpp -o fila
        !execução após compilação
            ?.\fila
*/
/*
    FILA
        -> estrutra linear: somente um único PREDECESSOR e SUCESSOR
        -> INSERÇÃO e REMOÇÃO 
            -: estrutura de VETOR: TEMPO CONSTANTE
            -: Enfila / inserção: final da fila
            -: Defila / remoção: início da fila
        -> FIFO (First In First Out): primeiro a entrar, primeiro a sair
        -> LILO (Last In Last Out): último a entrar, último a sair
        -> UTILIDADES:
            -: comportamento análogo à comunicação de processos
*/

#include "com160_fila.h"
#include <iostream>
using namespace std;

int main() {
    char caractere;
    Fila fila;
    char itemFila;

    cout << "Adicione uma sequência de caracteres. Pressione ENTER para FINALIZAR e SAIR: " << endl;
    cin.get(caractere);
    while (caractere != '\n' and !fila.cheia())
        {
        fila.inserir(caractere);
        cin.get(caractere);
        }
    while (!fila.vazia())
        {
        itemFila = fila.remover();
        cout << itemFila;
        }
    cout << endl;
}
