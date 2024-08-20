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

int main() {
  char caractere;
  Pilha pilha;
  char itemPilha;
  
  cout << "Adicione uma sequência de caracteres. Pressione ENTER para FINALIZAR e SAIR: " << endl;     
  cin.get(caractere);
  while (caractere != '\n')
    {
      pilha.inserir(caractere);
      cin.get(caractere);
    }
  
  // !remove os itens da pilha um a um
        // ?o texto digitado aparecerá ao contrário
        
  while (!pilha.vazia())
    {
      itemPilha = pilha.remover();
      cout << itemPilha;
    }
  
  cout << endl;
}
