/*
    COM160: Estruturas de Dados

    Semana 5: Árvores Binárias de Busca
        -> 
            -: lógica (header): 
                L: classe Aluno: com160_aluno.h
                L: struct No: com160_arvore_busca.h
                L: classe ArvoreBusca: com160_arvore_busca.h
                
            -: implementação: 
                L: classe Aluno: com160_estruturas_dados_semana5.cpp
                L: árvore de busca: com160_estruturas_dados_semana5.cpp
            -: execução: com160_arvore_busca_main.cpp


            !comando de compilação (certificar de estar no folder)
                g++ com160_estruturas_dados_semana5.cpp com160_arvore_busca_main.cpp -o arvore_busca
            !execução após compilação
                .\arvore_busca
*/
/*
    ÁRVORE
        -> Conjunto de NÓS:
            -: NÓ RAIZ (r)
            -: 0 ou + SUBÁRVORES cujas raízes são ligadas diretamente ao NÓ RAÍZ (r)
                L: uma SUBÁRVORE é uma ÁRVORE
            -: GRAU DO NÓ: n° de subárvores desse nó
            -: NÓ FOLHA: nó de grau 0
            -: NÓ INTERNO: nó de grau maior que 0
            -: DESCENDENTES: nós abaixo de um determinado nó
            -: ALTURA DE UM NÓ: comprimento do caminho MAIS LONGO indo do nó até uma folha
            -: ALTURA DA ÁRVORE: altura do nó raíz
            -: PROFUNDIDADE/NÍVEL DE UM NÓ: distância percorrida da raíz até o nó
            -: ÁRVORE BINÁRIA: árvore em que abaixo de cada nó existem no máximo 2 subárvores
                L: todos seus nós possuem grau 0, 1 ou 2

        -> NÃO É UMA ESTRUTURA LINEAR, ou seja, não há no máximo um predecessor/sucessor por nó
            -: Adequada para REPRESENTAÇÃO DE HIERARQUIA

    ÁRVORE BINÁRIA DE BUSCA
        -> Árvore binária em que para TODO NÓ:
            -: SUBÁRVORE ESQUERDA: registros com chaves menores
            -: SUBÁRVORE DIREITA: registros com chaves maiores  
        
        -> INSERÇÕES, REMOÇÕES E BUSCA: nº de comparações proporcional à ALTURA DA ÁRVORE
            -: REMOÇÃO POR SUCESSOR LÓGICO: elemento mais à ESQUERDA, na SUBÁRVORE DIREITA
                L: substituir o valor do nó removido por seu sucessor lógico, remover o sucessor lógico (já copiado)
            -: REMOÇÃO POR PREDECESSOR LÓGICO: elemento mais à DIREIRA, na SUBÁRVORE ESQUERDA
                L: substituir o valor do nó removido por seu predecessor lógico, remover o predecessor lógico (já copiado)

    PERCURSOS: percorrer os nós de maneira sistemática
        -> Sempre percorremos a SUBÁRVORE ESQUERDA ANTES da DIREITA, partindo da RAÍZ (nó raíz ou raíz das subárvores)
            -: PRÉ-ORDEM: nó raíz ->> nós da esquerda ->> nós da direita
            -: IN-ORDEM: nós da esquerda ->> nó raíz ->> nós da direita
                L: se iniciará em nó folha ("mais à esquerda")
                L: nesse percurso, os valores saem "ordenados"
            -: PÓS-ORDEM: nós da esquerda ->> nós da direita ->> nó raíz
                L: se iniciará em nó folha ("mais à esquerda")

    APLICAÇÕES DE ÁRVORES BINÁRIAS DE BUSCA
        -> estruturas fundamentais para construir outras estruturas
        -> organização de dados por meio de CHAVE usada nas buscas
        -> quando INSERÇÃO e REMOÇÃO são FREQUENTES, melhor que vetores/arrays ordenados
            -: pois, embora ambos sejam O(log n), para manter um vetor ordenado são necessários muitos deslocamentos
        

*/  

#include <iostream>
#include "com160_arvore_busca.h"
using namespace std;

