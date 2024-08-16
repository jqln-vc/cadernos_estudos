/*
COM160: Estruturas de Dados

Semana 1: Introdução ao C++
    -> ponteiros
    -> vetores
    -> passagem de parâmetros
*/

/*
PONTEIROS: endereço de memória
    -> localização na memória do 1° byte ocupado por ela
    -> operador &: permite obter o endereço de memória da variável
    -> alocação dinâmica: programa aloca e libera memória em tempo de execução
    -> operadores new e delete: alocação e desalocação de memória
    -> alocação dinâmica: variáveis residem em local diverso das alocadas estaticamente
    -> operador *: retorna o conteúdo da variável localizada no endereço


VETORES: 
    -> estrutura conjunto de dados, tamanho fixado na declaração
    -> elementos devem ser do mesmo tipo
    -> elementos ocupam regiões consecutivas de memória
    -> valores não inicializados serão preenchidos com 0
    -> alocação dinâmica: 
        -: tamanho do vetor não muda após a declaração
        -: usar operador new e delete
    -> o vetor é um ponteiro
*/

#include <iostream>
#include <cstddef>
using namespace std;

 /*
    valorAlocandoMemoria(int* ponteiro)
        -> não altera o valor da variável fora da função
        -> não modifica o endereço da variável fora da função
        -> explicação: o parâmetro foi passado por valor
    */
    void valorAlocandoMemoria(int* ponteiro){
        ponteiro = new int;
        *ponteiro = 7;
    }

    /*
    valorModificandoMemoria(int* ponteiro)
        -> altera o valor da variável fora da função
        -> explicação: o parâmetro foi passado por valor,
         mas com o operador * foi modificado o endereço de memória para onde o ponteiro aponta
            -: tanto b quanto p2 apontavam para o mesmo endereço
        
    */
    void valorModificandoMemoria(int* ponteiro){
        *ponteiro = 8;
    }

    /*
    referencia(int*& ponteiro)
        -> altera o endereço pois o parâmetro foi passado por referência
        -> explicação: a variável c não foi afetada, pois continua
        usando o endereço antigo
            -: o valor apontado por p3 é diferente de c
        
    */
    void referencia(int*& ponteiro){
        ponteiro = new int;
        *ponteiro = 9;
    }

    // Ao tentar modificar um valor com parâmetro passado com CONST
    //  valorModificandoMemoria(p1);
    // ->> error: assignment of read-only location '* ponteiro' 
    /*
        void valorModificandoMemoria(const int* ponteiro){
            *ponteiro = 11;
        }
    */

int main(){

    //declarando variáveis
    int* ponteiroA;
    int* ponteiroB;
    int inteiroNumero;
    //bool* verdade = NULL;
    //float* dinheiro = NULL;

    //inicializando ponteiro
    ponteiroA = &inteiroNumero; // alocação estática
    ponteiroB = new int; // alocação dinâmica

    //declarando vetores
    const int NUM_ELEM = 10; //especificando tamanho padrão de vetor com constante
    int vetorA[NUM_ELEM];
    int vetorB[3] = {0, 1, 2}; // declarando e inicializando
    int vetorC[] = {4, 5, 6}; // neste caso, o vetor terá o tamanho da lista

    cout << vetorC << endl;
    cout << vetorB[0] << endl;

    //iterando vetor com FOR
    for (int i = 0; i < 3; i++){
        cout << "vetorB[" << i << "] = " << vetorB[i] << "\n";
    }

    //inicializando vetor com laço de repetição
    for (int i = 0; i < 10; i++){
        vetorA[i] = 2 * i;
        cout << "vetorA[" << i << "] = " << vetorA[i] << "\n";
    }

    // ALOCAÇÃO DINÂMICA
    int* vetorD = new int[NUM_ELEM]; // constante 10 elementos
    vetorD[0] = 1;
    
    for (int i = 2; i < NUM_ELEM; i = i + 2){
        vetorD[i] = 1 * i;
    }

    for (int i = 0; i < NUM_ELEM; i++){
        cout << vetorD[i] << endl;
    }

    //desalocação
    delete [] vetorD;
    
    //PONTEIROS COMO PARÂMETROS
       
    int a = 1;
    int b = 2;
    int c = 3;
    int* p1 = &a;
    int* p2 = &b;
    int* p3 = &c;

    cout << "ANTES" << endl;
    cout << "p1: " << p1 << " | p2: " << p2 << " | p3: " << p3 << endl;
    cout << "*p1: " << *p1 << " | *p2: " << *p2 << " | *p3: " << *p3 << endl;
    cout << "a: " << a << " | b: " << b << " | c: " << c << endl;
    cout << endl;

    valorAlocandoMemoria(p1);
    valorModificandoMemoria(p2);
    referencia(p3);

    cout << "DEPOIS" << endl;
    cout << "p1: " << p1 << " | p2: " << p2 << " | p3: " << p3 << endl;
    cout << "*p1: " << *p1 << " | *p2: " << *p2 << " | *p3: " << *p3 << endl;
    cout << "a: " << a << " | b: " << b << " | c: " << c << endl;
    cout << endl;

    cout << "ANTES DA FUNÇÃO COM CONST" << endl;
    cout << "p1: " << p1 << " | p2: " << p2 << " | p3: " << p3 << endl;
    cout << "*p1: " << *p1 << " | *p2: " << *p2 << " | *p3: " << *p3 << endl;
    cout << "a: " << a << " | b: " << b << " | c: " << c << endl;
    cout << endl;

    


return 0;
}