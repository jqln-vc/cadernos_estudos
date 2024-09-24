/*
    COM160: Estruturas de Dados

    Semana 6: Árvores AVL e Grafos
      -> Grafos
            -: lógica (header): 
                L: classe Fila Encadeada: com160_fila_encadeada.h
                L: classe Vértice: com160_vertice.h
                L: classe Grafo: com160_grafo.h
                L: struct Vertice Nodetype: com160_grafo_nodetype.h
            -: implementação: com160_estruturas_dados_semana6_b.cpp
            -: execução: com160_grafo_main.cpp


            -: comando de compilação (certificar-se de estar no folder)
                g++ com160_grafo_main.cpp com160_estruturas_dados_semana6_b.cpp -o grafo
            -: execução após compilação
                .\grafo
*/
/*
    GRAFOS
        -> Grafo(Vertice,Aresta)
            -: Vertice = {v1, v2, v3...}
            -: Aresta = {a1, a2, a3...}: uma ARESTA é UM PAR DE VÉRTICES
                L: a1 = {v1, v2}
        -> Pode ser DIRECIONADO (arestas são pares ordenados) ou NÃO DIRECIONADO
        
        -> GRAU DO GRAFO
            -: NÃO DIRECIONADO: número de arestas que incidem nele
                L: self-loops não são considerados
            -: DIRECIONADO: número de arestas que saem do vértice (GRAU DE SAÍDA)
                somado ao número de arestas que chegam no vértice (GRAU DE ENTRADA)
                L: self-loops são considerados
        
        -> CAMINHO: sequência de vértices

        -> FORMAS DE REPRESENTAÇÃO
          -: MATRIZ de Adjcências: para um grafo com N vértices, temos uma matriz NxN
            L: A[i][j] = 1, se houver uma aresta indo do vértice i ao j
            L: A[i][j] = 0, caso contrário
            L: GRAFOS NÃO DIRECIONADOS POSSUEM MATRIZ SIMÉTRICA (não ocorre o mesmo em grafos direcionados)

                                          A B C D E
                                        A 0 1 0 1 0
                                        B 1 0 1 0 0
                                        C 0 1 0 1 1
                                        D 1 0 1 0 0
                                        E 0 0 1 0 0
            L: Para grafos ponderados, substituímos os 1s pelo PESO
            L: UTILIZAÇÃO:
              L: VANTAGENS: ocupam o mesmo espaço, tanto em grafos esparsos quanto densos
                            eficiente para verificar existência de aresta entre nós, dados seus índices
                            para encontrar os predecessores de um nó, só é preciso buscar a coluna do nó na matriz

              L: DESVANTAGENS: alocamos espaço para a matriz inteira no momento da declaração, antes de saber o # de vértices/arestas


          -: LISTAS de adjacências: um grafo com N vértices consiste de um arranjo de N listas encadeadas
            L: para cada vértice U, sua lista de adjacências contém todos os vizinhos de U
            L: adicionamos o valor do PESO na estrutura
            L: UTILIZAÇÃO:
              L: VANTAGENS: buscas são mais eficientes, pois já temos os adjacentes de cada nó

              L: DESVANTAGENS: se o grafo for muito denso (muitas arestas em relação aos vértices), ocupa muita memória
                               para encontrar os predecessores de um nó, é preciso varrer todas as listas



*/

#include <iostream>
#include <cstddef>         // Para NULL.
#include <new>             // Para bad_alloc.
#include "com160_fila_encadeada.h"  
#include "com160_grafo.h"
using namespace std;


// IMPLEMENTAÇÃO FILA ENCADEADA
std::ostream &operator<<(std::ostream &os, Vertice const &m) { 
  return os << m.getNome();
}

FilaEncadeada::FilaEncadeada() {
  inicio = NULL;
  final = NULL; 
}

FilaEncadeada::~FilaEncadeada() {
  NodeType* ponteiroTemporario;
  while (inicio != NULL) {
      ponteiroTemporario = inicio;
      inicio = inicio -> proximo;    
      delete ponteiroTemporario;
    }
  final = NULL;
}


bool FilaEncadeada::cheia() const {
  NodeType* testeAlocacao;
  try {
      testeAlocacao = new NodeType;
      delete testeAlocacao;
      return false;
  } catch(std::bad_alloc exception) {   
    return true;
  }
}

bool FilaEncadeada::vazia() const {
  return (inicio == NULL);
}

