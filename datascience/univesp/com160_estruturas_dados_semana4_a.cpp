/*
    COM160: Estruturas de Dados

    Semana 4: Tabela Hash
        -> Estrutura da Tabela Hash
        
            -: lógica (header): 
                L: classe Aluno: com160_aluno.h
                L: classe Hash: com160_hash.h
            -: implementação: 
                L: sem tratamento de colisões: com160_estruturas_dados_semana4_a.cpp
                L: com tratamento de colisões: com160_estruturas_dados_semana4_b.cpp
            -: execução: com160_hash_main.cpp


            -: comando de compilação (certificar-se de estar no folder)
                g++ com160_hash_main.cpp com160_estruturas_dados_semana4_a.cpp -o hash
                g++ com160_hash_main.cpp com160_estruturas_dados_semana4_b.cpp -o hash_com_tratamento
            -: execução após compilação
                .\hash
                .\hash_com_tratamento
*/
/*
    TABELA HASH
        -> Sinônimos: dicionário, mapa, array associativo
        -> Busca EFICIENTE em tempo constante (mantidas algumas condições restritivas)
            L: A tabela será organizada em memória como um VETOR (ou array)
        -> Estrutura de dados que mapeia CHAVES para VALORES
            L: CHAVE: qualquer tipo, identificador único -> mapeia para um endereço de memória
            L: VALOR: inteiro, para efetuar a busca no vetor -> índice do vetor
        
        -> Função de Espalhamento: f(chave) -> endereço
            L: vetor tamanho N, para valores bem distribuídos em um intervalo entre 0 e N-1
                L: necessário minimizar ocorrência de COLISÕES (2 chaves diferentes mapeadas para o mesmo endereço)
        
            ->> FUNÇÃO EXEMPLO 1: sem tratamento de colisões
                -: Mapear a somatória de inteiros de uma string,
                    de acordo com o valor de cada caractere na tabela ASCII, ao valor de um índice de vetor
                -: Tempo constante K: sendo K o limite de caracteres aceitos na chave
                -: PROBLEMA: chaves com os mesmos caracteres resultariam em um mesmo valor inteiro!
                    L: SOLUÇÃO: parametrizar um PESO para a POSIÇÃO dos caracteres na string
                        L: C0.a**(k-1) + C1.a**(k-2) + C2.a**(k-3)... + Ck-2.a**(1) + Ck-1
                        L: para a != 0 | 1
                        L: valor de a ALTO (>33, primos) tende a diminuir o nº de colisões
                            L: valor MUITO ALTO pode levar a overflow de inteiros
                            L: pode-se fazer uma compressão: i % N (N sendo o tamanho do vetor)
                            L: quanto maior N, menor o nº de colisões
                            L: escolher um valor PRIMO para N (diminui denominadores comuns)
            
*/                  

#include "com160_hash.h"
#include <iostream>
using namespace std;

// IMPLEMENTAÇÃO CLASSE ALUNO

Aluno::Aluno() {
    this -> ra = -1; // indica uma posição "vazia" no vetor (pode ser qualquer valor nunca utilizado)
    this -> nome = "";
};  
Aluno::Aluno(int ra, std::string nome) {
    this -> ra = ra; // indíce do vetor
    this -> nome  = nome;
}
string Aluno::getNome() const {
     return nome;
}
int Aluno::getRa() const {
    return ra;
}

/*
    IMPLEMENTAÇÃO TABELA HASH
        -> Buscar o valor de NOME pela chave de RA, da classe Aluno
        -> Não trata colisões
*/

// construtor
Hash::Hash(int max) {  
    tamanho = 0;
    max_items = max; // tamanho máximo do vetor
    estrutura = new Aluno[max_items]; // inicializa o vetor com o tamanho máximo
}

// destrutor
Hash::~Hash() {
    delete [] estrutura; // desaloca o vetor de dados
}

bool Hash::cheia() const {
    return (tamanho == max_items);
}

int Hash::obterTamanho() const {
    return tamanho;
}

/*
    OBTENÇÃO DE VALOR (RETRIEVE)
        -> Obter o valor associado a uma chave
        -> Caso não exista, retorna nulo
        -> aluno e encontrado: passados por referência
            -: variável aluno será atualizada com o dado obtido
*/ 
void Hash::obterAluno(Aluno& aluno, bool& encontrado) { 
    int localizacao = getHash(aluno); // retorna o índice (int) para o vetor de dados do Aluno
    Aluno aux = estrutura[localizacao]; // retorna em aux o valor na estrutura

    if (aluno.getRa() != aux.getRa()) { // checar se RA que veio como parâmetro é igual ao RA da estrutura de dados
        encontrado = false;
    } else {
        encontrado = true;
        aluno = aux; // variável atualizada com o valor da estrutura
    }
}

/*
    INSERÇÃO DE VALOR (INSERT)
        -> Insere uma entrada V associado a uma chave K, caso não exista	
        -> Caso exista, atualiza o valor
*/ 
void Hash::inserirAluno(Aluno aluno) {
    int localizacao = getHash(aluno); // obtém o índice
    estrutura[localizacao] = aluno; // insere o Aluno no vetor de dados na posição obtida com getHash
    tamanho++; // incrementa o tamanho da tabela
}

/*
    REMOÇÃO DE VALOR (DELETE)
        -> Remove uma chave K e o valor V associado, caso exista
*/ 
void Hash::removerAluno(Aluno aluno) {
    int localizacao = getHash(aluno); 
    estrutura[localizacao] = Aluno(); // insere um Aluno "vazio" (RA == -1, nome == "")
    tamanho--; // decrementa o tamanho da tabela
}

// IMPRIME: valores no vetor/array
void Hash::print() {
  for (int i = 0; i < max_items; i++) {
    cout << i << ":" <<
      estrutura[i].getRa() << ", " <<
      estrutura[i].getNome() << endl;
  }
}

int Hash::getHash(Aluno aluno){

    /*
        -> RA: índice do vetor
        -> RA mod N: evita que o RA (índice do vetor) extrapole os limites do vetor
            L: calcula o resto da divisão, se RA < N, retorna o próprio RA
    */
    return aluno.getRa() % max_items;
}