// IMPLEMENTAÇÃO CLASSE ALUNO
Aluno::Aluno() {
    this->ra = -1;
    this->nome = "";
};  
Aluno::Aluno(int ra, std::string nome) {
    this->ra = ra;
    this->nome = nome;
}
string Aluno::getNome() const {
    return nome;
}
int Aluno::getRa() const {
    return ra;
}


/*
    IMPLEMENTAÇÃO ÁRVORE BINÁRIA
        -> organização e busca de alunos pelo RA
            -: valor de interesse: nome
        -> interface pública RECURSIVA, invocando métodos PRIVADOS (com acesso à RAÍZ)

*/

// Destrutor: percurso pós-ordem para apagar a árvore, desalocando nó por nó
void ArvoreBusca::deletarArvore(EstruturaNo*& arvore) {
    if (arvore != NULL) {
        deletarArvore(arvore -> esquerda);
        deletarArvore(arvore -> direita);
        delete arvore;
    }
}

bool ArvoreBusca::vazia() const {
    return raiz == NULL;
}

bool ArvoreBusca::cheia() const {
    EstruturaNo* testeAlocacao;
    try {
        testeAlocacao = new EstruturaNo;
        delete testeAlocacao;
        return false;
    } catch(const std::bad_alloc& exception) {
        return true;
    }
}

void ArvoreBusca::obterAluno(EstruturaNo* arvore, Aluno& alunoBuscado, bool& encontrado) const {
    if (arvore == NULL)
        encontrado = false;
    // se RA menor que o RA do nó atual, chamada recursiva a partir do nó predecessor (esquerda)
    else if (alunoBuscado.getRa() < arvore -> aluno.getRa()) 
        obterAluno(arvore -> esquerda, alunoBuscado, encontrado);
    
    // se RA maior que o RA do nó atual, chamada recursiva a partir do nó sucessor (direita)
    else if (alunoBuscado.getRa() > arvore -> aluno.getRa()) 
        obterAluno(arvore -> direita, alunoBuscado, encontrado);
   
    else {
        alunoBuscado = arvore -> aluno; // valor é passado por referência para variável alunoBuscado
        encontrado = true;
    }
}

/* 
    Método INSERÇÃO (não assume casos de valores repetidos)
*/
void ArvoreBusca::inserirAluno(EstruturaNo*& arvore, Aluno novoAluno)
{
    if (arvore == NULL) { // verificar se nó atual está vazio, ou não possui filhos / subárvores, ou é um nó folha
        arvore = new EstruturaNo;
        arvore -> direita  = NULL; // iniciado sem sucessor
        arvore -> esquerda = NULL; // iniciado sem predecessor
        arvore -> aluno = novoAluno;
    }
    else if (novoAluno.getRa() < arvore -> aluno.getRa())
        inserirAluno(arvore -> esquerda, novoAluno);
    else
        inserirAluno(arvore -> direita, novoAluno);
}

/*
    REMOÇÃO ALUNO:
        -> Navega pela árvore até achar o aluno (int ra) a ser excluído
        -> Ao encontrar, invoca a função removerNó
*/
void ArvoreBusca::removerAluno(EstruturaNo*& arvore, int alunoRemovido) {
    if (alunoRemovido < arvore -> aluno.getRa())
        removerAluno(arvore -> esquerda, alunoRemovido);
    else if (alunoRemovido > arvore -> aluno.getRa() )
        removerAluno(arvore -> direita, alunoRemovido); 
    else if (alunoRemovido == arvore -> aluno.getRa())
        removerNo(arvore);
}

