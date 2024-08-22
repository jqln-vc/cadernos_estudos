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
/*
    FILA
        -> estrutra linear: somente um único PREDECESSOR e SUCESSOR
        -> INSERÇÃO e REMOÇÃO 
            -: estrutura de VETOR: TEMPO CONSTANTE
            -: Enqueue / inserção: final da fila
            -: Dequeue / remoção: início da fila
        -> FIFO (First In First Out): primeiro a entrar, primeiro a sair
        -> LILO (Last In Last Out): último a entrar, último a sair
        -> UTILIDADES:
            -: comportamento análogo à comunicação de processos
*/

/*
    VISÃO LÓGICA: com160_fila.h
    -:  só aceitará tipo "char"
-------------------------------------------    

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
*/

// IMPLEMENTAÇÃO

#include "com160_fila.h"
#include <iostream>
using namespace std;

// construtor: alocação
Fila::Fila() {
  inicio = 0;
  final  = 0;
  estrutura = new char[MAX_ITEMS];
}

// destrutor: desalocação
Fila::~Fila() {
  delete [] estrutura;
}

// método vazia()
bool Fila::vazia() const {
  return (inicio == final);
}

// método cheia()
bool Fila::cheia() const {
  return (final - inicio == MAX_ITEMS);
}

// método inserir(): enqueue
void Fila::inserir(char item) {
  if (!cheia()){
    estrutura[final % MAX_ITEMS] = item;
    final++;
  } else {
    throw "A fila já está cheia!";
  }
}

char Fila::remover()
{
  if (!vazia()){
    inicio++;
    /*
        MÓDULO i % MAX_ITEMS: 
            -: lidar com FILA CIRCULAR, garantindo que o índice permaneça dentro dos limites da estrutura  e volte ao início quando necessário
            (ex. quando i == MAX_ITEMS, o módulo será 0)
            -: operação MÓDULO retorna o próprio número quando ele é menor que o divisor
    */
    return estrutura[(inicio-1) % MAX_ITEMS];
  } else {
    throw "A fila está vazia!";
  }
}

void Fila::print() const
{
  cout << "Fila = ";
  for (int i = inicio; i < final; i++) {
    /*
        MÓDULO i % MAX_ITEMS: 
            -: lidar com FILA CIRCULAR, garantindo que o índice permaneça dentro dos limites da estrutura  e volte ao início quando necessário
            (ex. quando i == MAX_ITEMS, o módulo será 0)
            -: operação MÓDULO retorna o próprio número quando ele é menor que o divisor
    */
    cout << estrutura[i % MAX_ITEMS];
  }
  cout << endl;
}