void FilaEncadeada::inserir(ItemType novoItem) {
  if (!cheia()) {
    NodeType* novoNo;
    novoNo = new NodeType;
    novoNo -> dado = novoItem;
    novoNo -> proximo = NULL;
    if (final == NULL)
      inicio = novoNo;
    else
      final -> proximo = novoNo;
    final = novoNo;
  } else {
    throw "FilaEncadeada já está cheia!";           
  }
}

ItemType FilaEncadeada::remover() {
  if (!vazia()) {
    NodeType* ponteiroTemporario;
    ponteiroTemporario = inicio;
    ItemType item = inicio -> dado;     
    inicio = inicio -> proximo;
    if (inicio == NULL)
      final = NULL;
    delete ponteiroTemporario;
    return item;
  } else {
    throw "FilaEncadeada está vazia!";
  }    
}

void FilaEncadeada::print() const {
  NodeType* ponteiroTemporario = inicio;
  while (ponteiroTemporario != NULL) {
      cout << ponteiroTemporario -> dado;
      ponteiroTemporario = ponteiroTemporario -> proximo;
    }
  cout << endl;
}


// IMPLEMENTAÇÃO GRAFO COM MATRIZ DE ADJACÊNCIAS

// CONSTRUTOR
Grafo::Grafo(int max, int null_aresta) {
  NULL_ARESTA = null_aresta; 
  maxVertices = max;  
  numVertices = 0;
  vertices = new Vertice[maxVertices];
  marcasVertices = new bool[maxVertices];
  adjacencias = new int* [maxVertices];
  
  // Criando matriz de adjacências
  for (int linha = 0; linha < maxVertices; linha++)
    adjacencias[linha] = new int[maxVertices];  // cada índice [linha] é um ponteiro para uma lista de tamanho N vértices

  // Populando matriz de adjacências com valor nulo     
  for (int linha = 0; linha < maxVertices; linha++)
    for (int coluna = 0; coluna < maxVertices; coluna++)
      adjacencias[linha][coluna] = NULL_ARESTA; 
}

// DESTRUTOR
Grafo::~Grafo() {
  delete [] vertices;
  delete [] marcasVertices;
  for (int linha = 0; linha < maxVertices; linha++){
    delete [] adjacencias[linha]; // desaloca linha por linha da matriz
  }
  delete [] adjacencias; // desaloca o vetor de ponteiros 
}


int Grafo::getIndex(Vertice Vertice) {
  int index = 0;
  // faz uma busca sequencial no array de vértices para obter o índice
  while (!(Vertice.getNome() == vertices[index].getNome())){
    index++; 
  }
  return index;
}


void Grafo::adicionarVertice(Vertice Vertice) {
  vertices[numVertices] = Vertice; // adiciona o vértice no último índice disponível
  numVertices++; 
}


void Grafo::adicionarAresta(Vertice verticeOrigem, Vertice verticeDestino, int peso) {
  int linha = getIndex(verticeOrigem);
  int coluna = getIndex(verticeDestino);

  adjacencias[linha][coluna] = peso;
  adjacencias[coluna][linha] = peso;  // Remover se for grafo direcionado
}


int Grafo::getPeso(Vertice verticeOrigem, Vertice verticeDestino) {
  int linha = getIndex(verticeOrigem);
  int coluna = getIndex(verticeDestino);
  return adjacencias[linha][coluna];
}

void Grafo::getAdjacencias(Vertice Vertice, FilaEncadeada &verticesAdjacentes) {
  int indexDestino;
  int indexOrigem;

  indexOrigem = getIndex(Vertice); // inicia no vértice origem

  // percorre a linha corresponde ao vértice de origem
  // verifica se existem valores não nulos na coluna (indicando uma aresta)
  for (indexDestino = 0; indexDestino < numVertices; indexDestino++)
    if (adjacencias[indexOrigem][indexDestino] != NULL_ARESTA)
      
      // Uma cópia do elemento adjacente é adicionada no array de vérticesAdjacentes
      verticesAdjacentes.inserir(vertices[indexDestino]);
}

void Grafo::limparMarcasVertices() {
  for (int i = 0; i < numVertices; i++)
    marcasVertices[i] = false;    
}

// marca vértices visitados: úteis em algoritmos de busca
void Grafo::marcarVertice(Vertice Vertice) {
  int index = getIndex(Vertice);
  marcasVertices[index] = true;
}

bool Grafo::marcado(Vertice Vertice) {
  int index = getIndex(Vertice);
  return marcasVertices[index];  
}

void Grafo::printMatriz() {
  for (int i = 0; i < numVertices; i++) {
    for (int j = 0; j < numVertices; j++) {
      std::cout << adjacencias[i][j] << ",";
    }
    std::cout << std::endl;
  }
}