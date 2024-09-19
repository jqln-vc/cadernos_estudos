/*
    COM160: Estruturas de Dados

    Semana 4: Tabela Hash

            -: lógica (header): 
                L: classe Aluno: com160_aluno.h
                L: classe Hash: com160_hash.h
            -: implementação: 
                L: sem tratamento de colisões: com160_estruturas_dados_semana4_a.cpp
                L: com tratamento de colisões: com160_estruturas_dados_semana4_b.cpp
            -: execução: com160_hash_main.cpp


            -: comando de compilação (certificar-se de estar no folder)
                g++ com160_hash_main.cpp com160_estruturas_dados_semana4_a.cpp -o hash
                g++ com160_hash_main.cpp com160_estruturas_dados_semana4_b.cpp -o hash
            -: execução após compilação
                .\hash
*/


#include "com160_aluno.h"

class Hash {
    public:
        Hash(int max_items = 100); // construtor
        ~Hash(); // destrutor
        bool cheia() const; // isFull()
        int obterTamanho() const; // getLength()
        
        void obterAluno(Aluno& aluno, bool& found); //retrieveItem()
        void inserirAluno(Aluno aluno); // insertItem()
        void removerAluno(Aluno aluno);  // deleteItem()
        void print();

        
      private:
        int getHash(Aluno aluno);
        int   max_items; // 
        int   tamanho; // length
        Aluno* estrutura; // structure: vetor de objetos Aluno
};
