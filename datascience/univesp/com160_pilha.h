/*
COM160: Estruturas de Dados

Semana 2: As visões das estruturas de dados
    -> Pilha (Stack): vetor
        -: lógica (header): com160_pilha.h
        -: implementação: com160_estruturas_dados_semana2_b.cpp
        -: execução: com160_pilha_main.cpp

        -: ESTRUTURAÇÃO FEITA COMO VETOR
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
        -> POSIÇÃO NO TOPO da pilha, depende do número de elementos da pilha 
        -> UTILIDADES:
            -: garante o alinhamento de componentes em processos
            -: uso para chamada de funções em programas
            -: análise de sintaxe de linguagens de programação, devido aos "escopos"
        
*/


const int MAX_ITEMS = 100;

class Pilha {
    public:
        Pilha();   // !Construtor: alocação
        ~Pilha();   // !Destrutor: desalocação

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

