/*
COM160: Estruturas de Dados

Semana 2: As visões das estruturas de dados
    -> Classes
        -: lógica (header): com160_tempo.h
        -: implementação: univesp_com160_estruturas_dados_semana2_a.cpp
        -: execução: com160_tempo_main.cpp

        -: comando de compilação (certificar de estar no folder)
            g++ com160_tempo_main.cpp univesp_com160_estruturas_dados_semana2_a.cpp -o tempo
        -: execução após compilação
            .\tempo
*/
/*
    CLASSE
        -> encapsulamento de atributos estáticos e comportamentos dinâmicos
        -> modelo para criação de OBJETOS (ou INSTÂNCIAS)
        -> isolamento entre:
            -: visão lógica | visão de implementação | visão de aplicação
        -> visão lógica: criada em arquivo de extensão (.h)
            -: definição de MEMBROS PÚBLICOS e PRIVADOS
            -: a implementação da classe (.cpp) importa este arquivo com a diretiva include


    DIRETIVAS
        -> evitar definições repetidas de classes entre imports

        #ifndef CLASSE ->> inclui esse bloco somente se CLASSE não está definida (caso sim, será pulado)
        #define CLASSE ->> na 1ª inclusão, define CLASSE para evitar dupla inclusão

            ?definição da classe

        #endif         ->> final do bloco "ifndef" 

*/

#include <iostream>
#include "com160_tempo.h" //import da classe Tempo
using namespace std;


/*
    CLASSE TEMPO
        -> modela instância de tempo
        -> 3 ATRIBUTOS (hora, minuto e segundo)
        -> CONSTRUTOR público: inicializa atributos
        -> métodos GET e SET: gerenciamento de atributos
        -> método público PRINT: imprimir no formato hh:mm:ss
        -> método púlico para adicionar 1 segundo

        class Tempo {
            private: 
            
                !MEMBROS PRIVADOS
                int hora;       //0 - 23
                int minuto;     //0 - 59
                int segundo;    //0 - 59

            public: 
                !construtor
                Tempo(int hora = 0, int minuto = 0, int segundo = 0);
                
                !getters
                int getHora() const;
                int getMinuto() const;
                int getSegundo() const;

                !setters
                void setHora(int hora);
                void setMinuto(int minuto);
                void setSegundo(int segundo);

                !outros métodos
                void print() const;
                void adicionaSegundo();
        };

*/

/* 
    IMPLEMENTAÇÃO DOS MÉTODOS
        -> operador de resolução de escopo ::
        -> forma de alternativa inicialização de atributos separados por ":"
            ?atributo1(parâmetroA), atributo2(parâmetroB), ..., atributoN(parâmetroM)

*/

// construtor
Tempo::Tempo(int h, int m, int s) : hora(h), minuto(m), segundo(s) {
  /*
    O corpo do método executa após as inicializações. 
    Neste caso, está vazio pois só as inicializações são necessárias.
   */
}

// getters
int Tempo::getHora() const {
    return hora;
}
int Tempo::getMinuto() const {
    return minuto;
} 
int Tempo::getSegundo() const {
    return segundo;
}

// setters
void Tempo::setHora(int hora) {
    this->hora = hora;
}
void Tempo::setMinuto(int minuto) {
    this->minuto = minuto;
}
void Tempo::setSegundo(int segundo) {
    this->segundo = segundo;
}

// método print
void Tempo::print() const {
    cout << hora << ":" << minuto << ":" << segundo << endl;
}

// método adicionaSegundo
void Tempo::adicionaSegundo() {
    segundo += 1;

    if (segundo == 60) {
        segundo = 0;
        minuto += 1;
    }
    if (minuto == 60) {
        minuto = 0;
        hora +=1;
    }
    if (hora == 24) {
        hora = 0;
    }
}

