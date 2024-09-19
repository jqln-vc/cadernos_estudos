/*
    COM160: Estruturas de Dados

    Semana 4: Tabela Hash
        -> Tratamento de Colisões

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
-> TRATAMENTO DE COLISÕES
    -: As colisões são inevitáveis e precisam ser tratadas em uma tabela hash.
        L: ocorrem quando a função de espalhamento aponta 2 (ou mais) chaves para o mesmo endereço
            
    -: TIPOS:
        L: ENCADEAMENTO SEPARADO: cada endereço A[i] é um ponteiro para uma LISTA ENCADEADA
            que conterá todos os ELEMENTOS DE MESMO ÍNDICE (elementos que colidiram).
                L: ao colocar N elementos em M endereços, espera-se N/M entradas por endereço
                    L: FATOR DE CARGA (N/M): o ideal é que seja limitado por uma constante, idealmente menor que 1
                        L: significa que, para um boa função de hash, existirão sempre endereços vazios
                
        L: TESTE LINEAR: colisões serão tratadas sem alocação de memória adicional, será utilizado o próprio vetor
            L: ao colocar um item (k,v) em um endereço A[i] já ocupado com i=h(k), tenta-se em um novo endereço A[(i+1 mod M)]
                L: as tentativas continuam até que um endereço vazio seja encontrado
                L: problema de agrupamento: pesquisas podem se tornar lentas, devido à alocação em posições contíguas
            L: SOLUÇÕES DE AGRUPAMENTO:
                L: Teste Quadrático: testa em posições A[(i+f(j) mod M)] em que f(j) = j**2
                    L: evita o agrupamento sequencial mas cria novos padrões de agrupamento
                L: Hashing Duplo: utiliza uma nova função g(k) para tratar colisões
                    L: A[(i+f(j)) mod M] sendo que f(j) = j*g(k)
                    L: a função de hashing secundária g(k) não pode resultar em 0
                    
        
        
        ->> FUNÇÃO EXEMPLO 2: Tratando colisões a partir da função 1 com Teste Linear
            L: a função para OBTER o item deverá examinar endereços consecutivos
            L: a função DELETE não poderá mais remover os itens, pois cada item é um "indício" das possíveis colisões consecutivas
                L: a solução será substituir o item a ser removido por um MARCADOR "DISPONÍVEL" (-2)
                L: a função OBTER poderá utilizar os endereços "disponíveis" para inserir entradas


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
    IMPLEMENTAÇÃO TABELA HASH COM TRATAMENTO DE COLISÕES: TESTE LINEAR (LINEAR PROBING)

*/

// construtor
Hash::Hash(int max) {  
  tamanho = 0;
  max_items = max;
  estrutura = new Aluno[max_items];
}

Hash::~Hash(){
  delete [] estrutura;
}

bool Hash::cheia() const {
  return (tamanho == max_items);
}

int Hash::obterTamanho() const {
  return tamanho;
}


/*
    OBTER / RETRIEVEITEM
        -> localizacaoInicial: o índice retornado pela função de hash é o início da busca
            L: a busca é encerrada com RA -1, porém não com RA -2 (marcador de remoção de um agrupamento)


*/
void Hash::obterAluno(Aluno& aluno, bool& encontrado) {
  int localizacaoInicial = getHash(aluno); // início da busca
  bool continuarBusca = true; 
  int localizacao = localizacaoInicial;
  do {
    // caso o início da busca já seja o RA buscado ou seja um espaço vazio (-1), encerramos a busca
    if (estrutura[localizacao].getRa() == aluno.getRa() ||
	estrutura[localizacao].getRa() == -1)
      continuarBusca = false;

    // senão, continuamos a busca no próximo endereço (localizacao + 1)    
    // (localizacao + 1) % max_items: se o próximo endereço estiver fora do vetor, voltamos para o início
    else
      localizacao = (localizacao + 1) % max_items;

      // loop é encerrado quando "damos a volta" no vetor (localizacao == localizacaoInicial) ou continuarBusca é false
  } while (localizacao != localizacaoInicial && continuarBusca); 
  
  encontrado = (estrutura[localizacao].getRa() == aluno.getRa() );   
  if (encontrado) { 
    aluno = estrutura[localizacao];
  }
}

/*
    INSERIR / INSERTITEM
        -> Trata qualquer RA negativo como disponível
        -> Não trata o caso de a  estrutura estar cheia
*/
void Hash::inserirAluno(Aluno aluno) {
  int localizacao;
  localizacao = getHash(aluno);
  while (estrutura[localizacao].getRa() >= 0) // verifica se está disponível (RA < 0), senão continua procurando
    localizacao = (localizacao + 1) % max_items;
  estrutura[localizacao] = aluno;
  tamanho++;
}


/*
    REMOVER / DELETEITEM
        -> Mesma lógica de INSERIR
            L: marca elementos removidos com RA -2
                L: diferenciação dos espaços inicialmente vazios de RA -1
        
*/
void Hash::removerAluno(Aluno aluno) {
  int localizacaoInicial = getHash(aluno);
  bool continuarBusca = true; 
  int localizacao = localizacaoInicial;

  do {
    if (estrutura[localizacao].getRa() == aluno.getRa() ||
	estrutura[localizacao].getRa() == -1)
      continuarBusca = false;
    else
      localizacao = (localizacao + 1) % max_items;
  } while (localizacao != localizacaoInicial && continuarBusca);

  if (estrutura[localizacao].getRa() == aluno.getRa()) {       
    estrutura[localizacao] = Aluno(-2,""); // remove valor e coloca disponível após remoção (-2)
    tamanho--;
  }
}

void Hash::print() {
  for (int i = 0; i < max_items; i++) {
    cout << i << ":" << estrutura[i].getRa() << ", " << estrutura[i].getNome() <<endl;
  }
}

int Hash::getHash(Aluno aluno){
  return aluno.getRa() % max_items;
}

