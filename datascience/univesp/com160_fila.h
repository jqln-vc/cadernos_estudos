/*
COM160: Estruturas de Dados

Semana 2: As visões das estruturas de dados
    -> Fila (Queue): vetor
        -: lógica (header): com160_fila.h
        -: implementação: com160_estruturas_dados_semana2_c.cpp
        -: execução: com160_fila_main.cpp

        -: ESTRUTURAÇÃO FEITA COMO VETOR

        !comando de compilação (certificar de estar no folder)
            ?g++ com160_fila_main.cpp com160_estruturas_dados_semana2_c.cpp -o fila
        !execução após compilação
            ?.\fila
*/


// só aceitará tipo "char"
const int MAX_ITEMS = 100;

class Fila {
    public :  
        Fila(); // construtor: alocação
        ~Fila(); // destrutor: desalocação
        
        bool vazia() const;
        bool cheia() const;
        void print() const;

        void inserir(char); // enqueue, enfileirar
        char remover();  // dequeue, desenfileirar
    
    private:
        int inicio; // primeiro a entrar/sair
        int final; // ultimo a entrar/sair
        char* estrutura;
};