/*
    REMOÇÃO NÓ
        -> Invocada pela função removerAluno
            -: recebe o nó a ser excluído
        -> Trata 3 casos:
            -: 1. Nó é uma folha
            -: 2. Nó tem um filho
            -: 3. Nó tem 2 filhos
                L: valor do nó excluído será substituído pelo sucessor lógico
*/
void ArvoreBusca::removerNo(EstruturaNo*& noRemovido) {   
    Aluno dadosAluno;

    /*
        -> nóTemporario recebe o nó a ser removido (nóRemovido)
            -: nóRemovido não pode ser apagado sem que seja substituído pelos filhos
    */
    EstruturaNo* noTemporario;
    noTemporario = noRemovido; 

    /*
        -> caso não exista FILHO ESQUERDO, o FILHO DIREITO substituirá o valor de nóRemovido
            -: nóTemporário, que aponta para o nóRemovido, será então apagado (desalocado da memória)
    */
        if (noRemovido -> esquerda == NULL) {
        noRemovido = noRemovido -> direita;
        delete noTemporario;
    }
    /*
        -> caso exista FILHO ESQUERDO, entraremos nesta condição, o FILHO ESQUERDO substituirá o valor de nóRemovido
            -: nóTemporário, que aponta para o nóRemovido, será então apagado (desalocado da memória)
        -> caso o FILHO ESQUERDO seja NULL e o FILHO DIREITO seja NULL
            -: o nóRemovido já terá sido substituído por NULL (FILHO DIREITO) no if acima
            -: e será apagado (desalocado) normalmente
    */
    else if (noRemovido -> direita == NULL) {
        noRemovido = noRemovido -> esquerda;
        delete noTemporario;
    }

    /*
        -> caso nóRemovido tem 2 filhos, esquerdo e direito
            -: invocação getSucessor: recuperamos em dadosAluno o conteúdo do sucessor lógico do nó a ser removido
            -: o conteúdo do nóRemovido é substituído pelo seu sucessor lógico
            -: agora temos 2 nós repetidos: nóRemovido == sucessor lógico
                L: invocamos removerAluno, com o RA do sucessor lógico (dadosAluno.getRa()), para apagá-lo, partindo da SUBÁRVORE DIREITA
    */
    else {
        getSucessor(noRemovido, dadosAluno);
        noRemovido -> aluno = dadosAluno;
        removerAluno(noRemovido -> direita, dadosAluno.getRa());
    }
}

/*
    SUCESSOR LÓGICO == filho mais à ESQUERDA POSSÍVEL da SUBÁRVORE DIREITA
        L: importante: a árvore passada como parâmetro NÃO está sendo modificada, pois não está sendo passada por referência

        -> a árvoreNaBusca (parâmetro) será substituída pela sua SUBÁRVORE DIREITA
        -> árvoreNaBusca (parâmetro) == subárvore direita (etapa 1):
            -: enquanto seus filhos esquerdos (subárvore esquerda) não forem NULL: árvoreNaBusca == subávore esquerda (etapa 2)
                L: repete-se até que a subárvore esquerda seja NULL, ou seja, estamos o MAIS À ESQUERDA POSSÍVEL na SUBÁRVORE DIREITA (etapa 1)
        -> quando estivermos no SUCESSOR LÓGICO:
            -: dadosAluno recebe o conteúdo contido ali (arvoreNaBusca -> aluno)
                L: dadosAluno é modificado, pois está sendo referenciado
*/
void ArvoreBusca::getSucessor(EstruturaNo* arvoreNaBusca, Aluno& dadosAluno) {
    arvoreNaBusca = arvoreNaBusca -> direita;
    while (arvoreNaBusca -> esquerda != NULL)
        arvoreNaBusca = arvoreNaBusca -> esquerda;
    dadosAluno = arvoreNaBusca -> aluno;
}

// PRÉ-ORDEM: nó raíz ->> nós da esquerda ->> nós da direita
void ArvoreBusca::printPreOrdem(EstruturaNo* arvore) const {
    if (arvore != NULL) {
        std::cout << arvore -> aluno.getNome() << " , ";
        printPreOrdem(arvore -> esquerda);
        printPreOrdem(arvore -> direita);
    }
}

// IN-ORDEM: nós da esquerda ->> nó raíz ->> nós da direita
void ArvoreBusca::printInOrdem(EstruturaNo* arvore) const {
    if (arvore != NULL) {
        printInOrdem(arvore -> esquerda);
        std::cout << arvore -> aluno.getNome() << " , ";
        printInOrdem(arvore -> direita);
    }
}

// PÓS-ORDEM: nós da esquerda ->> nós da direita ->> nó raíz
void ArvoreBusca::printPosOrdem(EstruturaNo* arvore) const {
    if (arvore != NULL) {
        printPosOrdem(arvore->esquerda);
        printPosOrdem(arvore->direita);
        std::cout << arvore -> aluno.getNome() << " , ";
    }
}