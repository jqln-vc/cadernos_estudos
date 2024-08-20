/*
COM160: Estruturas de Dados

Semana 2: As visões das estruturas de dados
    -> Classes
        -: lógica (header): com160_tempo.h
        -: implementação: com160_estruturas_dados_semana2_a.cpp
        -: execução: com160_tempo_main.cpp

        !comando de compilação (certificar de estar no folder)
            ?g++ com160_tempo_main.cpp com160_estruturas_dados_semana2_a.cpp -o tempo
        !execução após compilação
            ?.\tempo
*/
/*
    HEADER
        -> visão lógica da classe Tempo
            -: definição de MEMBROS PÚBLICOS e PRIVADOS
            -: a implementação da classe (.cpp) importa este arquivo com a diretiva include
*/
/*
    CLASSE TEMPO
        -> modela instância de tempo
        -> 3 ATRIBUTOS (hora, minuto e segundo)
        -> CONSTRUTOR público: inicializa atributos
        -> métodos GET e SET: gerenciamento de atributos
        -> método público "print": imprimir no formato hh:mm:ss
        -> método púlico para adicionar 1 segundo

    DIRETIVAS
        -> evitar definições repetidas de classes entre imports

        #ifndef CLASSE ->> inclui esse bloco somente se CLASSE não está definida (caso sim, será pulado)
        #define CLASSE ->> na 1ª inclusão, define CLASSE para evitar dupla inclusão

            **código**
        #endif         ->> final do bloco "ifndef" 
*/

#ifndef TEMPO_H
#define TEMPO_H

class Tempo {
    private: //SEÇÃO PRIVADA
    
        //MEMBROS PRIVADOS
        int hora;       //0 - 23
        int minuto;     //0 - 59
        int segundo;    //0 - 59

    public: //SEÇÃO PÚBLICA
        //construtor
        Tempo(int hora = 0, int minuto = 0, int segundo = 0);
        
        //getters
        int getHora() const;
        int getMinuto() const;
        int getSegundo() const;

        //setters
        void setHora(int hora);
        void setMinuto(int minuto);
        void setSegundo(int segundo);

        void print() const;
        void adicionaSegundo();
};

#endif
