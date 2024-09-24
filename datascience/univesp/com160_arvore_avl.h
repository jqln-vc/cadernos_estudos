/*
    COM160: Estruturas de Dados

    Semana 6: Árvores AVL e Grafos
      -> Árvore AVL
            -: lógica (header): 
                L: classe Aluno: com160_aluno.h
                L: classe Árvore AVL: com160_arvore_avl.h
            -: implementação: com160_estruturas_dados_semana6_a.cpp
            -: execução: com160_arvore_avl_main.cpp


            -: comando de compilação (certificar-se de estar no folder)
                g++ com160_arvore_avl_main.cpp com160_estruturas_dados_semana6_a.cpp -o arvore_avl
            -: execução após compilação
                .\arvore_avl
*/


#include <cstddef>
#include <iostream>
#include "com160_aluno.h"

/*
  Estrutura baseada na classe Aluno
    -> endereços de subárvores
    -> fator de balanceamento
 */
struct NodeType
{
    Aluno aluno;
    int      fatorBalanceamento;
    NodeType*    esquerda;
    NodeType*    direita;
};


class arvoreBuscaAVL {
    public:  
    arvoreBuscaAVL() { raiz = NULL; }    
    ~arvoreBuscaAVL(){ destruirArvore(raiz); }
    bool vazia() const;
    bool cheia() const;
    void obterAluno(Aluno& item, bool& found) const{ 
        obterAluno(raiz, item, found);
}
    void inserirAluno(Aluno item){
        bool maisAlta;
        inserirAluno(raiz, item, maisAlta);
}  
    void removerAluno(int item){
        bool maisBaixa;
        removerAluno(raiz, item, maisBaixa);
}
    
    void printPreOrdem() const { printPreOrdem(raiz); }
    void printInOrdem() const { printInOrdem(raiz);  }
    void printPosOrdem() const { printPosOrdem(raiz); }

    
    private:
    void destruirArvore(NodeType*& arvore); 
    void obterAluno(NodeType* arvore,
                Aluno& item,
                bool& found) const;
    void inserirAluno(NodeType*& arvore, Aluno item, bool& maisAlta);  
    void removerAluno(NodeType*& arvore, int item, bool& maisBaixa);
    void removerNo(NodeType*& arvore, bool& maisBaixa);
    void getSucessor(NodeType* arvore, Aluno& data);
    void printArvore(NodeType *arvore) const;    
    void printPreOrdem(NodeType* arvore)  const;
    void printInOrdem(NodeType* arvore)   const;
    void printPosOrdem(NodeType* arvore) const;

    void rotacaoEsquerda(NodeType*& arvore) const;
    void rotacaoDireita(NodeType*& arvore) const;  
    void rotacaoEsquerdaDireita(NodeType*& arvore) const;
    void rotacaoDireitaEsquerda(NodeType*& arvore) const;

    void rotacionar(NodeType*& arvore) const;

    // Nó raiz da árvore.
    NodeType* raiz;
};
