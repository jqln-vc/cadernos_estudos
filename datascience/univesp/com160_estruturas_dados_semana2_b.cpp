/*
COM160: Estruturas de Dados

Semana 2: As visões das estruturas de dados
    -> Pilha (Pilha)
        -: lógica (header): com160_pilha.h
        -: implementação: com160_estruturas_dados_semana2_b.cpp
        -: execução: com160_pilha_main.cpp

        !comando de compilação (certificar de estar no folder)
            ?g++ com160_pilha_main.cpp com160_estruturas_dados_semana2_b.cpp -o pilha
        !execução após compilação
            ?.\pilha
*/
/*
    PILHA
        -> estrutra linear: somente um único PREDECESSOR e SUCESSOR
        -> INSERÇÃO e REMOÇÃO ocorrem no topo da pilha
            -: PUSH: inserção
            -: POP: remoção
            -: sempre verificar se CHEIA ou VAZIA
        -> FILO: primeiro a entrar, último a sair
        -> LIFO: último a entrar, primeiro a sair
        
*/

/*
    !VISÃO LÓGICA: com160_pilha.h
const int MAX_ITEMS = 100;

class Pilha {
    public:
        Pilha();   // !Construtor
        ~Pilha();   // !Destrutor

        bool vazia() const; // !isEmpty
        bool cheia() const; // !isFull
        void print() const; // !visualização padrão (index 0-n)
        void print_order() const; // !visualização na ordem de saída
  
  void inserir(char); // !push
  char remover();    // !pop
    private:
        int tamanho; // !length
        char* estrutura; // !structure
};
*/

#include "com160_pilha.h"
#include <iostream>
using namespace std;

// !IMPLEMENTAÇÃO

// !construtor
Pilha::Pilha() {
  tamanho = 0;
  estrutura = new char[MAX_ITEMS];
}

// ! destrutor: desalocar
Pilha::~Pilha() {
  delete [] estrutura;
}

// !verificar se está vazia
bool  Pilha::vazia() const {
  return (tamanho == 0);
}

// !verificar se está cheia
bool Pilha::cheia() const {
  return (tamanho == MAX_ITEMS);
}

// !inserção // PUSH
void Pilha::inserir(char item) {
  if (!cheia()){
    estrutura[tamanho] = item;
    tamanho++;
  } else {
    throw "A pilha já está cheia!";
  }
}

// !remoção // POP
char Pilha::remover() {
  if (!vazia()){
    char removido = estrutura[tamanho - 1];
    tamanho--;
    return removido;
  } else {
    throw "A pilha está vazia!";
  }
}

// !visualização padrão (index 0-n)
void Pilha::print() const {
  cout << "Pilha ordem 0 a n  = ";
  for (int i = 0; i < tamanho; i++) {
    cout << estrutura[i];
  }
  cout << endl;
}

// !visualização na ordem de saída
void Pilha::print_order() const {
  cout << "Pilha na ordem de saída = ";
  for (int i = tamanho-1; i < tamanho; i--) {
    cout << estrutura[i];
  }
  cout << endl;
}
